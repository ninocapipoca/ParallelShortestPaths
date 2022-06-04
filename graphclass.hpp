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

using adjVector = std::vector<std::vector<Node>>; // define alias here, otherwise it's quite messy

class Graph{
public:
  adjVector adjLists;

Graph();
Graph(adjVector _adjLists);
void printGraph();
};
