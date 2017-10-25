#pragma once

#include <experimental/filesystem>

class Vcs {
	Vcs(const std::experimental::filesystem::path& root_dir);
	bool is_vcs_initialized();
	bool init_vcs();
	//members
	const std::experimental::filesystem::path root_work_dir;
	const std::experimental::filesystem::path vcs_root_dir;
	const std::experimental::filesystem::path user_file_dir;
};
