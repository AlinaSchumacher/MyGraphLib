#include "CompleteGraph.h"

CompleteGraph::CompleteGraph(string inputDir) {
	isConnected = true;
	hasNegativeVals = false;

	ifstream file(inputDir);
	file >> vertexCount;

	//adjazenz Matrix nur bei vollstaendigen Graphen
	adjacencyList = vector<vector<int>>(vertexCount, vector<int>(vertexCount, -1));
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
		adjacencyList[from][to] = edgeID;
		adjacencyList[to][from] = edgeID;
	} while (file >> from >> to >> weight);

	//Fill Verices if not all connected
	for (int v = 0; v < vertexCount;v++) {
		if (!vertices[v]) {
			isConnected = false;
			break;
		}
	}
}

WeighedGraph::AdjacencyListInfo CompleteGraph::getAdjacencyListInfo(int vertex, int adjacencyListID) {
	AdjacencyListInfo adj;
	adj.neighbour = adjacencyListID;
	int e = adjacencyList[vertex][adjacencyListID];

	if (e == -1)
		return AdjacencyListInfo(-1, { 0, 0, 0 });

	adj.edge = edges[e];
	adj.neighbour = adjacencyListID;

	return adj;
}

CompleteGraph::HamiltonKreisInfo CompleteGraph::doppelterBaumAlg(int start) {
	HamiltonKreisInfo hk(-1, vector<int>());
	if (start < 0 || start >= vertexCount)
	{
		cerr << "No such Vertex found!" << endl;
		return hk;
	}

	//Init
	vector<bool> visited(vertexCount, false);
	WeighedGraph mst;
	mst.setVertexCount(vertexCount);
	primMST(start, &mst);
	vector<int> path;

	//depth first search
	mst.dfs(start, path, visited);
	path.push_back(path.front());

	int prev = start;
	hk.weight = 0;
	auto mstAdj = mst.getAdjacencyList();

	for (int p : path) {

		hk.path.push_back(p);

		auto [step, edge] = getAdjacencyListInfo(prev, p);
		if (step == -1)
			continue;

		hk.weight += edge.weight;
		prev = p;
	}

	return hk;
}

CompleteGraph::HamiltonKreisInfo CompleteGraph::nearestNeighbourAlg(int start) {
	HamiltonKreisInfo hk(-1, vector<int>());
	if (start < 0 || start >= vertexCount)
	{
		cerr << "No such Vertex found!" << endl;
		return hk;
	}

	//Init
	vector<bool> visited(vertexCount, false);
	hk.weight = 0;
	visited[start] = true;
	int curr = start;
	hk.path.push_back(start);

	//Find nearest Neighbour
	for (int i = 0; i < vertexCount; i++) {
		int nearestEdge = -1;
		int nearestNeighbour = -1;
		double compare = numeric_limits<double>::infinity();

		//Compare adjacent edges
		for (int v = 0; v < adjacencyList[curr].size(); v++) {

			auto [n, e] = getAdjacencyListInfo(curr, v);

			if (n == -1)
				continue;

			if (!visited[v] || (i == vertexCount - 1 && v == start)) {
				double temp = e.weight;
				if (temp < compare) {
					compare = temp;
					nearestEdge = n;
					nearestNeighbour = v;
				}
			}
		}

		//Set Data
		if (nearestEdge != -1)
		{
			visited[nearestNeighbour] = true;
			curr = nearestNeighbour;
			hk.weight += edges[nearestEdge].weight;
			hk.path.push_back(curr);
		}
	}

	return hk;
}

CompleteGraph::HamiltonKreisInfo CompleteGraph::bestPath(CompleteGraph::HamiltonKreisInfo(CompleteGraph::* algorithm)(int)) {
	HamiltonKreisInfo hk(-1, vector<int>());

	hk.weight = numeric_limits<double>::infinity();

	for (int v = 0; v < vertexCount; v++) {
		auto [cmp, tmp_hk] = (this->*algorithm)(v);
		if (cmp < hk.weight) {
			hk.weight = cmp;
			hk.path = tmp_hk;
		}
	}
	return hk;
}

CompleteGraph::HamiltonKreisInfo CompleteGraph::completeSearch(int branchAndBoundID) {
	HamiltonKreisInfo hk(-1, vector<int>());

	//Init
	vector<bool> visited(vertexCount, false);
	hk = nearestNeighbourAlg(0);

	vector<int> path;
	HamiltonKreisInfo tmp_hk = bnbDeepSearch(0, 0, hk.weight, branchAndBoundID, visited, &path);
	if (tmp_hk.weight < hk.weight) {
		hk = tmp_hk;
	}

	return hk;
}

//mehr bnb
CompleteGraph::HamiltonKreisInfo CompleteGraph::bnbDeepSearch(int current, double cWeight, double oWeight, int branchAndBound, vector<bool>& visited, vector<int>* path) {

	//bnb 
	HamiltonKreisInfo hk(cWeight, *path);

	if (branchAndBound > 0)
		switch (branchAndBound) {
		case 1:
			if (cWeight >= oWeight)
				return hk;
			break;
		case 2:
			double dif = vertexCount - path->size();
			hk.weight = cWeight + dif;
			if (hk.weight >= oWeight)
				return hk;
			break;
			//case 3:
			//	auto it = find(visited.begin(), visited.end(), false);
			//	if (it != visited.end()) {
			//		//todo
			//	}
			//	break;
		}

	visited[current] = true;
	path->push_back(current);
	hk.path = *path;
	int start = path->front(), pathSize = path->size();
	hk.weight = oWeight;

	//look at neighbours
	for (int n = 0;n < adjacencyList[current].size(); n++) {
		auto [next, edge] = getAdjacencyListInfo(current, n);

		if (next == -1)
			continue;

		if (!visited[next]) {
			HamiltonKreisInfo cmp_hk = bnbDeepSearch(next, cWeight + edge.weight, hk.weight, branchAndBound, visited, path);

			if (cmp_hk.weight < hk.weight) {
				hk = cmp_hk;
			}
		}

		//end of path
		else if (pathSize == vertexCount && next == start) {
			double totalWeight = edge.weight + cWeight;
			if (totalWeight < oWeight) {
				hk.path.push_back(start);
				hk.weight = totalWeight;
				break;
			}
		}
	}
	visited[current] = false;
	path->pop_back();

	return hk;
}