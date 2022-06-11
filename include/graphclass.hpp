#pragma once
#include <iostream>
#include <cmath>
#include <vector>

#define UNKNOWN 0
#define LIGHT 1
#define HEAVY 2


struct Request{
  // value
  // tentative cost + current cost (val assigned to node)
  double t_value;
  // cost of the edge
  double t_weight;
};



class Node{
  // value is the number assigned to the VERTEX
  // weight is weight of the edge
public:
  double value, weight;
  //std::vector<Node> adjList;
  int kind;


bool operator==(const Node& rhs);
bool operator!=(const Node& rhs);

void check();
Node();
Node(double _value, double _weight);

void printNode();
void assign(double delta);
};

 // define alias here, otherwise it's quite messy
using nodeList = std::vector<Node>;

class linkedList{
  Node head;
  nodeList list;

public:
  linkedList(Node h);
  linkedList(Node h, nodeList l);

  void insert(Node newNode);
  void insert_multiple(nodeList newnodes);
  bool contains(Node target);
  bool operator==(const linkedList& rhs);
  void assign(double delta);
  bool check_assigned();
  void printLinkedList();

};

class Graph{
public:
  std::vector<linkedList> nodes;
  double delta;

Graph();
Graph(std::vector<linkedList> _nodes);
Graph(std::vector<linkedList> _nodes, double d);
void printGraph();
bool is_empty();
void assign();
bool check_assigned();

};
