#include <iostream>
#include <cmath>
#include "graphclass.hpp"
#include <vector>

using namespace std;

Node::Node(int _value){
  value = _value;
  std::vector<Node> empty = { };
  adjList = empty;
}

Node::Node(int _value, std::vector<Node> _adjList){
  value = _value;
  adjList = _adjList;
}

void Node::insert(Node newNode){
  this->adjList.push_back(newNode);
}

Graph::Graph(adjVector _adjLists){
  adjLists = _adjLists;
}
