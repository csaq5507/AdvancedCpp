#include <iostream>
#include <experimental/filesystem>
#include <fstream>

#include "vcs_utility.h"
#include "DGraph.h"

using namespace std;
namespace fs = experimental::filesystem;

int main(int argv, char** args) {
	auto test = Vcs();
	test.init_vcs();
	test.commit();
	vector<fs::path> mod;
	vector<fs::path> add;
	
	
	return 0;
}
