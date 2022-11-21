#pragma once
#include "MatrixGraph.h"
#include "ListGraph.h"
#include <fstream>

class GraphHelper
{
public:
	static MatrixGraph* MatrixBuilder(std::ifstream& infile);
	static MatrixGraph* MatrixFromList(const ListGraph& L);
	static ListGraph* ListBuilder(std::ifstream& infile);
	static std::string TriangleToString(const std::vector<int>* tri);
};

