#include <iostream>
#include <cmath>
#include "graphclass.hpp"

using namespace std;

Vertex::Vertex(int val){
  value = val;
  adjacent = NULL;
}

Vertex::Vertex(int val, Vertex* adj){
  value = val;
  adjacent = adj;
}

void print_vertex(){
  cout << "value is " << val << endl;
  cout << "adjacent vertex is of value " << adjacent.val << endl;
}

Edge::Edge(int w, Vertex* s, Vertex* e){
  weight = w;
  start = s;
  end = e;
}

void print_edge(){

}

Graph::Graph(Vertex* _root){
  root = _root;
}

void print_graph(){

}
