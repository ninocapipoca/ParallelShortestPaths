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

Graph::Graph(adjVector _adjLists){
  adjLists = _adjLists;
}

void Node::printNode(){
  cout << "Node w/ val ";
  cout << this->value << endl;


  if (!(this->adjList).empty()){
    cout << "next: ";
    (this->adjList[0]).printNode();
  }

}

void printAdjList(vector<Node> list){
  for (auto ptr = list.begin(); ptr < list.end(); ptr++){
    ptr->printNode();
  }
}
