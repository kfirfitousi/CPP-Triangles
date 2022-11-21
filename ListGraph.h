#pragma once
#include <iostream>
#include <list>
#include <vector>
#include <exception>
#include <algorithm>

class ListGraph
{
public:
	const unsigned int n;
	unsigned int m;
	ListGraph(const unsigned int n);
	ListGraph(const ListGraph& L);
	~ListGraph() { if (V) delete V; };
	void AddEdge(const unsigned int u, const unsigned int v);
	void DeleteEgde(const unsigned int u, const unsigned int v);
	bool AreNeighbors(const unsigned int u, const unsigned int v) const;
	unsigned int Deg(const unsigned int v) const;
	std::vector<int>* Degree() const;
	std::list<int>& NeighborList(const unsigned int v) const;
private:
	std::vector<std::list<int>>* V;
};