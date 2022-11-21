#pragma once
#include "GraphHelper.h"
#include <cmath>

class Algorithms
{
public:
	/// AlgorithmOne gets a ListGraph and bool lowDegMid and:
	/// 1. builds a MatrixGraph.
	///		- theta(n^2 + m) complexity
	/// 2. searches for paths of length 2. if lowDegMid=true then only low degree
	///    middle vertices are checked.
	///		- O(n*m) complexity
	/// 3. checks if the first and last vertices in the path are connected.
	///		- theta(1) complexity using the matrix
	/// 4. if a triangle was found, returns an array containing its 3 vertices.
	/// 5. if no triangle was found, returns nullptr.
	/// 
	/// total complexity: O(n*m + n^2)
	static std::vector<int>* AlgorithmOne(const ListGraph& L, const bool lowDegMid=false);

	/// AlgorithmTwo gets a MatrixGraph M and:
	/// 1. calculates M^3.
	///		- theta(n^3) complexity
	/// 2. searches the diagonal of the matrix for the 3 vertices of a triangle.
	///		- theta(n) complexity
	/// 3. if a triangle was found, returns an array containing its 3 vertices.
	/// 4. if no triangle was found, returns nullptr.
	/// 
	/// total complexity: theta(n^3)
	static std::vector<int>* AlgorithmTwo(const MatrixGraph& M);

	/// AlgorithmThree gets a ListGraph and:
	/// 1. runs AlgorithmOne with lowDegMid=true, meaning only low degree middle vertices
	///    will be checked.
	///		- O(m*delta) = O(m^3/2) complexity
	/// 2. if a triangle was found, returns an array containing its 3 vertices.
	/// 3. if no triangle was found:
	/// 5. creates new matrix with only high degree vertices.
	///	   -  O(n + delta^2) = O(n + m) complexity
	/// 6. runs AlgorithmTwo on the new matrix and returns the result.
	///	   - theta(m^3/2) complexity
	/// 
	/// total complexity: O(m^3/2 + n^2)
	static std::vector<int>* AlgorithmThree(const ListGraph& L);
};

