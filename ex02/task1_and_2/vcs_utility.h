#pragma once

#include <experimental/filesystem>
#include "stage_file_entry.h"

struct Vcs {
	Vcs(const std::experimental::filesystem::path& root_dir);
	bool is_vcs_initialized();
	bool init_vcs();
	void commit();
	//todo make private
	void call_status(std::vector<StagedFileEntry> prevStagedFiles, std::vector<std::experimental::filesystem::path>& result);
	//members
	const std::experimental::filesystem::path root_work_dir;
	const std::experimental::filesystem::path vcs_root_dir;
	const std::experimental::filesystem::path user_file_dir;

private:
	void call_status(const std::experimental::filesystem::path& dir, std::vector<StagedFileEntry> prevStagedFiles, std::vector<std::experimental::filesystem::path>& result);
};
