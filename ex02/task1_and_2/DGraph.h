#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

//adjacent list
class DGraph : std::vector<std::vector<unsigned>> {
public:
	DGraph();

	unsigned add_vertex();
	void add_edge(unsigned outgoing_node, unsigned incoming_node);

	std::vector<unsigned> vertex_out_degree(unsigned degree);

	friend std::ostream &operator<<(std::ostream &os, const DGraph &m);
	//TODO
	void serialize(std::ofstream& f) ;
	static DGraph deserialize(std::istream& s);
	unsigned num_of_nodes();
	unsigned root_node;
};

std::ostream &operator<<(std::ostream &os, const DGraph &m);
