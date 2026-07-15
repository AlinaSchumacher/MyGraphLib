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

/*
* Eingabe:
*	int start:					Ausgangs-vertex (optional, keine Angabe = -1)
*	int end:					End-vertex (optional, falls speziell gesucht; keine Angabe = -1)
*	vector<double>* distances:	Liste der Erreichbarkeits-kosten aller Vertices (optional, keine Angabe = nullptr)
*	vector<int>* path:
*								falls zykel vorhanden:			kanten des negativen Zykels (optional, keine Angabe = nullptr)
*								sonst:	falls end vorhanden:	kanten des Pfades von end zu start (optional, keine Angabe = nullptr)
* Ausgabe:
*	true:						kein Zykel/ end gefunden
*	false:						Zykel gefunden
*/
bool CostGraph::mooreBellmanFordAlg(int start, int end, vector<double>* distances, vector<int>* path) {
	//Init
	vector<int> pred(vertexCount, -1);
	vector<double> dist = vector<double>(vertexCount, (start != -1) ? numeric_limits<double>::infinity() : 0);
	bool finish = false;

	if (start != -1)
	{
		pred[start] = -1;
		dist[start] = 0;
	}

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
				pred[to] = e;
				dist[to] = c;

				change = true;
			}
		}

		//early stop
		if (!change)
		{
			finish = true;
			break;
		}
	}

	if (distances)
		*distances = dist;

	if (!finish)
		for (int e = 0; e < edges.size(); e++) {
			CostEdge edge = edges[e];
			int from = edge.from, to = edge.to;
			double cost = edge.cost;
			double w = dist[from] + cost;

			if (w < dist[to]) {
				int x = to;
				for (int i = 0; i < vertexCount; i++) {
					//x = pred[x];
					x = edges[pred[x]].from;
				}
				vector<int> z = { pred[x] };
				int current = edges[pred[x]].from;
				while (current != x) {
					z.push_back(pred[current]);
					current = edges[pred[current]].from;
				}

				//return cycle
				if (path)
					*path = z;
				return false;
			}
		}

	if (end != -1 && path) {
		if (dist[end] == numeric_limits<double>::infinity())
			return false;

		vector<int> p = { pred[end] };
		int current = edges[pred[end]].from;
		while (current != start) {
			p.push_back(pred[current]);
			current = edges[pred[current]].from;
		}
		*path = p;
	}
	//return path
	return true;
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

	double maxFlow = 0;
	vector<double> flow(edges.size(), 0);

	CostGraph* residualGraph = makeResidualGraph(flow);
	vector<int> pathEdge(vertexCount, -1);

	//st-Weg in p, solange es einen gibt
	while (residualGraph->bfs(start, pathEdge, end)) {

		double minFlow = numeric_limits<double>::infinity();
		vector<tuple<int, int>> path;

		for (int p = end; p != start; p = residualGraph->edges[pathEdge[p]].from) {
			CostEdge edge = residualGraph->edges[pathEdge[p]];
			tuple<int, int> edgeID = make_tuple(-1, 0);

			//find the corresponding edge in current Graph
			// normal flow edge ids
			for (auto a : adjacencyList[edge.from]) {
				if (edges[a].to == p)
					edgeID = make_tuple(a, 1);
			}

			// residual edge ids
			if (get<1>(edgeID) == -1) {
				for (auto a : adjacencyList[edge.to]) {
					if (edges[a].to == p)
						edgeID = make_tuple(a, -1);
				}
			}

			path.push_back(edgeID);

			//find smallest capacity in path
			if (edge.capacity < minFlow)
				minFlow = edge.capacity;
		}

		for (auto s : path) {
			int id, res;
			tie(id, res) = s;
			if (res > 0)
				flow[id] += minFlow;
			else if (res < 0)
				flow[id] -= minFlow;
			else
				return -1;
		}

		maxFlow += minFlow;
		residualGraph = makeResidualGraph(flow);
		std::fill(pathEdge.begin(), pathEdge.end(), -1);
	}
	if (mflow)
	{
		*mflow = flow;
	}
	return maxFlow;
}

