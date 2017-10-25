#pragma warning(disable : 4996)

#include "vcs_utility.h"
#include "stage_file_entry.h"
#include "DGraph.h"
#include <experimental/filesystem>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

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

Vcs::Vcs() : root_work_dir("."), vcs_root_dir(root_work_dir / vcs_dir_name), user_file_dir (vcs_root_dir / user_files_dir_name) {}
	
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

void Vcs::commit(){
	//true -> first commit
	//TODO add edge
	DGraph graph{};
	if(fs::is_empty(vcs_root_dir / serialized_graph_file_name)){
		//TODO
		//?
		//can be deleted ?
	} else {
		std::ifstream f(vcs_root_dir / serialized_graph_file_name);
		graph = DGraph::deserialize(f);
		//graph = DGraph::deserialize(this->graphPath);
	}
	vector<fs::path> modified;
	vector<fs::path> added;
	call_status(vector<StagedFileEntry>(),modified, added);
	
	//variables to save data which must be written to stage_file
	unsigned num_stage_files = 0;
	std::string stage_file_entries("");
	
	for(auto& e : added){
		num_stage_files++;
		stage_file_entries += string(e) + string("\n");
		//TODO 
		//copy files with function of ivan
	}
	for(auto& e : modified) {
		num_stage_files++;
		stage_file_entries += string(e) + string("\n");
		//TODO
		//read previous version from "?"
		//create diff files with function of ivan
	}
	//TODO 
	//write this below into file stage_file.txt at the correct node folder
	cout << "Num of files for stage x: " << num_stage_files << endl;
	cout << endl;
	cout << "Files to add to stage file x: " << endl;
	cout << stage_file_entries;
	
	//create new node file
	//set current root node
	
	//TODO
	//Write graph back to file
	//graph.serialize();
}

//TODO test
file_status check_file_status(fs::path& fileToCheck, vector<StagedFileEntry> prevStagedFiles) {
	for (auto& e : prevStagedFiles) {
		if (e.path == fileToCheck) {
			auto timeStamp = fs::last_write_time(fileToCheck);
			std::time_t cftime = decltype(timeStamp)::clock::to_time_t(timeStamp);
			if (e.timestamp == std::asctime(std::localtime(&cftime))) return not_modified;
			return modified;
		}
	}
	return added;
}

void Vcs::call_status(vector<StagedFileEntry> prevStagedFiles, vector<fs::path>& modifiedFiles, vector<fs::path>& addedFiles) {
	call_status(fs::path("."), prevStagedFiles, modifiedFiles, addedFiles);
}
void Vcs::call_status(const fs::path& dir, vector<StagedFileEntry> prevStagedFiles, vector<fs::path>& modifiedFiles, vector<fs::path>& addedFiles) {
	for (auto& p : fs::directory_iterator(dir)) {
		auto path = p.path();
		if(path == vcs_root_dir) continue;
		if (fs::is_directory(path)) {
			call_status(path, prevStagedFiles, modifiedFiles, addedFiles);
		}else {
			auto status = check_file_status(path, prevStagedFiles);
			if(status == modified){
				modifiedFiles.push_back(path);
			} else if (status == added){
				addedFiles.push_back(path);
			}
		}
	}
}



/*
//TODO Test
file_status check_stagedFile_status(string timeStamp, fs::path& stagedFile) {
	if (fs::exists(stagedFile)) {
		//todo check time stamp
		auto time = fs::last_write_time(stagedFile);
		std::time_t cftime = decltype(time)::clock::to_time_t(time);
		if (timeStamp == std::asctime(std::localtime(&cftime))) return not_modified;
		return modified;
	}
	return removed;
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

void call_status(fs::path& dir, vector<StagedFileEntry> stageFileEntries) {
	for (auto& p : fs::directory_iterator(dir)) {
		auto path = p.path();
		auto status = check_file_status(path, stageFileEntries);

		std::cout << path << "\t status is: " << status << std::endl;
		if (fs::is_directory(path)) {
			if (status != not_added || status != removed) call_status(path, stageFileEntries);
		}
	}
}

//Problem consider deleted dictonary
//maybe fix with relative paths
//change call structure...meaning that given a path it checks if the file is Removed, Modified, Not-Added or Not-Modified
//atm for debugging purpose only printing
void call_status(fs::path& rootDir, fs::path& stagedFile) {
	vector<StagedFileEntry> stageFileEntries = getStagedFilesEntry(getStagedFileFromRootDic(rootDir));
	call_status(rootDir, stageFileEntries);
}
* */

//TODO implement graph, boost needs too much kwonlage for realibale usage!!! see http://www.boost.org/doc/libs/1_60_0/libs/graph/doc/adjacency_list.html for proof


//TODO commit changes:
//  first commit has special behavour, it stores all files and creates the root node of the graph
//  commit creates branch if graph has an outgoing edge at current node
//  merge searches for nodes which have no outgoing edge
//  stage file files contains data structure of every node
//  update graph and current root node
//  can affect staged files
//  can generate diff files
//  vcs order structure
//  --> userFiles (contains all the user files with the conntet at creation time (first commit))
//  --> currentRootNode (this will be inizialized at first commit)
//  --> serilzed graph
//	--> <graphNodeDesc>
//  each graphNodeDesc contains
//  --> commit msg
//  --> staged Files
//  --> possible diff files....based on staged file, convention using perfix file name
