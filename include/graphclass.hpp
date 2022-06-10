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
  std::vector<Node> adjList;
  int kind;

// bool operator == (Node node2) {
//   return (value == node2.value && weight == node2.weight && adjList == node2.adjList && light == node2.light);
// }

Node();
Node(double _value, double _weight);
Node(double _value, double _weight, std::vector<Node> _adjList);

void insert(Node newNode);
void printNode();
void insert_multiple(std::vector<Node> newnodes);
void assign(double delta);
};

//using adjVector = std::vector<Node>; // define alias here, otherwise it's quite messy

class Graph{
public:
  std::vector<Node> nodes;
  double delta;

Graph();
Graph(std::vector<Node> _nodes);
Graph(std::vector<Node> _nodes, double d);
void printGraph();
bool is_empty();
void assign();
bool check_assigned();

};
