//
// Created by ivan on 25/10/17.
//
#include "backup_builder.h"

fs::path backup_builder::create_path(const fs::path path, bool is_file) {
    if(dir_or_file_exists(path.parent_path()))
        return create_file_or_directory(path, is_file);
    else
        create_path(path.parent_path(), false);
        return create_file_or_directory(path, is_file);
}

fs::path backup_builder::create_file_or_directory(const fs::path path, bool is_file) {
    if(is_file){
        std::ofstream os(path);
        os << " ";
        os.close();
    }
    else
        fs::create_directory(path);
    return path;
}

bool backup_builder::dir_or_file_exists(const fs::path path) {
    if(fs::exists(path))
        return true;
    else
        return false;
}


void backup_builder::diff(const fs::path file_to_backup, int old_version, int new_version) {
    if(old_version==0) {
        system((std::string("diff ") + (user_files / file_to_backup).string() + std::string(" ") +
                (root_path / file_to_backup).string() + std::string(" > ") +
                (temp_path / file_to_backup).string()).c_str());
        create_path(vcs_info_folder / "node1" / file_to_backup,true);
        fs::copy(temp_path / file_to_backup,vcs_info_folder / "node1" / file_to_backup,fs::copy_options::overwrite_existing);
    } else {
        fs::path previous_file = patch(file_to_backup, old_version);
        fs::path new_file = root_path / file_to_backup;
        fs::path new_patch = vcs_info_folder / (std::string("node") + std::to_string(new_version)) / file_to_backup;
        system((std::string("diff ") + previous_file.string() + std::string(" ") + new_file.string() + std::string(" > ") + new_patch.string()).c_str());
    }
}

void backup_builder::initial_copy(const fs::path file_to_backup) {
    create_path(user_files /file_to_backup,true);
    fs::copy(root_path / file_to_backup, user_files /file_to_backup, fs::copy_options::overwrite_existing);
}

fs::path backup_builder::patch(const fs::path file_to_backup, int version) {
    fs::path original_file =  user_files / file_to_backup;
    fs::path current_version=original_file / ".temp";
    fs::copy(original_file, current_version);
    for(int i=1;i<=version;i++)
    {
        fs::path current_patch = vcs_info_folder / (std::string("node") + std::string(std::to_string(i))) / file_to_backup;
        system((std::string("patch ") + current_version.string() + std::string(" ") + current_patch.string()).c_str());
    }
    return current_version;
}

