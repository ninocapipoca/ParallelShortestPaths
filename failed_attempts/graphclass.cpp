#include <iostream>
#include <cmath>
#include "../include/graphclass.hpp"
#include <vector>
#include <limits>

using namespace std;
using nodeList = vector<Node>;
double inf = numeric_limits<double>::max();



// constructors
Node::Node(){
  value = 0;
  //weight = 0;
  kind = UNKNOWN;
}

Node::Node(int _value){
  value = _value;
  //weight = _weight; // of edge
  kind = UNKNOWN;
}

nodeCollection::nodeCollection(Node h){
  head = h;
  std::map<Node, int> empty = { };
  list = empty;
}


nodeCollection::nodeCollection(Node h, std::map<Node, int> l){
  head = h;
  list = l;
}

Graph::Graph(std::vector<nodeCollection> _nodes){
  nodes = _nodes;
  delta = 1.0;
}

Graph::Graph(std::vector<nodeCollection> _nodes, double d){
  nodes = _nodes;
  delta = d;
}


Request::Request(double t, Node* s, Node* e, double c){
  t_value = t;
  start = s;
  end = e;
  cost = c;
}


// overloading - nodes
bool Node::operator==(const Node& rhs){
  return (this->value == rhs.value) && (this->kind == rhs.kind);
}

bool Node::operator!=(const Node& rhs){
  return !((this->value == rhs.value) && (this->kind == rhs.kind));
}

// FUNCTIONS OUTSIDE OF ANY CLASS
bool vect_contains(nodeList list, Node target){
  for (auto ptr = list.begin(); ptr < list.end(); ptr++){
    if ((*ptr) == target){
      return true;
    }
  }
  return false;
}

// methods
void Node::assign(double delta){ // assigns a label of either 'light' or not to a single node
  if (this->value <= delta){
    kind = LIGHT;
  }
  else {
    kind = HEAVY; }
}

void nodeCollection::insert(Node newNode){ // CHECK: honestly not sure if it's worth having 2 separate methods
  this->list.push_back(newNode);
}

void nodeCollection::insert_multiple(nodeList newnodes){
  for (auto ptr = newnodes.begin(); ptr < newnodes.end(); ptr++){
    this->list.push_back(*ptr); // CHECK: is this or a function call better?
  }
}

bool nodeCollection::contains(Node target){ // verify if target node is in current nodeCollection
  if (this->head == target){
    return true;
  }
  return vect_contains(this->list, target);
}

void nodeCollection::assign(double delta){
  if ((this->head).kind == UNKNOWN){
    (this->head).assign(delta); // assign head
  }

  for (auto ptr = this->list.begin(); ptr < this->list.end(); ptr++){
    if (ptr->kind == UNKNOWN){ // if not labelled
      ptr->assign(delta);
    }
  }
}

bool nodeCollection::check_assigned(){ // checks if all nodes in list assigned
  if (this->head.kind == UNKNOWN){
    return false;
  }

  for (auto ptr = this->list.begin(); ptr < this->list.end(); ptr++){
    if (ptr->kind == UNKNOWN){ // if even 1 not assigned, return false
      return false;
    }
  }

  return true;
}



bool Graph::is_empty(){
  return nodes.empty();
}

// FOR STEP ALGORITHM -----
void Graph::assign(){ // assign 'light' / 'heavy' label to all nodes in graph
  for (auto ptr = this->nodes.begin(); ptr < this->nodes.end(); ptr++){
    ptr->assign(this->delta);
  }
}

bool Graph::check_assigned(){ // check if all nodes are assigned a label
  for (auto ptr = this->nodes.begin(); ptr < this->nodes.end(); ptr++){
    if (!ptr->check_assigned()){
      return false;
    }
  }
  return true;
}

// overloading - linked lists
// in our case, the linke lists are equal if:
// 1. the head is the same
// 2. the rest of the nodes are the same, but in whichever order
bool nodeCollection::operator==(const nodeCollection& rhs){
  if (this->head != rhs.head){
    return false;
  }

  for (auto ptr = rhs.list.begin(); ptr < rhs.list.end(); ptr++){
    if (!this->contains(*ptr)){ // if even 1 contained in curr list
      return false; // no equality
    }
  }

  return true;

}

// ------

// funcs to print nicely (or kind of nicely)
void Node::printNode(){
  cout << "-------" << endl;
  cout << "Parent - value: " << this->value << endl;


}

void nodeCollection::printnodeCollection(){
  cout << "Parent: " << endl;
  (this->head).printNode();

  if (!(this->list).empty()){
    cout << "Children: " << endl;
    for (auto ptr = list.begin(); ptr < list.end(); ptr++){
      cout << "value " << ptr-> value << endl;
      //cout << ptr->value << endl;
    }
}
}

void Graph::printGraph(){
  cout << "printing graph" << endl;
  auto test = nodes.begin();
  for (auto ptr = nodes.begin(); ptr != nodes.end(); ptr++){
    (ptr)->printnodeCollection();
  }
}
