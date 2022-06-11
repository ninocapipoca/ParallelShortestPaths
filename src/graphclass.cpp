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

// overloading
bool Node::check_equal_aux(Node rhs){
  // checks some of the properties for equality
  bool test_value = (rhs.value) == value;
  bool test_weight = (rhs.weight) == weight;
  bool test_kind = (rhs.kind) == kind;

  return test_value && test_weight && test_kind ;
}



// bool Node::operator==(const Node& rhs){
//   bool test_adjlist = true;
//   if (!this->check_equal_aux(rhs)){
//     // if any of the other properties don't match, directly false
//     return false;
//   }
//
//   // otherwise check that adjList is the same
//   for (auto ptr = this->adjList.begin(); ptr < this->adjlist.end(); ptr++){
//     this->adjList.push_back(*ptr); // CHECK: is this or a function call better?
//   }
// }


// just realised why this code doesn't work.
bool Node::check_equal_address(Node* rhs){
  return (this == rhs);
}

bool Node::adjList_eq(nodeList& list){
  for (auto ptr = this->adjList.begin(); ptr < this->adjList.end(); ptr++){
    for (auto ptr_l = list.begin(); ptr_l < list.end(); ptr_l++){
      if (ptr != ptr_l){
        return false;
      }
    }
  }
  return true;

}

bool Node::operator==(const Node& rhs){
  return true; // TEMPORARY - just so this compiles
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


// some attempts at stuff
// void Node::check_value_rec(nodeList list, bool& res){ // NOT IN HPP YET
//   if (adjList.size() != list.size()){
//     res = false;
//   }
//
//   if (list.empty()){
//     return res;
//   }
//
//   bool temp = false;
//   for (auto ptr = list.begin(); ptr < list.end(); ptr++){
//     // iterate and check values correspond
//
//
//   }
//
// }
