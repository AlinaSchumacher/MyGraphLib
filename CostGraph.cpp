#include "CostGraph.h"

CostGraph::CostGraph(string inputDir) {
	isConnected = true;
	hasNegativeVals = false;

	ifstream file(inputDir);
	file >> vertexCount;

	vector<bool> vertices(vertexCount, false);
	this->balances = vector<double>(vertexCount, 0);
	adjacencyList = vector<vector<int>>(vertexCount);

	string line;

	for (int i = 0; i < vertexCount; i++)
	{
		getline(file >> ws, line);
		istringstream iss(line);
		iss >> balances[i];
	}

	//weighed or not
	getline(file >> ws, line);

	try {
		int spaces = count(line.begin(), line.end(), '\t');
		if (spaces < 3)
			throw(spaces);
	}
	catch (int input) {
		cerr << "Graph is not weighed or wrong format!" << endl;
	}

	//Set Vertices
	istringstream iss(line);
	int from, to;
	double capacity, cost;

	iss >> from >> to >> cost >> capacity;
	do
	{
		if (!hasNegativeVals && cost < 0)
			hasNegativeVals = true;

		if (!vertices[from])
			vertices[from] = true;
		if (!vertices[to])
			vertices[to] = true;

		//Set Edges
		edges.push_back({ from, to, cost, capacity });

		//Set Adjacency List
		int edgeID = edges.size() - 1;
		adjacencyList[from].push_back(edgeID);
	} while (file >> from >> to >> cost >> capacity);

	//Fill Verices if not all connected
	for (int v = 0; v < vertexCount;v++) {
		if (!vertices[v]) {
			isConnected = false;
			break;
		}
	}
}

MyGraph<CostEdge>::AdjacencyListInfo CostGraph::getAdjacencyListInfo(int vertex, int adjacencyListID) {
	AdjacencyListInfo adj;
	adj.neighbour = adjacencyListID;
	int e = adjacencyList[vertex][adjacencyListID];

	if (e == -1)
		return AdjacencyListInfo(-1, { 0, 0, 0, 0 });

	adj.edge = edges[e];
	adj.neighbour = adj.edge.to;

	return adj;
}

int CostGraph::addEdge(const CostEdge edge) {
	for (int e = 0; e < edges.size(); e++) {
		if (edges[e] == edge) {
			return e;
		}
	}

	int v1 = edge.from;
	int v2 = edge.to;
	double cost = edge.cost;
	double capacity = edge.capacity;

	edges.push_back({ v1, v2, cost, capacity });
	int id = edges.size() - 1;

	this->adjacencyList[v1].push_back(id);

	return id;
}

//-----------------------------------------------------------------------------------------------------P6

double CostGraph::CycleCancelingAlg() {
	//is b-flow possible?
	double bSum = 0;
	for (auto b : balances) {
		bSum += b;
	}

	if (bSum != 0)
		return -1;

	return 3;
}
