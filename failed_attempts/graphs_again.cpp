#pragma once
#include <iostream>
#include <vector>
#include <limits>
#include <utility>
#include <list>
#include <set>

using namespace std;

class Graph{
private:
  int V; // nr of vertices
  list<pair<int,int>> *adj); // ptr to adjList

public:
  Graph(int v);
  void addEdge(int v1, int v2, int weight);

}

Graph::Graph(int v){
  V = v;

  // create new adjlist
  adj = new list<pair<int,int>>[v];
}

void Graph::addEdge(int v1, int v2, int weight){
  // add edge to graph
  adj[v1].push_back(make_pair(v2,weight));
}
