#include "MatrixGraph.h"

MatrixGraph::MatrixGraph(const unsigned int n) : n(n)
{
	if (n < 0)
		throw std::invalid_argument("n can not be negative");

	A = new Matrix(n, std::vector<int>(n, 0)); // create n*n matrix and initialize cells to 0
}

void MatrixGraph::AddEdge(const unsigned int u, const unsigned int v)
{
	if (u<1 || u>n || v<1 || v>n)
		throw std::out_of_range("u and v should be in range [1,n]");

	(*A)[u-1][v-1] = 1;
}

void MatrixGraph::DeleteEgde(const unsigned int u, const unsigned int v)
{
	if (u<1 || u>n || v<1 || v>n)
		throw std::out_of_range("u and v should be in range [1,n]");

	(*A)[u-1][v-1] = 0;
}

bool MatrixGraph::AreNeighbors(const unsigned int u, const unsigned int v) const
{
	if (u<1 || u>n || v<1 || v>n)
		throw std::out_of_range("u and v should be in range [1,n]");

	return (*A)[u-1][v-1] == 1;
}

int& MatrixGraph::operator()(const unsigned int u, const unsigned int v) {
	if (u<1 || u>n || v<1 || v>n)
		throw std::out_of_range("u and v should be in range [1,n]");

	return (*A)[u-1][v-1];
}

MatrixGraph::Matrix* MatrixGraph::Matrix3() const
{
	auto M2 = new Matrix(n, std::vector<int>(n));
	auto M3 = new Matrix(n, std::vector<int>(n));
	
	for (unsigned int i = 0; i < n; i++)
		for (unsigned int  j = 0; j < n; j++)
			for (unsigned int  k = 0; k < n; k++)
				(*M2)[i][j] += (*A)[i][k] * (*A)[k][j];

	for (unsigned int i = 0; i < n; i++)
		for (unsigned int j = 0; j < n; j++)
			for (unsigned int k = 0; k < n; k++)
				(*M3)[i][j] += (*M2)[i][k] * (*A)[k][j];

	delete M2;
	return M3;
}
