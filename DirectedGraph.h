#pragma once

#include "WeighedGraph.h"

using namespace std;

class DirectedGraph : public WeighedGraph
{
protected:
	AdjacencyListInfo getAdjacencyListInfo(int vertex, int adjacencyListID);
public:
	DirectedGraph(string inputDir);
	int addEdge(const WeighedEdge edge);
	//------------------------------------------------------------P4
	double dijkstraAlg(int start, int end);
	double mooreBellmanFordAlg(int start, int end);
};

