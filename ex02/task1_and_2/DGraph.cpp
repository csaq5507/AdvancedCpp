#include <iostream>
#include <vector>

constexpr char delimiter = ';';
constexpr char tab = '\t';

//adjacent list
class DGraph : std::vector<std::vector<unsigned>> {
public:
	DGraph() : std::vector<std::vector<unsigned>>() {};

	unsigned add_vertex() {
		this->push_back(std::vector<unsigned>());
		return this->size() - 1;
	}
	
	void add_edge(unsigned outgoing_node, unsigned incoming_node) {
		//index out of bounce
		if (outgoing_node >= this->size() || incoming_node >= this->size()) return;
		//TODO add check if incoming node is not alraedy contained
		(*this)[outgoing_node].push_back(incoming_node);
	}

	std::vector<unsigned> vertex_out_degree(unsigned degree) {
		std::vector<unsigned> res;
		for (int i = 0; i < this->size(); i++) {
			if ((*this)[i].size() == degree) res.push_back(i);
		}
		return res;
	}

	friend std::ostream &operator<<(std::ostream &os, const DGraph &m);
	//TODO
	void serialize() {}
	DGraph deserialize() { return DGraph{}; }
};

std::ostream &operator<<(std::ostream &os, const DGraph &m) {
	for (unsigned i = 0; i < m.size(); i++) {
		os << i << tab;
		for (auto& e : m[i]) {
			os << e << delimiter;
		}
		os << std::endl;
	}
	return os;
}