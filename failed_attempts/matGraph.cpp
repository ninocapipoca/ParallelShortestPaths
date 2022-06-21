#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include "../include/matGraph.hpp"

// NOTE ON ADJACENCY MATRIX
// the coefficient = 1 if there exists an edge between vertex [row] (i) & vertex [col] (j)

template <typename T> // this shld work for both ints & floats
std::vector<std::vector<T>> create_zero_mat(int n){
  std::vector<T> zeroes;
  for (int i = 0; i < n; i++){
    zeroes.push_back(0);
  }

  std::vector<T> final;
  for (int j = 0;j < n; j++){
    final.push_back(zeroes);
  }

  return final;
}

matGraph::matGraph(Matrix c, binaryMatrix adj){
  costs = c;
  adjacent = adj;
  int x = adj.size();

  Matrix dist = create_zero_mat(x);
  distances = dist;

}
matGraph::matGraph(Matrix c, binaryMatrix adj, Matrix dist){
  costs = c;
  adjacent = adj;
  distances = dist;
}

void construct_adj_mat(std::vector<matNode> nodeList, binaryMatrix& binMat, Matrix& costMat){
  // assumes nodes do not go to themselves
  // will overwrite binMat and costMat

  for (int row = 0; row < nodeList.size(); row++){
    for (int col = 0; col < nodeList.size(); col++){

      bool exists_edge = nodeList[row].contained_in(nodeList[col].adj_nodes);

      if(exists_edge){ // fill in ones appropriately; i.e. if there is an edge
        binMat[row][col] = 1;
        costMat[row][col] =
      }
    }
  }

}

Matrix construct_cost_mat(std::vector<matNode> nodeList){

}
