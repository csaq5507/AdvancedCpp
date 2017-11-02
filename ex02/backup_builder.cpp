//
// Created by ivan on 25/10/17.
//
#include "backup_builder.h"
#include <vector>

backup_builder::backup_builder(const fs::path root_path) {
    this->root_path = fs::current_path();
    this->vcs_info_dir = this->root_path / std::string(".vcs_info_dir");
    this->user_files = this->vcs_info_dir / std::string("user_file_dir");
    this->temp_path = this->vcs_info_dir / std::string("temp");
    if(!fs::exists(vcs_info_dir)) create_directory(vcs_info_dir);
    if(!fs::exists(user_files)) create_directory(user_files);
    if(!fs::exists(temp_path)) create_directory(temp_path);
}

fs::path backup_builder::create_path(const fs::path path, bool is_file) {
    if(fs::exists(path.parent_path()))
        return (is_file ? create_file(path) : create_directory(path));
    else
        create_path(path.parent_path(), false);
        return (is_file ? create_file(path) : create_directory(path));
}

fs::path backup_builder::create_file(const fs::path path) {
    std::ofstream os(path);
    os << " ";
    os.close();
    return path;
}

fs::path backup_builder::create_directory(const fs::path path) {
    fs::create_directory(path);
	return path;
}

void backup_builder::diff(const fs::path file_to_backup, const std::vector<unsigned> old_version,const int new_version) {
        fs::path previous_file = patch(file_to_backup, old_version);
        fs::path new_file = root_path / file_to_backup;
        fs::path new_patch = vcs_info_dir /  std::to_string(new_version) / file_to_backup;
        create_path(new_patch,true);
        system((std::string("diff ") + previous_file.string() + std::string(" ") + new_file.string() + std::string(" > ") + new_patch.string()).c_str());
}

void backup_builder::initial_copy(const fs::path file_to_backup) {
    create_path(user_files /file_to_backup,true);
    fs::copy(root_path / file_to_backup, user_files /file_to_backup, fs::copy_options::overwrite_existing);
}

fs::path backup_builder::patch(const fs::path file_to_backup, std::vector<unsigned> version) {
    fs::path original_file =  user_files / file_to_backup;
    fs::path current_version= temp_path / file_to_backup;
    create_path(current_version,true);
    fs::copy(original_file, current_version, fs::copy_options::overwrite_existing);
    for(auto& i : version) {
        fs::path current_patch = vcs_info_dir / std::string(std::to_string(i)) / file_to_backup;
		if (!fs::exists(current_patch)) continue;
        system((std::string("patch ") + current_version.string() + std::string(" ") + current_patch.string()).c_str());
    }
    return current_version;
}

