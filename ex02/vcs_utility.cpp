#include "vcs_utility.h"
#include "stage_file_entry.h"
#include "DGraph.h"
#include "backup_builder.h"
#include <experimental/filesystem>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
namespace fs = std::experimental::filesystem;

const std::string vcs_dir_name(".vcs_info_dir");
const std::string user_files_dir_name("user_file_dir");
const std::string stage_file_name("staged_files.txt");
const std::string serialized_graph_file_name("serialized_graph.txt");

enum file_status {
	modified,
	not_modified,
	added
};

    Vcs::Vcs() : root_work_dir("."), vcs_root_dir(root_work_dir / vcs_dir_name), user_file_dir (vcs_root_dir / user_files_dir_name){
	if (is_vcs_initialized()) {
		ifstream in(vcs_root_dir / serialized_graph_file_name);
		graph = DGraph::deserialize(in);
	}
}

Vcs::~Vcs() {
	ofstream out(vcs_root_dir / serialized_graph_file_name, std::ios_base::trunc);
	graph.serialize(out);
}
	
bool Vcs::is_vcs_initialized() {
	return exists(vcs_root_dir);
}
	
bool Vcs::init_vcs() {
	if (is_vcs_initialized()) return false;
	create_directory(vcs_root_dir);
	create_directory(user_file_dir);
	DGraph g{};
	g.add_vertex();
	create_directory(vcs_root_dir / fs::path(std::to_string(g.root_node)));
	std::ofstream f(vcs_root_dir / serialized_graph_file_name);
	g.serialize(f);
	graph=g;
	return true;
}

//TODO test + rename args
vector<StagedFileEntry> getStagedFilesEntry(fs::path& f) {
	vector<StagedFileEntry> result;
	ifstream file(f);
	string line;
	//cut of header
	getline(file, line);
	while (getline(file, line)) {
		result.push_back(StagedFileEntry::Deserialize(line));
	}
	return result;
}

void Vcs::commit(std::string commitMsg){
	if (!is_vcs_initialized()) return;	
	backup_builder b(root_work_dir);

	std::vector<fs::path> allFiles = getAllFiles();
	vector<fs::path> modified = getModifiedFiles();
	vector<fs::path> added = getAddedFiles();
	vector<StagedFileEntry> prevEntries = getPrevStagedFiles();
	if (modified.empty() && added.empty()) return;

	//Update graph
	auto oldVersion = graph.root_node;
	auto newVersion = graph.add_vertex();
	graph.add_edge(oldVersion, newVersion);
	graph.root_node = newVersion;


	auto stageFilePath = this->vcs_root_dir / std::to_string(this->graph.root_node) / stage_file_name;
	b.create_path(stageFilePath, true);
	std::ofstream f(stageFilePath);

	auto oldDiffs = graph.BFS(0, oldVersion);

    added = remove_point(added);
    modified = remove_point(modified);
    allFiles = remove_point(allFiles);

	for(auto& e : added) b.initial_copy(e);
	for(auto& e : modified) b.diff(e, oldDiffs, newVersion);
	for(auto& e : allFiles) { f << StagedFileEntry::Serialize(e) << endl; }

	std::ofstream f1(this->vcs_root_dir / std::to_string(this->graph.root_node) / "commitMsg");
	f1 << commitMsg;
}

std::vector<fs::path> Vcs::remove_point(std::vector<fs::path> files)
{
    std::vector<fs::path> result=std::vector<fs::path>();
    for(auto& e : files){
        fs::path new_path = fs::path();
        for(auto& elem : e){
            if(elem.string() !=".")
                new_path=new_path / elem;
        }
        std::string test = new_path.string();
        result.push_back(new_path);
    }
    return result;
}

void Vcs::show() {
	auto folder = this->vcs_root_dir / std::to_string(this->graph.root_node);
	auto files = getAllFiles(folder);
	for (auto& f : files) {
		system((std::string("cat ") + f.string()).c_str());
	}
}

void Vcs::checkout(int version) {
	backup_builder b(root_work_dir);
	if (version < 0 || version >= graph.num_of_nodes()) return;
	//Todo test then add the remove command
	//fs::remove_all(this->root_work_dir);
	graph.root_node = version;
	auto diffs = graph.BFS(0, version);

	auto stageFilePath = this->vcs_root_dir / std::to_string(this->graph.root_node) / stage_file_name;
	vector<StagedFileEntry> prevEntries = getPrevStagedFiles();
	for (auto& f : prevEntries) {
		auto tmpFile = b.patch(f.path, diffs);
		fs::copy(tmpFile, root_work_dir / f.path, fs::copy_options::overwrite_existing);
	}
}

/*
	returns a vector which contains the path to all files of this directory and all sub directories
*/
std::vector<fs::path> Vcs::getAllFiles() {
	return getAllFiles(this->root_work_dir);
}

std::vector<fs::path> Vcs::getAllFiles(const fs::path& dir) {
	std::vector<fs::path> result;
	for (auto& p : fs::directory_iterator(dir)) {
		auto path = p.path();
		if (path == vcs_root_dir || path.filename().string()=="VCS") continue;
		if (!fs::is_directory(path)) {
			result.push_back(path);
		} else {
			auto tmp = getAllFiles(p);
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
	}
	return result;
}

template<class InputIt1, class InputIt2, class Out>
void difference(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Out result) {
	for (;first1 != last1; first1++) {
		bool eq = false;
		for (auto inner = first2; inner != last2; inner++) {
			if (*inner == *first1) eq = true;
		}
		if (!eq) *(result++) = *first1;
	}
}

std::vector<fs::path> Vcs::getAddedFiles() {
	auto fileList = remove_point(getAllFiles());
	auto stagedFiles = getPrevStagedFiles();
	std::vector<fs::path> result;
	difference(fileList.begin(), fileList.end(), stagedFiles.begin(), stagedFiles.end(), std::back_inserter(result));
	return result;
}

std::vector<fs::path> Vcs::getModifiedFiles() {
	auto fileList = remove_point(getAllFiles());

	std::vector<fs::path> result;
	auto stagedFiles = getPrevStagedFiles();
	for (auto& e : stagedFiles) {
		auto tmp = std::find(fileList.begin(), fileList.end(), e.path);
		if (tmp != fileList.end()) {
			auto s = StagedFileEntry::getTimeStamp(*tmp);
			if (e.timestamp != s) {
				result.push_back(*tmp);
			}
		}
	}
	return result;
}

std::vector<StagedFileEntry> Vcs::getPrevStagedFiles() {
	auto path = this->vcs_root_dir / std::to_string(this->graph.root_node) / stage_file_name;
	return getStagedFilesEntry(path);
}
