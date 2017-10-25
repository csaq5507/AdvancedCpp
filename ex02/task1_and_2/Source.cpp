#include <iostream>
#include <experimental/filesystem>
#include <fstream>
#include "vcs_utility.h"

using namespace std;
namespace fs = experimental::filesystem;

int main(int argv, char** args) {
	auto test = Vcs();
	test.init_vcs();
	test.commit();
	vector<fs::path> mod;
	vector<fs::path> add;
	test.call_status(vector<StagedFileEntry>(),mod, add);
	cout << "modified" << endl;
	for(auto& e : mod){
		cout << e << endl;
	}
	
	cout << "added" << endl;
	for(auto& e : add){
		cout << e << endl;
	}
	
	return 0;
}
