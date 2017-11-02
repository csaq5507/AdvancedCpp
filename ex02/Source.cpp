#include <iostream>
#include <experimental/filesystem>
#include <boost/program_options.hpp>
#include <fstream>

#include "vcs_utility.h"
#include "DGraph.h"

using namespace std;
namespace fs = experimental::filesystem;
namespace po = boost::program_options;

int main(int argv, char** args) {
	
	auto vcs = Vcs();
	string message="";
	int node=-1;
	int node_a=-1;
	int node_b=-1;
	
	po::options_description desc("Allowed options");
	desc.add_options()
    ("help,h", "help")
    ("init,i", "init")
    ("commit,c", po::value< string >(&message), "commit")
    ("show,s", po::value<int>(&node), "show")
    ("checkout,o", po::value<int>(&node), "checkout")
    ("mergea,a", po::value<int>(&node_a), "mergea")
	("mergeb,b", po::value<int>(&node_b), "mergeb");
	
	po::variables_map vm;
	po::store(po::parse_command_line(argv, args, desc), vm);
	po::notify(vm);   
	
	if (vm.count("help")) {
    cout << desc << "\n";
    return 1;
	} else if (vm.count("init")) {
		vcs.init_vcs();
	} else if (vm.count("commit")) {
		if (message == "") {
			cout << "No commit message set" << endl;
		} else{
			vcs.commit(message);
		}
	} else if (vm.count("show")) {
		if (node == -1) {
			cout << "No node set" << endl;
		} else{
			//vcs.show(node);
		}
	} else if (vm.count("checkout")) {
		if (node == -1) {
			cout << "No node set" << endl;
		} else{
			vcs.checkout(node);
		}
	} else if (vm.count("merge")) {
		if (node_a == -1 || node_b == -1) {
			cout << "No node set" << endl;
		} else{
			//vcs.merge(node_a, node_b);
		}
	} else {
		cout << "Unknown command" << endl;
	}

	return 0;
}
