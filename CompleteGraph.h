#pragma once
#include "WeighedGraph.h"
#include "MyGraph.h"

using namespace std;

class CompleteGraph : public WeighedGraph
{
protected:
	AdjacencyListInfo getAdjacencyListInfo(int vertex, int adjacencyListID);
public:
	CompleteGraph(string inputDir);
	//------------------------------------------------------------P3
	struct HamiltonKreisInfo {
		double weight;
		vector<int> path;
	};
	HamiltonKreisInfo doppelterBaumAlg(int start);
	HamiltonKreisInfo nearestNeighbourAlg(int start);
	HamiltonKreisInfo bestPath(CompleteGraph::HamiltonKreisInfo(CompleteGraph::* algorithm)(int));
	HamiltonKreisInfo completeSearch(int intelligenceID = 0);
	HamiltonKreisInfo bnbDeepSearch(int current, double cWeight, double oWeight, int intelligence, vector<bool>& visited, vector<int>* path);
};

