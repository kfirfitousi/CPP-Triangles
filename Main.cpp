#include "Algorithms.h"

int main(int argc, char* argv[]) {
	if (argc < 3)
	{
		std::cout << "USAGE: " << argv[0] << " <input-file> <output-file>";
		exit(1);
	}

	std::ifstream infile(argv[1]);
	std::ofstream outfile(argv[2]);

	if (!infile || !outfile)
	{
		std::cout << "Error: File can not be opened";
		exit(1);
	}

	int algo;
	ListGraph* Lptr;
	MatrixGraph* Mptr;
	std::vector<int>* triangle;
	std::string resStr;
	std::streampos pos;
	
	infile >> algo; // algorithm number

	switch (algo)
	{
	case 1:
		Lptr = GraphHelper::ListBuilder(infile);
		if (!Lptr) goto Error; 
		triangle = Algorithms::AlgorithmOne(*Lptr);
		resStr = GraphHelper::TriangleToString(triangle);
		goto Finish;
	case 2:
		Mptr = GraphHelper::MatrixBuilder(infile);
		if (!Mptr) goto Error;
		triangle = Algorithms::AlgorithmTwo(*Mptr);
		resStr = GraphHelper::TriangleToString(triangle);
		goto Finish;
	case 3:
		Lptr = GraphHelper::ListBuilder(infile);
		if (!Lptr) goto Error;
		triangle = Algorithms::AlgorithmThree(*Lptr);
		resStr = GraphHelper::TriangleToString(triangle);
		goto Finish;
	case 4:
		pos = infile.tellg(); // save current position in input file
		Lptr = GraphHelper::ListBuilder(infile);
		if (!Lptr) goto Error;
		triangle = Algorithms::AlgorithmOne(*Lptr);
		resStr = GraphHelper::TriangleToString(triangle);

		infile.seekg(pos); // restore position in input file
		Mptr = GraphHelper::MatrixBuilder(infile);
		if (!Mptr) goto Error;
		triangle = Algorithms::AlgorithmTwo(*Mptr);
		resStr += '\n' + GraphHelper::TriangleToString(triangle);

		triangle = Algorithms::AlgorithmThree(*Lptr);
		resStr += '\n' + GraphHelper::TriangleToString(triangle);
		goto Finish;
	default:
		resStr = "invalid algorithm number";
		goto Finish;

	Error:
		resStr = "invalid input";
	
	Finish:
		outfile << resStr;
		outfile.close();
		infile.close();
	}	
}