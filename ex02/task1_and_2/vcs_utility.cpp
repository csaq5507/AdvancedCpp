#pragma warning(disable : 4996)

#include "vcs_utility.h"
#include "stage_file_entry.h"
#include <experimental\filesystem>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;
namespace fs = std::experimental::filesystem;

const std::string vcs_dic_name(".vcs_info_folder");
const std::string stage_file_name(".staged_files.txt");


enum file_status {
	modified,
	not_modified,
	removed,
	not_added
};

bool is_vcs_initialized(fs::path& p) {
	return exists(p / vcs_dic_name);
}

/* stage file convention: first line contains "#Staged files"
next lines contains the staged files and additional information in following order
"file name"\t"timestamp"\n
*/
void create_stage_file(fs::path& p) {
	auto f = p / stage_file_name;
	if (exists(f)) remove(f);
	std::ofstream stage_info_file(f);
	stage_info_file << "#Staged files" << std::endl;
	stage_info_file.close();
}

/* TODO: discusse with teammates how to handle error, only with bool and set glboal flag or throw exceptions*/
bool init_vcs(fs::path& p) {
	if (is_vcs_initialized(p)) return false;
	auto vcs_dic = p / vcs_dic_name;
	create_directory(vcs_dic);
	//TODO add config files
	create_stage_file(vcs_dic);

	return true;
}

fs::path getStagedFileFromRootDic(fs::path& rootDic) {
	return rootDic / vcs_dic_name / stage_file_name;
}


//TODO test
file_status check_file_status(fs::path& fileToCheck, vector<StagedFileEntry> stageFileEntries) {
	for (auto& e : stageFileEntries) {
		if (e.path == fileToCheck) {
			auto timeStamp = fs::last_write_time(fileToCheck);
			std::time_t cftime = decltype(timeStamp)::clock::to_time_t(timeStamp);
			if (e.timestamp == std::asctime(std::localtime(&cftime))) return not_modified;
			return modified;
		}
	}
	return not_added;
}


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