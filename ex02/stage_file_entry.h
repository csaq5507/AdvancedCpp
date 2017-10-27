#pragma once
#include <string>

struct StagedFileEntry {
	std::string path;
	std::string timestamp;
	StagedFileEntry(std::string f, std::string s) : path(f), timestamp(s) {}

	static std::string Serialize(StagedFileEntry& entry);
	static StagedFileEntry Deserialize(std::string serialized_staged_file_entry);
};