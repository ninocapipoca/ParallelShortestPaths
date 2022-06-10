#pragma once
#include <iostream>
#include <cmath>
#include <vector>


struct Node{
  int value;
  std::vector<Node> adjList;

Node();
Node(int _value);
Node(int _value, std::vector<Node> _adjList);

void insert(Node newNode);
void printNode();
};

//using adjVector = std::vector<Node>; // define alias here, otherwise it's quite messy

class Graph{
public:
  std::vector<Node> nodes;

Graph();
Graph(std::vector<Node> _nodes);
void printGraph();
bool is_empty();
};
