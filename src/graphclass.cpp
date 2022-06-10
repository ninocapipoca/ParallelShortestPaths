#include <iostream>
#include <cmath>
#include "../include/graphclass.hpp"
#include <vector>

using namespace std;
using nodeList = std::vector<Node>;

// constructors
Node::Node(double _value, double _weight){
  value = _value;
  weight = _weight;
  nodeList empty = { };
  adjList = empty;
  kind = UNKNOWN;
}

Node::Node(double _value, double _weight, nodeList _adjList){
  value = _value;
  weight = _weight;
  adjList = _adjList;
  kind = UNKNOWN;
}

Graph::Graph(nodeList _nodes){
  nodes = _nodes;
  delta = 1.0;
}

Graph::Graph(nodeList _nodes, double d){
  nodes = _nodes;
  delta = d;
}


// methods
void Node::insert(Node newNode){ // CHECK: honestly not sure if it's worth having 2 separate methods
  this->adjList.push_back(newNode);
}

void Node::insert_multiple(nodeList newnodes){
  for (auto ptr = newnodes.begin(); ptr < newnodes.end(); ptr++){
    this->adjList.push_back(*ptr); // CHECK: is this or a function call better?
  }
}

void Node::assign(double delta){ // assigns a label of either 'light' or not to a single node
  if (this->weight <= delta){
    kind = LIGHT;
  }
  else {
    kind = HEAVY; }
}

bool Graph::is_empty(){
  return nodes.empty();
}

// FOR STEP ALGORITHM -----
void Graph::assign(){ // assign 'light' / 'heavy' label to all nodes in graph
  for (auto ptr = this->nodes.begin(); ptr < this->nodes.end(); ptr++){
    if (ptr->kind == UNKNOWN){ // if not labelled
      ptr->assign(this->delta);
    }
  }
}

bool Graph::check_assigned(){ // check if all nodes are assigned a label
  for (auto ptr = this->nodes.begin(); ptr < this->nodes.end(); ptr++){
    if (ptr->kind == UNKNOWN){ // if even 1 not assigned, return false
      return false;
    }
  }

  return true;
}

// ------

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
