#include <iostream>
#include <experimental/filesystem>
#include <string_view>
#include <fstream>
#include "vcs_utility.h"

using namespace std;
namespace fs = experimental::filesystem;

int main(int argv, char** args) {
	auto test = Vcs(fs::current_path());
	test.init_vcs();
	test.commit();
	return 0;
}
