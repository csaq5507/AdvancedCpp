#pragma once

#include <experimental/filesystem>
#include "stage_file_entry.h"
#include "DGraph.h"

struct Vcs {
	const std::experimental::filesystem::path root_work_dir;
	const std::experimental::filesystem::path vcs_root_dir;
	const std::experimental::filesystem::path user_file_dir;


	Vcs();

	bool is_vcs_initialized();
	bool init_vcs();
	void commit(std::string commitMsg);
	void show();
	void checkout(int version);

	std::vector<std::experimental::filesystem::path> getAllFiles();
	std::vector<std::experimental::filesystem::path> getAllFiles(const std::experimental::filesystem::path& dir);
	std::vector<std::experimental::filesystem::path> getAddedFiles();
	std::vector<StagedFileEntry> getPrevStagedFiles();
	std::vector<std::experimental::filesystem::path> getModifiedFiles();
	//members
	//TODO make graph a member
	DGraph graph;

};