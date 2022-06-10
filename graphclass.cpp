#include <iostream>
#include <cmath>
#include "graphclass.hpp"
#include <vector>

using namespace std;
using adjacencyList = std::vector<Node>;

// constructors
Node::Node(int _value, int _weight){
  value = _value;
  weight = _weight;
  adjacencyList empty = { };
  adjList = empty;
}

Node::Node(int _value, int _weight, adjacencyList _adjList){
  value = _value;
  weight = _weight;
  adjList = _adjList;
}

Graph::Graph(adjacencyList _nodes){
  nodes = _nodes;
}


// methods
void Node::insert(Node newNode){
  this->adjList.push_back(newNode);
}

bool Graph::is_empty(){
  return nodes.empty();
}


// funcs to print nicely (or kind of nicely)
void Node::printNode(){
  cout << "-------" << endl;
  cout << "Parent - value: " << this->value << ",  weight: " << this-> weight << endl;


  if (!(this->adjList).empty()){
    cout << "Children: " << endl;
    for (auto ptr = adjList.begin(); ptr < adjList.end(); ptr++){
      cout << "value & weight " << ptr-> value << "," << ptr->weight << endl;
      //cout << ptr->value << endl;
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
