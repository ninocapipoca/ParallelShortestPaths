#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <stdio.h>
#include <stdlib.h>


// actually int and double matrices respectively, but whatever
using binaryMatrix = std::vector<std::vector<int>>;
using Matrix = std::vector<std::vector<double>>;


double inf = numeric_limits<double>::max();

template <typename T>
bool g_contains(T item, std::vector<T> l){
  for (int i = 0; i < l.size(); i++){
    if (item == vector[i]){
      return true;
    }
  }

  return false;
}

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

struct nodeVals{
  // cost to get to node
  // whether it is adjacent
  // distance to this node
  int id;
  int cost, adj, dist;

nodeVals(){
  cost = 0;
  adj = 0;
  dist = inf;

}
nodeVals(int c, int a, int d){
  cost = c;
  adj = a;
  dist = d;
}
};

class _Graph{
  nodeValsMatrix mat;
  std::vector<int> used_ids;

_Graph();
_Graph(nodeValsMatrix m, std::vector<int> ids){
  mat = m;
  used_ids = ids;
}

_Graph(nodeValsMatrix m){
  mat = m;
  std::vector<int> empty = {};
  used_ids = empty;
}

};

using nodeValsMatrix = std::vector<std::vector<nodeVals>>;

// TODO - write a func that makes the graph matrix
nodeValsMatrix generate_graph_mat(std::vector<nodeVals> nodes){
  int n = nodes.size;

  nodeValsMatrix res;

  return res;
}
