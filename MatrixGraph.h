#pragma once
#include <iostream>
#include <vector>
#include <exception>

class MatrixGraph
{
public:
	using Matrix = std::vector<std::vector<int>>;
	const unsigned int n;
	MatrixGraph(const unsigned int n);
	~MatrixGraph() { if (A) delete A; };
	void AddEdge(const unsigned int u, const unsigned int v);
	void DeleteEgde(const unsigned int u, const unsigned int v);
	bool AreNeighbors(const unsigned int u, const unsigned int v) const;
	int& operator()(const unsigned int u, const unsigned int v);
	Matrix* Matrix3() const;
private:
	Matrix* A;
};