#include <iostream>
#include <cmath>
#include "graphclass.hpp"
#include <vector>

using namespace std;
using adjacencyList = std::vector<Node>;

Node::Node(int _value){
  value = _value;
  adjacencyList empty = { };
  adjList = empty;
}

Node::Node(int _value, adjacencyList _adjList){
  value = _value;
  adjList = _adjList;
}

void Node::insert(Node newNode){
  this->adjList.push_back(newNode);
}

Graph::Graph(adjacencyList _nodes){
  nodes = _nodes;
}

bool Graph::is_empty(){
  return nodes.empty();
}

void Node::printNode(){
  cout << "-------" << endl;
  cout << "Parent: ";
  cout << this->value << endl;


  if (!(this->adjList).empty()){
    cout << "\n Children: ";
    for (auto ptr = adjList.begin(); ptr < adjList.end(); ptr++){
      cout << "Node w/ val";
      cout << ptr->value << endl;
    }
  }

}

void Graph::printGraph(){
  cout << "printing graph" << endl;
  auto test = nodes.begin();
  for (auto ptr = nodes.begin(); ptr != nodes.end(); ptr++){
    ptr->printNode();
  }
}
