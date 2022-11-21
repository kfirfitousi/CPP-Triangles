#include "ListGraph.h"

ListGraph::ListGraph(const unsigned int n) : n(n), m(0)
{
	if (n < 0)
		throw std::invalid_argument("n can not be negative");

	V = new std::vector<std::list<int>>(n);
}

ListGraph::ListGraph(const ListGraph& L) : n(L.n), m(L.m)
{
	V = new std::vector<std::list<int>>(n);
	for (unsigned int i = 1; i <= n; i++)
	{
		(*V)[i-1] = (*L.V)[i-1];
	}
}

void ListGraph::AddEdge(const unsigned int u, const unsigned int v)
{
	if (u<1 || u>n || v<1 || v>n)
		throw std::out_of_range("u and v should be in range [1,n]");

	(*V)[u-1].push_back(v);
	m++;
}

void ListGraph::DeleteEgde(const unsigned int u, const unsigned int v)
{
	if (u<1 || u>n || v<1 || v>n)
		throw std::out_of_range("u and v should be in range [1,n]");

	(*V)[u-1].remove(v);
	m--;
}

bool ListGraph::AreNeighbors(const unsigned int u, const unsigned int v) const
{
	if (u<1 || u>n || v<1 || v>n)
		throw std::out_of_range("u and v should be in range [1,n]");

	return std::find((*V)[u-1].begin(), (*V)[u-1].end(), v) != (*V)[u-1].end();
}

unsigned int ListGraph::Deg(const unsigned int v) const
{
	if (v<1 || v>n)
		throw std::out_of_range("v should be in range [1,n]");

	int deg = (int)NeighborList(v).size(); // outDegree

	for (unsigned int u = 1; u <= n; u++) // inDegree
	{
		auto AdjU = NeighborList(u);
		if (std::find(AdjU.begin(), AdjU.end(), v) != AdjU.end())
		{
			deg++;
		}
	}

	return deg;
}

std::vector<int>* ListGraph::Degree() const
{
	auto deg = new std::vector<int>(n);

	for (unsigned int i = 1; i <= n; i++)
	{
		(*deg)[i-1] = Deg(i);
	}

	return deg;
}

std::list<int>& ListGraph::NeighborList(const unsigned int v) const
{
	if (v<1 || v>n)
		throw std::out_of_range("v should be in range [1,n]");

	return (*V)[v-1];
}
