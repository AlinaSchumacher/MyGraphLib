#include "WeighedGraph.h"

WeighedGraph::WeighedGraph(string inputDir) {
	isConnected = true;
	hasNegativeVals = false;

	ifstream file(inputDir);
	file >> vertexCount;

	vector<bool> vertices(vertexCount, false);
	adjacencyList = vector<vector<int>>(vertexCount);

	//weighed or not
	string line;
	getline(file >> ws, line);

	try {
		int spaces = count(line.begin(), line.end(), '\t');
		if (spaces < 2)
			throw(spaces);
	}
	catch (int input) {
		cerr << "Graph is not weighed or wrong format!" << endl;
	}

	//Set Vertices
	istringstream iss(line);
	int from, to;
	double weight;

	iss >> from >> to >> weight;
	do
	{
		if (!hasNegativeVals && weight < 0)
			hasNegativeVals = true;

		if (!vertices[from])
			vertices[from] = true;
		if (!vertices[to])
			vertices[to] = true;

		//Set Edges
		edges.push_back({ from, to, weight });

		//Set Adjacency List
		int edgeID = edges.size() - 1;
		adjacencyList[from].push_back(edgeID);
		adjacencyList[to].push_back(edgeID);
	} while (file >> from >> to >> weight);

	//Fill Verices if not all connected
	for (int v = 0; v < vertexCount;v++) {
		if (!vertices[v]) {
			isConnected = false;
		}
	}
}

MyGraph<WeighedEdge>::AdjacencyListInfo WeighedGraph::getAdjacencyListInfo(int vertex, int adjacencyListID) {
	AdjacencyListInfo adj;
	adj.neighbour = adjacencyListID;
	int e = adjacencyList[vertex][adjacencyListID];

	if (e == -1)
		return AdjacencyListInfo(-1, { 0, 0, 0 });

	adj.edge = edges[e];
	if (vertex == adj.edge.from)
		adj.neighbour = adj.edge.to;
	else
		adj.neighbour = adj.edge.from;

	return adj;
}

int WeighedGraph::addEdge(const WeighedEdge edge) {
	for (int e = 0; e < edges.size(); e++) {
		if (edges[e] == edge) {
			return e;
		}
	}

	int v1 = edge.from;
	int v2 = edge.to;
	double weight = edge.weight;

	edges.push_back({ v1, v2, weight });
	int id = edges.size() - 1;

	this->adjacencyList[v1].push_back(id);
	this->adjacencyList[v2].push_back(id);

	return id;
}

//-----------------------------------------------------------------------------------------------------P2

//Helpfunction for edge-priority-queue
struct WeighedGraph::SortByBiggerEdgeWeight
{
	bool operator()(WeighedEdge e1, WeighedEdge e2) const {
		return e2.weight < e1.weight;
	}
};

double WeighedGraph::primMST(int start, WeighedGraph* mst) {
	if (start < 0 || start >= vertexCount)
	{
		cerr << "No such Vertex found!" << endl;
		return -1;
	}

	//Initialisierung
	priority_queue < WeighedEdge, vector<WeighedEdge>, WeighedGraph::SortByBiggerEdgeWeight > prio;
	int pred = start;
	double weight = 0;
	vector<bool> visited(vertexCount, false);
	visited[start] = true;

	do {
		//Find new edges
		for (int v = 0;v < adjacencyList[pred].size(); v++) {

			auto [curr, edge] = getAdjacencyListInfo(pred, v);

			if (curr == -1)
				continue;

			if (!visited[curr]) {
				prio.push(edge);
			}
		}

		//Decide which edge to continue
		WeighedEdge cheapest = { -1, -1, -1 };
		while (cheapest.from == -1 && !prio.empty())
		{
			WeighedEdge tmp_e = prio.top();
			int tmp_v = tmp_e.from;

			if (visited[tmp_v]) {
				tmp_v = tmp_e.to;
				if (visited[tmp_v]) {
					tmp_v = -1;
				}
			}

			if (tmp_v != -1) {
				pred = tmp_v;
				cheapest = tmp_e;
			}
			prio.pop();
		}

		if (cheapest.from != -1) {
			visited[pred] = true;
			if (mst)
				mst->addEdge(cheapest);
			weight += cheapest.weight;
		}
	} while (!prio.empty());

	return weight;
}

