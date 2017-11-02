#pragma warning(disable : 4996)

#include "stage_file_entry.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

static constexpr char delimiter('?');

using namespace std;
namespace fs = std::experimental::filesystem;

template <typename T>
static void split(const string &input, const char delim, T res) {
	istringstream stream(input);
	string token;
	while (getline(stream, token, delim)) {
		*res++ = token;
	}
}

static vector<string> split(const string& s, const char delim) {
	vector<string> result;
	split(s, delim, back_inserter(result));
	return result;
}

StagedFileEntry::StagedFileEntry(std::string f, std::string s) : path(f), timestamp(s) {}
StagedFileEntry::StagedFileEntry(std::string f) : path(f), timestamp(getTimeStamp(f)) {}

string StagedFileEntry::Serialize(StagedFileEntry& entry) {
	string result = entry.path + delimiter + entry.timestamp;
	return result;
}

std::string StagedFileEntry::Serialize(std::experimental::filesystem::path& p) {
	string result = p.string() + delimiter + getTimeStamp(p);
	return result;
}

StagedFileEntry StagedFileEntry::Deserialize(std::string serialized_staged_file_entry) {
	auto splited = split(serialized_staged_file_entry, delimiter);
	StagedFileEntry entry(splited[0], splited[1]);
	return entry;
}

std::string StagedFileEntry::getTimeStamp(const fs::path& p) {
	auto time = fs::last_write_time(p);
	std::time_t cftime = decltype(time)::clock::to_time_t(time);
	std::string res = std::asctime(std::localtime(&cftime));
	res.erase(res.length()-1);
	return res;
}

bool StagedFileEntry::operator==(const StagedFileEntry &other) const {
	return this->path == other.path && this->timestamp == other.timestamp;
}
bool StagedFileEntry::operator==(const std::experimental::filesystem::path &path) const {
	return this->path == path;
}