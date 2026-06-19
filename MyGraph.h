#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <deque>
#include <limits>
#include "DisjointSet.h"

using namespace std;

struct Edge {
	int from;
	int to;

	bool operator==(const Edge& other) const {
		return this->from == other.from && this->to == other.to;
	}
};

template <typename Edgetype>
class MyGraph
{
protected:
	vector<Edgetype> edges;
	vector<vector<int>> adjacencyList;
	int vertexCount;
	bool isConnected;
	bool hasNegativeVals;

	struct AdjacencyListInfo {
		int neighbour;
		Edgetype edge;
	};

	AdjacencyListInfo getAdjacencyListInfo(int vertex, int adjacencyListID) {
		AdjacencyListInfo adj;
		adj.neighbour = adjacencyListID;
		int e = adjacencyList[vertex][adjacencyListID];

		if (e == -1)
			return { -1, { 0, 0 } };

		adj.edge = edges[e];
		if (vertex == adj.edge.from)
			adj.neighbour = adj.edge.to;
		else
			adj.neighbour = adj.edge.from;

		return adj;
	}

public:
	MyGraph() {
		vertexCount = 0;
		isConnected = true;
		hasNegativeVals = false;
		edges = vector<Edgetype>();
		adjacencyList = vector<vector<int>>();
	}

	MyGraph(string inputDir) {
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
			if (spaces >= 2)
				throw(spaces);
		}
		catch (int input) {
			cerr << "Graph is weighed or wrong format!" << endl;
		}

		//Set Vertices
		istringstream iss(line);
		int from, to;
		double weight;

		iss >> from >> to;
		do
		{

			if (!vertices[from])
				vertices[from] = true;
			if (!vertices[to])
				vertices[to] = true;

			//Set Edges
			edges.push_back({ from, to });

			//Set Adjacency List
			int edgeID = edges.size() - 1;
			adjacencyList[from].push_back(edgeID);
			adjacencyList[to].push_back(edgeID);
		} while (file >> from >> to);

		//all connected?
		for (int v = 0; v < vertexCount;v++) {
			if (!vertices[v]) {
				isConnected = false;
				break;
			}
		}
	}

	void setVertexCount(int count) {
		if (vertexCount == 0) {
			this->vertexCount = count;

			adjacencyList = vector<vector<int>>(vertexCount, vector<int>());
		}
	}

	int getVertexCount() {
		return this->vertexCount;
	}

	vector<vector<int>> getAdjacencyList() {
		return this->adjacencyList;
	}

	int addEdge(const Edgetype edge) {
		for (int e = 0; e < edges.size(); e++) {
			if (edges[e] == edge) {
				return e;
			}
		}

		int v1 = edge.from;
		int v2 = edge.to;

		edges.push_back({ v1, v2 });
		int id = edges.size() - 1;

		this->adjacencyList[v1].push_back(id);
		this->adjacencyList[v2].push_back(id);

		return id;
	}

	//------------------------------------------------------------P1

	bool bfs(int start, vector<int>& pathEdge, int end = -1) {
		if (start < 0 || start >= vertexCount)
		{
			cerr << "No such Vertex found!" << endl;
			return false;
		}

		//init
		queue<int> vertQueue;
		vertQueue.push(start);
		pathEdge[start] = -2;

		while (!vertQueue.empty()) {
			//take first vertex
			int v = vertQueue.front();
			vertQueue.pop();

			for (int n = 0; n < adjacencyList[v].size(); n++) {
				//neighbor not visited, add to queue
				auto next = getAdjacencyListInfo(v, n);

				if (next.neighbour != -1 && pathEdge[next.neighbour] == -1) {
					vertQueue.push(next.neighbour);
					pathEdge[next.neighbour] = adjacencyList[v][n];

					if (next.neighbour == end)
						return true;
				}

			}
		}

		return false;
	}

	int zusammenhagsKomp() {
		//init
		int zsmhgsKmp = 0;
		vector<int> visited(vertexCount, -1);

		for (int v = 0; v < vertexCount; v++) {
			//if vertex not visited, do bfs
			if (visited[v] == -1) {
				bfs(v, visited);
				zsmhgsKmp++;
			}
		}
		return zsmhgsKmp;
	}

	//------------------------------------------------------------P3

	void dfs(int node, vector<int>& path, vector<bool>& visited) {
		visited[node] = true;
		path.push_back(node);

		if (path.size() == vertexCount)
			return;

		deque<AdjacencyListInfo> queue;

		for (int a = 0; a < adjacencyList[node].size(); a++) {
			auto next = getAdjacencyListInfo(node, a);

			if (next.neighbour == -1)
				continue;

			if (!visited[next.neighbour])
				queue.push_back(next);
		}

		for (auto& e : queue) {
			int next = e.neighbour;
			if (!visited[next]) {
				dfs(next, path, visited);
			}
		}
	}
};