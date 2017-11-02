#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <experimental/filesystem>



//adjacent list
class DGraph {
public:
	DGraph();
	DGraph(const std::experimental::filesystem::path p);

	unsigned add_vertex();
	void add_edge(unsigned outgoing_node, unsigned incoming_node);

	std::vector<unsigned> vertex_out_degree(unsigned degree);
	std::vector<unsigned> BFS(const unsigned startNode, const unsigned endNode);
	friend std::ostream &operator<<(std::ostream &os, const DGraph &m);
	//TODO
	void serialize(std::ofstream& f);
	static DGraph deserialize(std::ifstream& s);
	unsigned num_of_nodes();

	//members
	unsigned root_node;
	std::vector<std::vector<unsigned>> adjacentList;
};

std::ostream &operator<<(std::ostream &os, const DGraph &m);
