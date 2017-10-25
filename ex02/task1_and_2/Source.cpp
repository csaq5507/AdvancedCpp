#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include "vcs_utility.h"

using namespace std;
namespace fs = experimental::filesystem;

int main(int argv, char** args) {
	auto test = Vcs(fs::current_path());
	test.init_vcs();
	test.commit();
	vector<fs::path> result;
	test.call_status(vector<StagedFileEntry>(),result);
	for(auto& e : result){
		cout << e << endl;
	}
	return 0;
}
