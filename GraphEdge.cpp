#include "GraphEdge.h"

GraphEdge::GraphEdge(GraphVertex* from, GraphVertex* to, float weight) {
	this->v1 = from;
	this->v2 = to;
	this->weight = weight;
}

GraphVertex* GraphEdge::getV1()  const {
	return v1;
}

GraphVertex* GraphEdge::getV2() const {
	return v2;
}

GraphVertex* GraphEdge::getOther(int vertex)  const {
	if (vertex == v1->getID()) {
		return v2;
	}
	else if (vertex == v2->getID()) {
		return v1;
	}
	return nullptr;
}

float GraphEdge::getWeight()  const {
	return this->weight;
}

void GraphEdge::print()  const {
	cout << v1->getID() << "--" << weight << "->" << v2->getID() << endl;
}

bool GraphEdge::operator<(const GraphEdge& other) const {
	if (this->weight < other.weight)
		return true;
	else
		return false;
}

bool GraphEdge::operator==(const GraphEdge& other) const {
	bool eq = false;
	if(this->v1 == other.v1 && this->v2 == other.v2)
		eq = true;
	else if(this->v2 == other.v1 && this->v1 == other.v2)
		eq = true;
	return eq && this->weight == other.weight;
}

bool GraphEdge::operator!=(const GraphEdge& other) const {
	return !(*this == other);
}
