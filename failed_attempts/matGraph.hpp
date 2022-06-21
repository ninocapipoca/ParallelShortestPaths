#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include "../include/matNode.hpp"

using binaryMatrix = std::vector<std::vector<int>>;
using Matrix = std::vector<std::vector<double>>;

class matGraph{
private:
  Matrix costs;
  binaryMatrix adjacent;
  Matrix distances;

public:
  matGraph();
  matGraph(Matrix c, binaryMatrix adj);
  matGraph(Matrix c, binaryMatrix adj, Matrix dist);

};

template <typename T>
std::vector<std::vector<T>> create_zero_mat(int n);

binaryMatrix construct_adj_mat(std::vector<matNode> nodeList);
