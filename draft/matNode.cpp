#include <iostream>
#include <cmath>
#include "../include/matNode.hpp"
#include <vector>
#include <limits>

// my other implementation seems to be way too
// complicated so I'm trying sth else

// constructors

matNode::matNode(int k){
  id = max_id + 1;
  max_id++;

  kind = k;
  assigned_val = inf;
  std::vector<double> empty_costs = {};
  edge_costs = empty_costs;
  std::vector<matNode> empty_adj = {};
  adj_nodes = empty_adj;

}
matNode::matNode(int k, double val){
  id = max_id + 1;
  max_id++;

  kind = k;
  assigned_val = val;
  std::vector<double> empty_costs = {};
  edge_costs = empty_costs;
  std::vector<matNode> empty_adj = {};
  adj_nodes = empty_adj;
}

matNode::matNode(int k, double val, std::vector<double> costs, std::vector<matNode> adj){
  id = max_id + 1;
  max_id++;

  kind = k;
  assigned_val = val;
  edge_costs = costs;
  adj_nodes = adj;
}

// not sure if correct
matNode::~matNode(){
  max_id--;
}

// methods
bool matNode::contained_in(std::vector<matNode> nodeList){
  if (this->adj_nodes.empty()){
    return false;
  }

  for (auto it = nodeList.begin(); it < nodeList.end(); nodeList++){
    if ((*it).id == this->id){
      return true;
    }
  }
  return false;
}
