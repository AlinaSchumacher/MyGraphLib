#pragma once

#include "MyGraph.h"

using namespace std;

struct CostEdge : public Edge {
	double cost;
	double capacity;

	bool operator==(const CostEdge& other) const {
		return this->from == other.from && this->to == other.to && this->capacity == other.capacity && this->cost == other.cost;
	}
};

class CostGraph : MyGraph<CostEdge>
{
protected:
	vector<double> balances;
	AdjacencyListInfo getAdjacencyListInfo(int vertex, int adjacencyListID);
public:
	CostGraph() {}
	CostGraph(string inputDir);
	int addEdge(const CostEdge edge);
	//------------------------------------------------------------P6
	double CycleCancelingAlg();
};

