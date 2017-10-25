#include <iostream>
#include <experimental/filesystem>
#include <string_view>
#include <fstream>

using namespace std;
namespace fs = experimental::filesystem;

int main(int argv, char** args) {
	
	auto path = fs::current_path();
	cout << path << endl;
	ofstream file(path / "t" / "t.txt");
	file << "lest see" << endl;
	//	if (!is_vcs_initialized(path)) {
//	init_vcs(path);
	  //	}
	//call_status(path, getStagedFileFromRootDic(path));
	

	return 0;
}
