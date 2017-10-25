#pragma once

#include <experimental/filesystem>

struct Vcs {
	Vcs(const std::experimental::filesystem::path& root_dir);
	bool is_vcs_initialized();
	bool init_vcs();
	void commit();
	//todo make private
	void Vcs::call_status(fs::path& dir, vector<fs::path>& result, vector<StagedFileEntry> prevStagedFiles);
	//members
	const std::experimental::filesystem::path root_work_dir;
	const std::experimental::filesystem::path vcs_root_dir;
	const std::experimental::filesystem::path user_file_dir;
};
