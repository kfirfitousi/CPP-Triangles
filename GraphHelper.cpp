#include "GraphHelper.h"

MatrixGraph* GraphHelper::MatrixBuilder(std::ifstream& infile) {
	int u, v, n;

	infile >> n;

	MatrixGraph* M = new MatrixGraph(n);

	while (!infile.eof())
	{
		infile >> u >> v;

		try {
			M->AddEdge(u, v);
		}
		catch (...) { // invalid edge
			delete M;
			return nullptr;
		}
	}

	return M;
}

MatrixGraph* GraphHelper::MatrixFromList(const ListGraph& L)
{
	MatrixGraph* M = new MatrixGraph(L.n);

	for (unsigned int u = 1; u <= L.n; u++)
	{
		auto AdjU = L.NeighborList(u);
		for (auto v = AdjU.begin(); v != AdjU.end(); v++)
		{
			M->AddEdge(u, *v);
		}
	}

	return M;
}

ListGraph* GraphHelper::ListBuilder(std::ifstream& infile) {
	int u, v, n;
	
	infile >> n;
	
	ListGraph* L = new ListGraph(n);
	
	while (!infile.eof())
	{
		infile >> u >> v;
	
		try {
			L->AddEdge(u, v);
		}
		catch (...) { // invalid edge
			delete L;
			return nullptr;
		}
	}
	
	return L;
}

std::string GraphHelper::TriangleToString(const std::vector<int>* tri)
{
	if (!tri)
		return "NO";

	std::string S;

	S += (char)((*tri)[0] + '0');
	S += ',';
	S += (char)((*tri)[1] + '0');
	S += ',';
	S += (char)((*tri)[2] + '0');

	return S;
}