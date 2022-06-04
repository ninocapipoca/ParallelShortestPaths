#pragma once
#include <iostream>
#include <cmath>

class Vertex{ // equivalent to a node
public:
  int value;
  Vertex* adjacent;

  Vertex();
  Vertex(int val);
  Vertex(int val, Vertex* adj);
  print_vertex();
};

class Edge{ // connects vertices
public:
  int weight;
  Vertex* start;
  Vertex* end;

  Edge();
  Edge(int w, Vertex* s, Vertex* e);
  print_edge();
};

class Graph{
private:
  Vertex* root;

public:
  Graph();
  Graph(Vertex* _root);
  insert(Vertex* vertex, Edge edge);
  connect(Vertex* v1, Vertex* v2);
  print_graph();

}
