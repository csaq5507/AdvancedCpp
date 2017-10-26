//
// Created by ivan on 25/10/17.
//
#include "backup_builder.h"

backup_builder::backup_builder(const fs::path root_path) {
    this->root_path = root_path;
    this->vcs_info_folder = root_path / std::string(".vcs_info_folder");
    this->user_files = this->vcs_info_folder / std::string("user_files");
    this->temp_path = this->vcs_info_folder / std::string("temp");
    if(!dir_or_file_exists(vcs_info_folder)) create_file_or_directory(vcs_info_folder,false);
    if(!dir_or_file_exists(user_files)) create_file_or_directory(user_files,false);
    if(!dir_or_file_exists(temp_path)) create_file_or_directory(temp_path,false);
}

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
        fs::path previous_file = user_files / file_to_backup;
        fs::path new_file = root_path / file_to_backup;
        fs::path new_patch = vcs_info_folder / std::string("node1") / file_to_backup;
        create_path(new_patch,true);
        system((std::string("diff ") + previous_file.string() + std::string(" ") + new_file.string() + std::string(" > ") + new_patch.string()).c_str());
    } else {
        fs::path previous_file = patch(file_to_backup, old_version);
        fs::path new_file = root_path / file_to_backup;
        fs::path new_patch = vcs_info_folder / (std::string("node") + std::to_string(new_version)) / file_to_backup;
        create_path(new_patch,true);
        system((std::string("diff ") + previous_file.string() + std::string(" ") + new_file.string() + std::string(" > ") + new_patch.string()).c_str());
    }
}

void backup_builder::initial_copy(const fs::path file_to_backup) {
    create_path(user_files /file_to_backup,true);
    fs::copy(root_path / file_to_backup, user_files /file_to_backup, fs::copy_options::overwrite_existing);
}

fs::path backup_builder::patch(const fs::path file_to_backup, int version) {
    fs::path original_file =  user_files / file_to_backup;
    fs::path current_version= temp_path / file_to_backup;
    fs::copy(original_file, current_version);
    for(int i=1;i<=version;i++)
    {
        fs::path current_patch = vcs_info_folder / (std::string("node") + std::string(std::to_string(i))) / file_to_backup;
        system((std::string("patch ") + current_version.string() + std::string(" ") + current_patch.string()).c_str());
    }
    return current_version;
}

