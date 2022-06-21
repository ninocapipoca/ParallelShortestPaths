#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;
double inf = numeric_limits<int>::max();
int max_assigned_id = 0;

void reset_ids(){
  max_assigned_id = 0;
}

class Node{
public:
  double estimate; // the shortest path so far
  int id; // int to identify node
  vector<Node> adj_list; // connected nodes
  vector<double> weight_list; // cost of getting to those nodes

  Node();
  Node(vector<Node> adj, vector<double> weights);
  void connect(Node node, double weight);
  bool operator==(const Node& rhs);
  bool operator!=(const Node& rhs);
  bool contained_in(vector<Node> list);
};

Node::Node(){
  estimate = inf;
  id = max_assigned_id;
  max_assigned_id++;

  vector<Node> empty_nodes = {};
  vector<double> empty_weights = {};
  adj_list = empty_nodes;
  weight_list = empty_weights;
  cout << "empty node with id " << id << " created" << endl;
}

Node::Node(vector<Node> adj, vector<double> weights){
  estimate = inf;
  id = max_assigned_id;
  max_assigned_id++;

  adj_list = adj;
  weight_list = weights;
  cout << "node with id " << id << " created" << endl;
}

// node operator overloading
bool Node::operator==(const Node& rhs){
  return (this->id == rhs.id);
}

bool Node::operator!=(const Node& rhs){
  return (this->id != rhs.id);
}

using nodeList = vector<Node>;
bool Node::contained_in(nodeList list){
  for (int i = 0; i < list.size(); i++){
    if (list[i] == (*this)){
      return true;
    }
  }
  return false;
}

void Node::connect(Node node, double weight){
  // connect two nodes together
  // update "self" info
  if (node.contained_in(adj_list) || this->contained_in(node.adj_list)){
    return;
  }
  adj_list.push_back(node);
  weight_list.push_back(weight);

  // update input node info
  (&node)->adj_list.push_back(*this);
  (&node)->weight_list.push_back(weight);
  cout << "connected node " << id << " with " << node.id << ", weight " << weight << endl;
}

struct Request{
  Node start_node; // v (vertex)
  Node end_node; // w  (vertex)
  double calculated_value; // tent(v) + c(v, w)
public:
  Request(Node start, Node end, double calculated);
};

Request::Request(Node start, Node end, double calculated){
  start_node = start;
  end_node = end;
  calculated_value = calculated;
}

class Graph{
public:
  nodeList nodes;
  double delta;
  Graph();
  Graph(nodeList _nodes, double d);
  void insert_node(Node node, double weight);
  bool reachable(Node start, Node target, int ind);
  double get_weight(Node start, Node end);
  int find_nr_buckets();
};

Graph::Graph(){
  nodeList empty = {};
  nodes = empty;
  delta = 0;
  cout << "empty graph created" << endl;
}

Graph::Graph(nodeList _nodes, double d){
  nodes = _nodes;
  delta = d;
  cout << "graph with at least one node and delta " << d << " created" << endl;
}

void Graph::insert_node(Node node, double weight){
  // adding a new node into the graph
  node.connect(node, weight);
  nodes.push_back(node);
}



bool Graph::reachable(Node start, Node target, int ind){
  // determines whether target is reachable
  // from start
  if (start.contained_in(target.adj_list) || target.contained_in(start.adj_list)){
    return true;
  }

  else if (start == target){
    return true;
  }
  else {
    if (ind < start.adj_list.size()){
      return reachable(start.adj_list[ind], target, ind+1);
    }
    return false;

  }
}

double Graph::get_weight(Node start, Node end){
  // get weight of directly connected nodes
  if (!reachable(start, end, 0)){
    return -1.0;
  }

  int ind = -1;
  for (int i = 0; i < start.adj_list.size(); i++){
    if (start.adj_list[i].id == end.id){
      ind = i;
      break;
    }
  }

  return start.weight_list[ind];
}

int Graph::find_nr_buckets(){
  double max_cost = 0;
  // iter through nodes
  for (int i = 0; i < nodes.size(); i++){
    // iter through node cost lists
    for (int j = 0; j < nodes[i].weight_list.size(); j++){
      if (nodes[i].weight_list[j] > max_cost){
        max_cost = nodes[i].weight_list[j];
      }
    }
  }

  return ceil(max_cost / delta) + 1;
}

class Bucket{
public:
  int ind; // index of bucket
  nodeList contents;

  Bucket(int index);
  void insert(Node node);
  void remove(Node node);
};

Bucket::Bucket(int index){
  ind = index;
  nodeList empty = {};
  contents = empty;
}

void Bucket::insert(Node node){
  // adds node to back
  contents.push_back(node);
}

void Bucket::remove(Node node){
  // removes node specifically
  // maybe not the most elegant implementation but it's all I could do for now
  nodeList temp = {};
  for (int i = 0; i < contents.size(); i++){
    if (contents[i] != node){
      temp.push_back(contents[i]);
    }
  }

  contents = temp;
}

int smallest_nonempty(std::vector<Bucket> bucketList){
  // returns index of smallest nonempty bucket
  int smallest_size = 99999;
  int index = 0;
  for (int i = 0; i < bucketList.size(); i++){
    if (bucketList[i].contents.size() < smallest_size && bucketList[i].contents.size() > 0){
      smallest_size = bucketList[i].contents.size();
      index = i;
    }
  }
  return index;
}

void transfer_deleted(nodeList deleted, nodeList contents){
  for (int i = 0; i < contents.size(); i++){
    (&deleted)->push_back(contents[i]);
  }
}
