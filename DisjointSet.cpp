#include "DisjointSet.h"

DisjointSet::DisjointSet() {
	parent = {};
}

void DisjointSet::makeSet(int id) {
	parent[id] = id;
	rank[id] = 0;
}

int DisjointSet::find(int id) {
	if(!parent.empty())
	{
		if (parent[id] == id)
			return id;
		parent[id] = find(parent[id]);
		return parent[id];
	}
	return -1;
}

bool DisjointSet::dsUnion(int n1, int n2) {
	int root1 = find(n1);
	int root2 = find(n2);

	if (root1 != root2) {
		if (rank[root1] < rank[root2])
			parent[root1] = root2;
		else if (rank[root2] < rank[root1])
			parent[root2] = root1;
		else {
			parent[root2] = root1;
			rank[root1]++;
		}
		return true;
	}			
	return false;
}
