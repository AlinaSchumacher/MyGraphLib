#pragma once
#include <limits>
#include <string>

using namespace std;

class GraphVertex
{
private:
	int id;
	string name;

public:
	GraphVertex(string name, int id= -1);
	//-------------------------------------------------------------- Getters
	int getID() const;
	string getName() const;
	//-------------------------------------------------------------- Setters
	void setID(int newID);
	//-------------------------------------------------------------- Operators
	bool operator==(const GraphVertex& other) const;
	bool operator<(const GraphVertex& other) const;
};

