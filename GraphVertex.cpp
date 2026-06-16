#include "GraphVertex.h"

GraphVertex::GraphVertex(string name, int id) {
	this->id = id;
	this->name = name;
}

int GraphVertex::getID()  const {
	return this->id;
}

void GraphVertex::setID(int newID) {
	this->id = newID;
}

string GraphVertex::getName() const {
	return this->name;
}

bool GraphVertex::operator==(const GraphVertex& other) const {
	return this->name == other.name;
}

bool GraphVertex::operator<(const GraphVertex& other) const {
	if (this->id < other.id)
		return true;
	else
		return false;
}
