#pragma once

#include <experimental/filesystem>
#include "stage_file_entry.h"
#include "DGraph.h"

struct Vcs {
	Vcs();

	bool is_vcs_initialized();
	bool init_vcs();
	void commit();

	std::vector<std::experimental::filesystem::path> getAllFiles();
	std::vector<std::experimental::filesystem::path> Vcs::getAddedFiles();
	std::vector<StagedFileEntry> Vcs::getPrevStagedFiles();
	std::vector<std::experimental::filesystem::path> Vcs::getModifiedFiles();
	//members
	//TODO make graph a member
	DGraph graph;
	const std::experimental::filesystem::path root_work_dir;
	const std::experimental::filesystem::path vcs_root_dir;
	const std::experimental::filesystem::path user_file_dir;

};