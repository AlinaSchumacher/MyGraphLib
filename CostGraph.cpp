#include "CostGraph.h"

CostGraph::CostGraph() {
	vertexCount = 0;
	isConnected = true;
	hasNegativeVals = false;
	edges = vector<CostEdge>();
	balances = vector<double>();
	adjacencyList = vector<vector<int>>();
}

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

void CostGraph::addBalances(const vector<double>& balances) {
	this->balances = balances;
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

vector<int> CostGraph::mooreBellmanFordAlg() {
	if (!isConnected) {
		cerr << "Graph is not connected!" << endl;
		return {};
	}

	//Init
	vector<int> pred(vertexCount, -1);
	vector<double> dist(vertexCount, 0);

	//V - 1 durchlaeufe
	for (int i = 0; i < vertexCount - 1; i++) {
		bool change = false;

		//Alle Kanten Pruefen
		for (int e = 0; e < edges.size(); e++) {
			CostEdge edge = edges[e];
			int from = edge.from, to = edge.to;
			double cost = edge.cost;

			double c = dist[from] + cost;
			if (c < dist[to]) {
				dist[to] = c;
				pred[to] = from;

				change = true;
			}
		}
	}

	for (int e = 0; e < edges.size(); e++) {
		CostEdge edge = edges[e];
		int from = edge.from, to = edge.to;
		double cost = edge.cost;
		double w = dist[from] + cost;

		if (w < dist[to]) {
			int x = to;
			for (int i = 0; i < vertexCount; i++) {
				x = pred[x];
			}
			int start = x;
			vector<int> z = { start };
			int current = pred[start];
			while (current != start) {
				z.push_back(current);
				current = pred[current];
			}
			z.push_back(start);
			return z;
		}
	}

	return {};
}

CostGraph* CostGraph::makeResidualGraph(vector<double> flow) {
	if (flow.size() != edges.size()) {
		cerr << "Flow doesn't fit to Graph!" << endl;
		return nullptr;
	}

	CostGraph* residualGraph = new CostGraph();
	residualGraph->setVertexCount(vertexCount);
	residualGraph->addBalances(this->balances);

	for (int e = 0; e < edges.size(); e++) {
		CostEdge edge = edges[e];
		double backward = flow[e], forward = edge.capacity - backward;

		if (forward != 0)
			residualGraph->addEdge({ edge.from, edge.to, edge.cost, forward });
		if (backward != 0)
			residualGraph->addEdge({ edge.to, edge.from, -edge.cost, backward });
	}

	return residualGraph;
}

double CostGraph::EdmondsKarpAlg(int start, int end, vector<double>* mflow) {
	if (start < 0 || start >= vertexCount || end < 0 || end >= vertexCount)
	{
		cerr << "No such Vertex found!" << endl;
		return -1;
	}
	if (!isConnected) {
		cerr << "Graph is not connected!" << endl;
		return -1;
	}

	double maxFlow = 0;
	vector<double> flow(edges.size(), 0);

	CostGraph* residualGraph = makeResidualGraph(flow);
	vector<int> pathEdge(vertexCount, -1);

	//st-Weg in p, solange es einen gibt
	while (residualGraph->bfs(start, pathEdge, end)) {

		double minFlow = numeric_limits<double>::infinity();
		vector<int> path;

		for (int p = end; p != start; p = residualGraph->edges[pathEdge[p]].from) {
			CostEdge edge = residualGraph->edges[pathEdge[p]];
			int edgeID = -1;

			//find the corresponding edge in current Graph
			for (auto a : adjacencyList[edge.from]) {
				if (edges[a].to == p)
					edgeID = a;
			}
			if (edgeID == -1) {
				for (auto a : adjacencyList[edge.to]) {
					if (edges[a].to == p)
						edgeID = -a;
				}
			}
			path.push_back(edgeID);

			//find smallest capacity in path
			if (edge.capacity < minFlow)
				minFlow = edge.capacity;
		}

		for (int s : path) {
			if (s >= 0)
				flow[s] += minFlow;
			else
				flow[-s] -= minFlow;
		}

		maxFlow += minFlow;
		residualGraph = makeResidualGraph(flow);
		fill(pathEdge.begin(), pathEdge.end(), -1);
	}
	if (mflow)
	{
		for (int f = 0; f < mflow->size(); f++) {
			mflow->at(f) = flow[f];
		}
	}
	return maxFlow;
}

vector<double> CostGraph::findBFlow()
{
	vector<double> flow(edges.size(), 0);

	int source = vertexCount;
	int sink = vertexCount + 1;

	CostGraph g;

	g.setVertexCount(vertexCount + 2);

	// ursprüngliche Kanten übernehmen
	for (const auto& e : edges)
		g.addEdge(e);

	double demand = 0;

	// Super-Quelle und Super-Senke
	for (int v = 0; v < vertexCount; ++v)
	{
		if (balances[v] > 0)
		{
			g.addEdge({ source, v, 0, balances[v] });
			demand += balances[v];
		}
		else if (balances[v] < 0)
		{
			g.addEdge({ v, sink, 0, -balances[v] });
		}
	}

	// Maxflow berechnen
	double maxFlow = g.EdmondsKarpAlg(source, sink, &flow);

	if (maxFlow != demand)
	{
		cerr << "Kein zulässiger b-Flow vorhanden." << endl;
		return {};
	}

	return flow;
}

vector<double> CostGraph::CycleCancelingAlg() {
	//is b-flow possible?
	double bSum = 0;
	for (auto b : balances) {
		bSum += b;
	}

	if (bSum != 0)
		return {};

	vector<double> flow = findBFlow();
	if (flow.empty())
		return {};

	vector<int> cycle;

	do {
		CostGraph* residualGraph = makeResidualGraph(flow);
		cycle = residualGraph->mooreBellmanFordAlg();

		if (cycle.empty())
			return flow;

		// kleinste Restkapazität auf dem Zyklus
		double delta = numeric_limits<double>::infinity();

		vector<int> edgeIDs;

		for (int i = cycle.size() - 1; i > 0 ; i--)
		{
			int u = cycle[i];
			int v = cycle[i - 1];

			int edgeID = -1;

			for (int e : residualGraph->adjacencyList[u])
			{
				if (residualGraph->edges[e].to == v)
				{
					edgeID = e;
					break;
				}
			}

			if (edgeID == -1)
			{
				cerr << "Cycle edge not found!" << endl;
				return {};
			}

			edgeIDs.push_back(edgeID);

			delta = min(delta, residualGraph->edges[edgeID].capacity);
		}

		// Flow anpassen
		for (int rEdgeID : edgeIDs)
		{
			CostEdge rEdge = residualGraph->edges[rEdgeID];

			bool found = false;

			// Vorwaertskante?
			for (int i = 0; i < edges.size(); i++)
			{
				if (edges[i].from == rEdge.from &&
					edges[i].to == rEdge.to &&
					edges[i].cost == rEdge.cost)
				{
					flow[i] += delta;
					found = true;
					break;
				}
			}

			if (!found)
			{
				// Rückwärtskante
				for (int i = 0; i < edges.size(); i++)
				{
					if (edges[i].from == rEdge.to &&
						edges[i].to == rEdge.from &&
						edges[i].cost == -rEdge.cost)
					{
						flow[i] -= delta;
						break;
					}
				}
			}
		}
	} while (!cycle.empty());

	return flow;
}

double CostGraph::getCost(vector<double>& flow) {
	if (flow.size() != edges.size())
	{
		cerr << "Flow doesn't fit to graph!" << endl;
		return -1;
	}

	double cost = 0;

	for (int i = 0; i < edges.size(); i++)
	{
		cost += flow[i] * edges[i].cost;
	}

	return cost;
}