//Helpfunction for list sort
struct WeighedGraph::SortBySmallerEdgeWeight
{
	bool operator()(WeighedEdge e1, WeighedEdge e2) {
		return e1 < e2;
	}
};

double WeighedGraph::kruskalMST(WeighedGraph* mst) {

	//Init
	double weight = 0;
	DisjointSet ds = DisjointSet();
	deque<WeighedEdge> prio;

	//Make disjoint sets for all Vertices
	for (int i = 0; i < vertexCount; i++) {
		ds.makeSet(i);
	}

	//Make Sorted List of Edges
	for (auto& e : edges) {
		prio.push_back(e);
	}
	sort(prio.begin(), prio.end(), WeighedGraph::SortBySmallerEdgeWeight());

	while (!prio.empty()) {

		//take next smallest edge
		WeighedEdge e = prio.front();
		prio.pop_front();

		//if disjoint, save edge and unite
		int k1 = e.from, k2 = e.to;
		if (ds.dsUnion(k1, k2)) {
			if (mst)
				mst->addEdge(e);
			weight += e.weight;
		}
	}
	return weight;
}

//-----------------------------------------------------------------------------------------------------P4

double WeighedGraph::dijkstraAlg(int start, int end) {
	if (start < 0 || start >= vertexCount)
	{
		cerr << "No such Vertex found!" << endl;
		return -1;
	}
	if (!isConnected) {
		cerr << "Graph is not connected!" << endl;
		return -1;
	}
	if (hasNegativeVals) {
		cerr << "Graph has negative Vals!" << endl;
		return -1;
	}

	//Init
	vector<int> pred(vertexCount, -1);
	pred[start] = start;
	vector<double> dist(vertexCount, numeric_limits<double>::infinity());
	dist[start] = 0;
	vector<bool> finished(vertexCount, false);

	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> prio;
	prio.push({ 0, start });

	//Vertices pruefen
	while (!prio.empty()) {
		auto p = prio.top();
		prio.pop();
		int v = p.second;

		if (finished[v])
			continue;

		//Nachbarn kennenlernen
		for (int n = 0; n < adjacencyList[v].size(); n++) {
			auto [next, edge] = getAdjacencyListInfo(v, n);

			if (next == -1 || finished[next])
				continue;

			double d = dist[v] + edge.weight, dNext = dist[next];

			//update distances
			if (d < dNext) {
				dist[next] = d;
				pred[next] = v;
				prio.push({ d, next });
			}
		}

		finished[v] = true;
	}
	return dist[end];
}

double WeighedGraph::mooreBellmanFordAlg(int start, int end) {
	if (start < 0 || start >= vertexCount)
	{
		cerr << "No such Vertex found!" << endl;
		return -1;
	}

	//Init
	vector<int> pred(vertexCount, -1);
	pred[start] = start;
	vector<double> dist(vertexCount, numeric_limits<double>::infinity());
	dist[start] = 0;

	//V - 1 durchlaeufe
	for (int i = 0; i < vertexCount - 1; i++) {
		bool change = false;

		//Alle Kanten Pruefen
		for (int e = 0; e < edges.size(); e++) {
			WeighedEdge edge = edges[e];
			int from = edge.from, to = edge.to;
			double weight = edge.weight;

			double w = dist[from] + weight;
			if (w < dist[to]) {
				dist[to] = w;
				pred[to] = from;

				change = true;
			}

			w = dist[to] + weight;
			if (w < dist[from]) {
				dist[from] = w;
				pred[from] = to;

				change = true;
			}
		}

		//early stop
		if (!change)
			return dist[end];
	}

	for (int e = 0; e < edges.size(); e++) {
		WeighedEdge edge = edges[e];
		int from = edge.from, to = edge.to;
		double weight = edge.weight;

		if (double w = dist[from] + weight < dist[to])
			return -1;

		if (double w = dist[to] + weight < dist[from])
			return -1;
	}

	return dist[end];
}
