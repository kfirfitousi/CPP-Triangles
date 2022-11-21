#include "Algorithms.h"

std::vector<int>* Algorithms::AlgorithmOne(const ListGraph& L, const bool lowDegMid)
{
	std::vector<int>* res = nullptr;
	auto deg = new std::vector<int>(L.n, 0); 
	double d = 1.0;

	if (lowDegMid)
	{
		delete deg;
		deg = L.Degree(); // degree array
		d = sqrt(L.m); // delta 
	}

	const auto M = GraphHelper::MatrixFromList(L); // build matrix from list

	for (unsigned int v = 1; v <= L.n; v++)
	{
		const auto AdjV = L.NeighborList(v);
		for (auto u = AdjV.begin(); u != AdjV.end(); u++)
		{
			if (!lowDegMid || (lowDegMid && (double)(*deg)[*u-1] <= d)) // lowDegMid=false, or lowDegMid=true and u has low degree
			{
				const auto AdjU = L.NeighborList(*u);
				for (auto w = AdjU.begin(); w != AdjU.end(); w++)
				{
					if (M->AreNeighbors(*w, v))
					{
						// triangle found v->u->w->v
						res = new std::vector<int>;
						res->push_back(v);
						res->push_back(*u);
						res->push_back(*w);
						return res;
					}
				}
			}
		}
	}

	return res;
}

std::vector<int>* Algorithms::AlgorithmTwo(const MatrixGraph& M)
{
	std::vector<int>* res = nullptr;
	const auto M3 = M.Matrix3(); // calculate third power of M
	unsigned int v = 1, u = 1, w = 1; 

	for (; v <= M.n; v++) // search for 1st vertex v
	{
		if ((*M3)[v-1][v-1] >= 1)
		{
			res = new std::vector<int>;
			res->push_back(v);
			break;
		}
	}

	if (!res) // no triangle found
		return nullptr;

	for (; u <= M.n; u++) // search for 2nd vertex u
	{
		if ((*M3)[u-1][u-1] >= 1 && M.AreNeighbors(v, u))
		{
			res->push_back(u);
			break;
		}
	}

	for (; w <= M.n; w++) // search for 3rd vertex w
	{
		if ((*M3)[w-1][w-1] >= 1 && M.AreNeighbors(u, w) && M.AreNeighbors(w, v))
		{
			res->push_back(w);
			break;
		}
	}

	return res;
}

std::vector<int>* Algorithms::AlgorithmThree(const ListGraph& L)
{
	std::vector<int>* res = nullptr;
	
	// step 1:
	res = AlgorithmOne(L, true); // run AlgorithmOne with lowDegMid=true
	if (res)
		return res;

	// step 2:
	const double d = sqrt(L.m);	// delta
	std::vector<int> highDeg; // high-degree vertices array; highDeg[i-1] wil be mapped to vertex i in new matrix
	for (unsigned int v = 1; v <= L.n; v++)
	{
		if (L.Deg(v) > d) // v has high degree
		{
			highDeg.push_back(v);
		}
	}

	const unsigned int hdSize = (unsigned int)highDeg.size(); // number of high degree vertices
	auto M = MatrixGraph(hdSize); // create new MatrixGraph with high degree vertices only

	for (unsigned int v = 1; v <= hdSize; v++) // fill matrix using highDeg for conversion
	{
		for (unsigned int u = 1; u <= hdSize; u++)
		{
			M(v, u) = L.AreNeighbors(highDeg[v-1], highDeg[u-1]);
		}
	}

	res = AlgorithmTwo(M); // run AlgorithmTwo on new matrix
	
	if (res)
	{
		// convert back to original vertices
		(*res)[0] = highDeg[(*res)[0] - 1];
		(*res)[1] = highDeg[(*res)[1] - 1];
		(*res)[2] = highDeg[(*res)[2] - 1];
	}

	return res;
}

