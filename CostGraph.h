#pragma once

#include "MyGraph.h"

using namespace std;

struct CostEdge : public Edge {
	double cost;
	double capacity;

	bool operator==(const CostEdge& other) const {
		return this->from == other.from && this->to == other.to && this->cost == other.cost;
	}
};

class CostGraph : MyGraph<CostEdge>
{
protected:
	vector<double> balances;
	AdjacencyListInfo getAdjacencyListInfo(int vertex, int adjacencyListID);
public:
	CostGraph();
	CostGraph(string inputDir);
	int addEdge(const CostEdge edge);
	void addBalances(const vector<double>& balances);
	//------------------------------------------------------------P6
	vector<int> mooreBellmanFordAlg();
	CostGraph* makeResidualGraph(vector<double> flow);
	double EdmondsKarpAlg(int start, int end, vector<double>* flow = nullptr);
	vector<double> findBFlow();
	vector<double> CycleCancelingAlg();
	double getCost(vector<double>& flow);
};

