#pragma once
#include <string>
#include <unordered_map>

using namespace std;

class DisjointSet
{
private:
	unordered_map<int, int> parent;
	unordered_map<int, int> rank;

public:
	DisjointSet();
	void makeSet(int id);
	int find(int id);
	bool dsUnion(int n1, int n2);
};

