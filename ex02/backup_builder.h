//
// Created by ivan on 25/10/17.
//

#ifndef ADVANCEDCPP_FILE_BUILDER_H
#define ADVANCEDCPP_FILE_BUILDER_H

#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include <vector>

namespace fs = std::experimental::filesystem;


class backup_builder {

private:
    fs::path root_path; /** The root path of the VCS Folder containing src and .vcs_info_dir */

    fs::path vcs_info_dir; /** The path of the vcs info folder containing user_files and nodes */

    fs::path user_files; /** The path of the user files folder containing the initial copy of every file */

    fs::path temp_path; /** The path of a folder containing temporary createt files */

    /**
     * Creates a empty file at path
     * @param path
     * @return the path of the file
     */
    fs::path create_file(const fs::path path);

    /**
     * Creates a directory like experimental::filesystem::create_directory and returns the same
     * @param path
     * @return the path of the createt directory
     */
    fs::path create_directory(const fs::path path);

public:
	/**
	* Builds creates Files and folders of a given path
	* @param path
	* @param is_file true if the path is a path to a file, false if it's a directory
	* @return
	*/
	fs::path create_path(const fs::path path, bool is_file);

    /**
     * Creates a instance of the backup builder.
     * With the backup builder class you are able to create diff's of some root Path and patch them back to a arbitrary version.
     * Constructor creates ".vcs_info_dir", "..vcs_info_dir/user_files" and ".vcs_info_dir/temp" if not exist
     *
     * @param root_path of the source files
     */
    backup_builder(const fs::path root_path);

    ~backup_builder()
        { }

    /**
     * Creates a diff file of the file_to_backup in the ".vcs_info_dir/node{new_version}"
     *
     * @param file_to_backup relative path to the file that needs to backup, for ex.: "/src/Class/a.cpp"
     * @param old_version
     * @param new_version
     */
    void diff(const fs::path file_to_backup, const std::vector<unsigned> old_version, const int new_version);

    /**
     * Copy the file_to_backup into the ".vcs_info_dir/user_files"
     *
     * @param file_to_backup relative path to the file that needs to backup, for ex.: "/src/Class/a.cpp"
     */
    void initial_copy(const fs::path file_to_backup);

    /**
     * Patch a the ".vcs_info_dir/node{version}/file_to_backup" diff file back and return the path of the file.
     * Patched file is in the ".vcs_info_dir/temp/" folder.
     *
     * @param file_to_backup
     * @param version
     * @return
     */
    fs::path patch(const std::experimental::filesystem::path file_to_backup, std::vector<unsigned> version);
};


#endif //ADVANCEDCPP_FILE_BUILDER_H
