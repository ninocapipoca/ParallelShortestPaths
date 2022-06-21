#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <map>


#define UNKNOWN 0
#define LIGHT 1
#define HEAVY 2


struct Request{
  // tentative cost
  double t_value;
  Node* start;
  Node* end;
  double cost; // of going from start to end

  Request();
  Request(double t, Node* s, Node* e, double c);
};



class Node{
  // value is the number assigned to the VERTEX
  // weight is weight of the edge
public:
  int value; // weight;
  //std::vector<Node> adjList;
  int kind;


bool operator==(const Node& rhs);
bool operator!=(const Node& rhs);

void check();
Node();
Node(int _value);

void printNode();
void assign(double delta);
};

 // define alias here, otherwise it's quite messy
using nodeList = std::vector<Node>;

class nodeCollection{
  Node head;
  std::map<Node, int> list;

public:
  nodeCollection(Node h);
  nodeCollection(Node h, std::map<Node, int> l);

  void insert(Node newNode);
  void insert_multiple(nodeList newnodes);
  bool contains(Node target);
  bool operator==(const nodeCollection& rhs);
  void assign(double delta);
  bool check_assigned();
  void printnodeCollection();

};

class Graph{
public:
  std::vector<nodeCollection> nodes;
  double delta;

Graph();
Graph(std::vector<nodeCollection> _nodes);
Graph(std::vector<nodeCollection> _nodes, double d);
void printGraph();
bool is_empty();
void assign();
bool check_assigned();

};