vector<double> CostGraph::findBFlow()
{
	vector<double> flow;

	int source = vertexCount;
	int sink = vertexCount + 1;

	CostGraph g;

	g.setVertexCount(vertexCount + 2);
	g.addBalances(balances);

	// ursprüngliche Kanten übernehmen
	for (const auto& e : edges)
		g.addEdge(e);

	double supply = 0, demand = 0;

	// Super-Quelle und Super-Senke
	for (int v = 0; v < vertexCount; ++v)
	{
		if (balances[v] > 0)
		{
			g.addEdge({ source, v, 0, balances[v] });
			supply += balances[v];
		}
		else if (balances[v] < 0)
		{
			g.addEdge({ v, sink, 0, -balances[v] });
			demand -= balances[v];
		}
	}

	// b(s) == b(t)?
	if (supply != demand)
	{
		cerr << "Kein zulässiger b-Flow vorhanden." << endl;
		return {};
	}

	// Maxflow berechnen
	double maxFlow = g.EdmondsKarpAlg(source, sink, &flow);

	// b' == b?
	if (maxFlow != demand) {
		cerr << "Kein zulässiger b-Flow vorhanden." << endl;
		return {};
	}

	//trim excess
	for (int f = flow.size(); f > edges.size(); f--) {
		flow.pop_back();
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

		if (residualGraph->mooreBellmanFordAlg(-1, -1, nullptr, &cycle))
			return flow;

		// kleinste Restkapazität auf dem Zyklus
		double delta = numeric_limits<double>::infinity();

		vector<int> edgeIDs;

		for (int i = cycle.size() - 1; i >= 0; i--)
		{
			edgeIDs.push_back(cycle[i]);

			delta = min(delta, residualGraph->edges[cycle[i]].capacity);
		}

		// Flow anpassen
		for (int edgeID : cycle)
		{
			CostEdge edge = residualGraph->edges[edgeID];
			bool found = false;

			// Vorwaertskante?
			for (int i = 0; i < edges.size(); i++)
			{
				if (edges[i].from == edge.from &&
					edges[i].to == edge.to &&
					edges[i].cost == edge.cost)
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
					if (edges[i].from == edge.to &&
						edges[i].to == edge.from &&
						edges[i].cost == -edge.cost)
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

vector<double> CostGraph::successiveShortestPathAlg() {
	vector<double> b(vertexCount, 0);
	vector<double> flow(edges.size(), 0);

	// satisfy negative edges
	if (hasNegativeVals)
		for (int e = 0; e < edges.size(); e++) {
			CostEdge edge = edges[e];

			if (edge.cost < 0)
			{
				b[edge.from] += edge.capacity;
				b[edge.to] -= edge.capacity;
				flow[e] = edge.capacity;
			}
		}

	int source = vertexCount;
	deque<int> sinks;

	CostGraph g;

	g.setVertexCount(vertexCount + 1);
	g.addBalances(balances);
	g.balances.push_back(0);
	b.push_back(0);

	// ursprüngliche Kanten übernehmen
	for (const auto& e : edges)
		g.addEdge(e);

	double demand = 0;

	for (int v = 0; v < vertexCount; ++v)
	{
		// Super-Source
		if (balances[v] - b[v] > 0)
		{
			g.addEdge({ source, v, 0, balances[v] - b[v] });
			flow.push_back(0);
			g.balances[source] += balances[v] - b[v];
		}
		// remember all sinks
		else if (balances[v] - b[v] < 0)
		{
			sinks.push_back(v);
			demand += abs(balances[v] - b[v]);
		}
	}

	if (g.balances[source] != demand)
		return {};

	do {
		int sink = sinks.front();
		sinks.pop_front();

		// test if all sinks are reachable
		vector<int> pathEdge(g.vertexCount, -1);
		CostGraph* residualGraph = g.makeResidualGraph(flow);
		residualGraph->bfs(source, pathEdge, sink);

		vector<int> path;
		// sink not reachable
		if (pathEdge[sink] == -1)
			return { -1 };
		// sink reachable
		else {
			//s,t-Path
			if (!residualGraph->mooreBellmanFordAlg(source, sink, nullptr, &path))
				return {};
			double gamma = numeric_limits<double>::infinity();
			vector<tuple<int, int>> gPath;

			for (int p : path) {
				//Find corresponding edges
				CostEdge edge = residualGraph->edges[p];
				bool found = false;

				for (auto a : g.adjacencyList[edge.from])
				{
					if (g.edges[a].to == edge.to)
					{
						gPath.push_back(make_tuple(a, 1));
						found = true;
						break;
					}
				}

				if (!found)
				{
					for (auto a : g.adjacencyList[edge.to])
					{
						if (g.edges[a].to == edge.from)
						{
							gPath.push_back(make_tuple(a, -1));
							break;
						}
					}
				}

				gamma = min(gamma, edge.capacity);
			}

			gamma = min(gamma, min(g.balances[source] - b[source], abs(g.balances[sink] - b[sink])));

			if (gamma == 0)
				break;

			b[source] += gamma;
			b[sink] -= gamma;

			for (auto p : gPath) {
				int vert = get<0>(p);
				flow[vert] += gamma * get<1>(p);
			}
		}

		if (balances[sink] != b[sink])
			sinks.push_back(sink);

	} while (!sinks.empty() && g.balances[source] != b[source]);

	//clean up flow
	for (int i = flow.size(); i > edges.size(); i--) {
		flow.pop_back();
	}

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