#include "DGraph.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <map>
#include <queue>
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

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
DGraph::DGraph() {};
DGraph::DGraph(const fs::path p) {
	std::ifstream  s(p);
	auto r = deserialize(s);
	this->root_node = r.root_node;
	this->adjacentList = r.adjacentList;
}

unsigned DGraph::num_of_nodes(){
	return this->adjacentList.size();
}

unsigned DGraph::add_vertex() {
	this->adjacentList.push_back(std::vector<unsigned>());
	this->root_node = this->adjacentList.size() - 1;
	return this->adjacentList.size() - 1;
}
	
void DGraph::add_edge(unsigned outgoing_node, unsigned incoming_node) {
	//index out of bounce
	if (outgoing_node >= this->adjacentList.size() || incoming_node >= this->adjacentList.size()) return;
	//TODO add check if incoming node is not already contained
	(*this).adjacentList[outgoing_node].push_back(incoming_node);
}

std::vector<unsigned> DGraph::vertex_out_degree(unsigned degree) {
	std::vector<unsigned> res;
	for (unsigned i = 0; i < this->adjacentList.size(); i++) {
		if ((*this).adjacentList[i].size() == degree) res.push_back(i);
	}
	return res;
}

//TODO test
void DGraph::serialize(std::ofstream& f) {
	f << (*this);
}

DGraph DGraph::deserialize(std::ifstream& s) {
	DGraph g{};
	std::string line;
	//header is root node
	getline(s,line);
	auto root = std::stoul(line);
	getline(s, line);
	auto num_of_nodes = std::stoul(line);
	while(getline(s,line)){
		auto res = split(line, delimiter);
		std::vector<unsigned> list;
		for(auto& e : res){
			auto val = std::stoul(e);
			//TODO make meaningfull exception
			if (val >= num_of_nodes) throw 11;
			list.push_back(std::stoul(e));
		}
		g.add_vertex();
		g.adjacentList[g.root_node] = list;
	}
	g.root_node = root;
	return g;
}

//TODO test
std::vector<unsigned> DGraph::BFS (const unsigned startNode,const unsigned endNode){
	std::vector<unsigned> res;
	std::map<unsigned,unsigned> path;
	bool done = false;
	if(startNode >= this->adjacentList.size() || endNode >= this->num_of_nodes()) return res;
	std::vector<bool> visited = std::vector<bool>(this->num_of_nodes(), false);
	std::queue<unsigned> queue;
	visited[startNode] = true;
	queue.push(startNode);
	while(!queue.empty() && done){
		auto n = queue.front();
		queue.pop();
		for(auto c : (*this).adjacentList[n]){
			if(visited[c]) continue;
			visited[c] = true;
			queue.push(c);
			path[c] = n;
			if(c == endNode){
				done = true;
				break;
			}
		}
	}
	if(done){
		auto parent = endNode;
		res.push_back(parent);
		while(parent != startNode){
			parent = path[parent];
			res.push_back(parent);
		}
	}
	std::reverse(std::begin(res), std::end(res));
	return res;
}

std::ostream& operator<<(std::ostream &os, const DGraph &m) {
	os << m.root_node << std::endl;
	os << m.adjacentList.size() << std::endl;

	for (unsigned i = 0; i < m.adjacentList.size(); i++) {
		for(auto it = m.adjacentList[i].begin() ; it != m.adjacentList[i].end(); ++it){
			os << *it;
			if((it + 1) != m.adjacentList[i].end()) os << delimiter;
		}
		os << std::endl;
	}
	return os;
}