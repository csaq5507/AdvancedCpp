#include "DGraph.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>


constexpr char delimiter = ';';

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


//adjacent list
DGraph::DGraph() : std::vector<std::vector<unsigned>>() {};

unsigned DGraph::num_of_nodes(){
	return this->size();
}

unsigned DGraph::add_vertex() {
	this->push_back(std::vector<unsigned>());
	this->root_node = this->size() - 1;
	return this->size() - 1;
}
	
void DGraph::add_edge(unsigned outgoing_node, unsigned incoming_node) {
	//index out of bounce
	if (outgoing_node >= this->size() || incoming_node >= this->size()) return;
	//TODO add check if incoming node is not alraedy contained
	(*this)[outgoing_node].push_back(incoming_node);
}

std::vector<unsigned> DGraph::vertex_out_degree(unsigned degree) {
	std::vector<unsigned> res;
	for (int i = 0; i < this->size(); i++) {
		if ((*this)[i].size() == degree) res.push_back(i);
	}
	return res;
}

//TODO test
void DGraph::serialize(std::ofstream& f) {
	f << (*this);
}

DGraph DGraph::deserialize(std::istream& s) {
	DGraph g{};
	std::string line;
	//header is root node
	getline(s,line);
	auto root = std::stoul(line);
	while(getline(s,line)){
		auto res = split(line, delimiter);
		std::vector<unsigned> list;
		for(auto& e : res){
			list.push_back(std::stoul(e));
		}
		g.add_vertex();
		g[g.root_node] = list;
	}
	g.root_node = root;
	return g;
}

std::ostream& operator<<(std::ostream &os, const DGraph &m) {
	os << m.root_node << std::endl;
	for (unsigned i = 0; i < m.size(); i++) {
		for(auto it = m[i].begin() ; it != m[i].end(); ++it){
			os << *it << delimiter;
		}
		os << std::endl;
	}
	return os;
}
