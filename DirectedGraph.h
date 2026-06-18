#pragma once

#include "WeighedGraph.h"

using namespace std;

class DirectedGraph : public WeighedGraph
{
protected:
	AdjacencyListInfo getAdjacencyListInfo(int vertex, int adjacencyListID);
public:
	DirectedGraph();
	DirectedGraph(string inputDir);
	int addEdge(const WeighedEdge edge);
	int addEdge(WeighedEdge* edge);
	//------------------------------------------------------------P4
	double dijkstraAlg(int start, int end);
	double mooreBellmanFordAlg(int start, int end);
	//------------------------------------------------------------P5
	DirectedGraph* makeResidualGraph(vector<double> flow);
	bool stFlowBFS(int start, int end);
	double EdmondsKarpAlg(int start, int end);
};

