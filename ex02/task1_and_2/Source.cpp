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
	test.call_status(vector<StagedFileEntry>(),mod, add);
	//std::ifstream f(test.vcs_root_dir / "serialized_graph.txt");
	//DGraph graph = DGraph::deserialize(f);
	//cout << graph;
	//cout << "Num of nodes: " << graph.num_of_nodes() << endl;
	
	//std::ofstream f(test.vcs_root_dir / "serialized_graph.txt");
	//DGraph graph{};
	//graph.add_vertex();
	//cout << graph;
	//graph.serialize(f);
	
	return 0;
}
