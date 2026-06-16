#pragma once

#include <iostream>
#include"GraphVertex.h"

using namespace std;

class GraphEdge
{
	private:
		GraphVertex* v1;
		GraphVertex* v2;
		float weight;
public:
	GraphEdge(GraphVertex* from, GraphVertex* to, float weight = 0);
	//-------------------------------------------------------------- Getters
	GraphVertex* getV1() const;
	GraphVertex* getV2() const;
	GraphVertex* getOther(int vertex) const;
	float getWeight() const;
	void print() const;
	//-------------------------------------------------------------- Operators
	bool operator<(const GraphEdge& other) const;
	bool operator==(const GraphEdge& other) const;
	bool operator!=(const GraphEdge& other) const;
};

