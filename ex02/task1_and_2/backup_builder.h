//
// Created by ivan on 25/10/17.
//

#ifndef ADVANCEDCPP_FILE_BUILDER_H
#define ADVANCEDCPP_FILE_BUILDER_H

#include <iostream>
#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;


class backup_builder {

private:
    fs::path root_path;

    fs::path vcs_info_folder;

    fs::path user_files;

    fs::path temp_path;


    bool dir_or_file_exists(const fs::path path);

    fs::path create_file_or_directory(const fs::path path, bool is_file);

    fs::path create_path(const fs::path path, bool is_file);

    const fs::path create_diff_file(const fs::path file_to_backup, int old_version, int new_version);

public:

    backup_builder(const fs::path root_path)
        { this->root_path = root_path; this->user_files = root_path / ".vcs_info_folder" / "user_files"; this->vcs_info_folder = root_path / ".vcs_info_folder"; this->temp_path = root_path / "temp"; }

    ~backup_builder()
        { }

    /**
     *
     * @param file_to_backup relative path to the file that needs to backup, for ex.: "/src/Class/a.cpp"
     * @param old_version
     * @param new_version
     */
    void diff(const fs::path file_to_backup, int old_version, int new_version);

    /**
     *
     * @param file_to_backup relative path to the file that needs to backup, for ex.: "/src/Class/a.cpp"
     */
    void initial_copy(const fs::path file_to_backup);

    fs::path patch(const std::experimental::filesystem::path file_to_backup, int version);
};


#endif //ADVANCEDCPP_FILE_BUILDER_H
