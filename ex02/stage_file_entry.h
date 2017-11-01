#pragma once
#include <string>
#include <experimental/filesystem>

struct StagedFileEntry {
	std::string path;
	std::string timestamp;

	StagedFileEntry(std::string f);
	StagedFileEntry(std::string f, std::string s);
	bool operator==(const StagedFileEntry &other) const;
	bool operator==(const std::experimental::filesystem::path &path) const;
	static std::string getTimeStamp(const std::experimental::filesystem::path& p);
	static std::string Serialize(StagedFileEntry& entry);
	static StagedFileEntry Deserialize(std::string serialized_staged_file_entry);
};