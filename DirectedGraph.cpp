#include "DirectedGraph.h"

DirectedGraph::DirectedGraph() {
	vertexCount = 0;
	isConnected = true;
	hasNegativeVals = false;
	edges = vector<WeighedEdge>();
	adjacencyList = vector<vector<int>>();
}

DirectedGraph::DirectedGraph(string inputDir) {
	isConnected = true;
	hasNegativeVals = false;

	ifstream file(inputDir);
	file >> vertexCount;

	adjacencyList = vector<vector<int>>(vertexCount);
	vector<bool> vertices(vertexCount, false);

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
	} while (file >> from >> to >> weight);

	//Fill Verices if not all connected
	for (int v = 0; v < vertexCount;v++) {
		if (!vertices[v]) {
			isConnected = false;
			break;
		}
	}
}

MyGraph<WeighedEdge>::AdjacencyListInfo DirectedGraph::getAdjacencyListInfo(int vertex, int adjacencyListID) {
	AdjacencyListInfo adj;
	adj.neighbour = adjacencyListID;
	int e = adjacencyList[vertex][adjacencyListID];

	if (e == -1)
		return AdjacencyListInfo(-1, { 0, 0, 0 });

	adj.edge = edges[e];
	adj.neighbour = adj.edge.to;

	return adj;
}

int DirectedGraph::addEdge(const WeighedEdge edge) {
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

	return id;
}

int DirectedGraph::addEdge(WeighedEdge* edge) {
	for (int e = 0; e < edges.size(); e++) {
		if (edges[e] == *edge) {
			return e;
		}
	}

	edges.push_back(*edge);
	int id = edges.size() - 1;

	this->adjacencyList[edge->from].push_back(id);

	return id;
}

//-----------------------------------------------------------------------------------------------------P4

double DirectedGraph::dijkstraAlg(int start, int end) {
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

double DirectedGraph::mooreBellmanFordAlg(int start, int end) {
	if (start < 0 || start >= vertexCount)
	{
		cerr << "No such Vertex found!" << endl;
		return -1;
	}
	if (!isConnected) {
		cerr << "Graph is not connected!" << endl;
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
	}

	return dist[end];
}

//-----------------------------------------------------------------------------------------------------P5

DirectedGraph* DirectedGraph::makeResidualGraph(vector<double> flow) {
	if (flow.size() != edges.size()) {
		cerr << "Flow doesn't fit to Graph!" << endl;
		return nullptr;
	}

	DirectedGraph* residualGraph = new DirectedGraph();
	residualGraph->setVertexCount(vertexCount);

	for (int e = 0; e < edges.size(); e++) {
		WeighedEdge edge = edges[e];
		double backward = flow[e], forward = edge.weight - backward;

		if (forward != 0)
			residualGraph->addEdge({ edge.from, edge.to, forward });
		if (backward != 0)
			residualGraph->addEdge({ edge.to, edge.from, backward });
	}

	return residualGraph;
}

double DirectedGraph::EdmondsKarpAlg(int start, int end) {
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


	DirectedGraph* residualGraph = makeResidualGraph(flow);
}