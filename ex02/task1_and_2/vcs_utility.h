#pragma once

#include <experimental\filesystem>

/*convention is that the folder containing vcs information is called vcs_info_folder */
bool is_vcs_initialized(std::experimental::filesystem::path& p);
bool init_vcs(std::experimental::filesystem::path& p);
std::experimental::filesystem::path getStagedFileFromRootDic(std::experimental::filesystem::path& rootDic);
void call_status(std::experimental::filesystem::path& rootDir, std::experimental::filesystem::path& stagedFile);