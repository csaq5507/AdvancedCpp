#include "stage_file_entry.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

static constexpr char delimiter('\t');

using namespace std;

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


string StagedFileEntry::Serialize(StagedFileEntry& entry) {
	string result = entry.path + delimiter + entry.timestamp;
	return result;
}

StagedFileEntry StagedFileEntry::Deserialize(std::string serialized_staged_file_entry) {
	auto splited = split(serialized_staged_file_entry, delimiter);
	StagedFileEntry entry(splited[0], splited[1]);
	return entry;
}
