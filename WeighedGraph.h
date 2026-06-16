#pragma once

#include "MyGraph.h"

using namespace std;

struct WeighedEdge : Edge {
	double weight;

	bool operator==(const WeighedEdge& other) const {
		return this->from == other.from && this->to == other.to && this->weight == other.weight;
	}

	bool operator<(const WeighedEdge& other) const {
		return this->weight < other.weight;
	}
};

class WeighedGraph : public MyGraph<WeighedEdge>
{
protected:
	struct SortByBiggerEdgeWeight;
	struct SortBySmallerEdgeWeight;
	AdjacencyListInfo getAdjacencyListInfo(int vertex, int adjacencyListID);
public:
	WeighedGraph(){}
	WeighedGraph(string inputDir);
	int addEdge(const WeighedEdge edge);
	//------------------------------------------------------------P2
	double primMST(int start, WeighedGraph* mst = nullptr);
	double kruskalMST(WeighedGraph* mst = nullptr);
	//------------------------------------------------------------P4
	double dijkstraAlg(int start, int end);
	double mooreBellmanFordAlg(int start, int end);
};

