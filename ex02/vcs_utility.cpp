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

Vcs::Vcs() : root_work_dir("."), vcs_root_dir(root_work_dir / vcs_dir_name), user_file_dir (vcs_root_dir / user_files_dir_name), graph(vcs_root_dir / serialized_graph_file_name) {}
	
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

void Vcs::commit(){
	if (!is_vcs_initialized()) return;	
	backup_builder b(root_work_dir);
	//Update graph
	auto oldVersion = graph.root_node;
	auto newVersion = graph.add_vertex();
	graph.add_edge(oldVersion, newVersion);
	graph.root_node = newVersion;

	std::vector<fs::path> allFiles = getAllFiles();
	vector<fs::path> modified = getModifiedFiles();
	vector<fs::path> added = getAddedFiles();
	vector<StagedFileEntry> prevEntries = getPrevStagedFiles();

	for(auto& e : added) b.initial_copy(e);
}

/*
	returns a vector which contains the path to all files of this directory and all sub directories
*/
std::vector<fs::path> Vcs::getAllFiles() {
	std::vector<fs::path> result;
	for (auto& p : fs::recursive_directory_iterator(this->root_work_dir)) {
		auto path = p.path();
		if (path == vcs_root_dir) continue;
		if (!fs::is_directory(path)) {
			result.push_back(path);
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
	auto fileList = getAllFiles();
	auto stagedFiles = getPrevStagedFiles();
	std::vector<fs::path> result;
	//difference(fileList.begin(), fileList.end(), stagedFiles.begin(), stagedFiles.end(), std::back_inserter(result));
	return result;
}

std::vector<fs::path> Vcs::getModifiedFiles() {
	std::vector<fs::path> result;
	auto fileList = getAllFiles();
	auto stagedFiles = getPrevStagedFiles();
	for (auto& e : stagedFiles) {
		auto tmp = std::find(fileList.begin(), fileList.end(), e);
		if (tmp != fileList.end()) {
			if (e.timestamp != StagedFileEntry::getTimeStamp(*tmp)) fileList.erase(tmp);
		}
	}
	//difference(fileList.begin(), fileList.end(), stagedFiles.begin(), stagedFiles.end(), std::back_inserter(result));
	return result;
}

std::vector<StagedFileEntry> Vcs::getPrevStagedFiles() {
	return getStagedFilesEntry(this->vcs_root_dir / std::to_string(this->graph.root_node) / stage_file_name);
}
