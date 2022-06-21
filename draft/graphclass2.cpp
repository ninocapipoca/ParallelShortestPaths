#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

using namespace std;
int inf = numeric_limits<int>::max();
int max_assigned_id = 0;

void reset_ids(){
  max_assigned_id = 0;
}

class Node{
private:
  double estimate; // the shortest path so far
  int id; // int to identify node
  vector<Node> adj_list; // connected nodes
  vector<double> weight_list; // cost of getting to those nodes
public:
  Node();
  Node(vector<Node> adj, vector<double> weights);
  void connect(Node& node, double weight);
  bool operator==(const Node& rhs);
  bool operator!=(const Node& rhs);
};

Node::Node(){
  estimate = inf;
  id = max_assigned_id;
  max_assigned_id++;

  vector<Node> empty_nodes = {};
  vector<double> empty_weights = {};
  adj_list = empty_nodes;
  weight_list = empty_weights;
}

Node::Node(vector<Node> adj, vector<double> weights){
  estimate = inf;
  id = max_assigned_id;
  max_assigned_id++;

  adj_list = adj;
  weight_list = weights;
}

Node::connect(Node* node, double weight){
  // connect two nodes together
  // update "self" info
  adj_list.push_back(node);
  weight_list.push_back(weight);

  // update input node info
  node->adj_list.push_back(*this);
  node->weight_list.push_back(weight);
}

// node operator overloading
bool Node::operator==(const Node& rhs){
  return (this->id == rhs.id);
}

bool Node::operator!=(const Node& rhs){
  return (this->id != rhs.id);
}

using nodeList = vector<Node>;

struct Request{
  Node start_node; // v (vertex)
  Node end_node; // w  (vertex)
  double calculated_value; // tent(v) + c(v, w)
};

Request::Request(Node start, Node end, double calculated){
  start_node = start;
  end_node = end;
  calculated_value = calculated;
}

class Graph{
private:
  nodeList nodes;
  double delta;
public:
  Graph();
  Graph(nodeList _nodes, double d);
  void insert_node(Node node, double weight);
  bool reachable(Node start, Node target);
  double get_weight(Node start, Node end);
  int find_nr_buckets();
};

Graph::Graph(){
  nodeList empty = {};
  nodes = empty;
  delta = 0;
}

Graph::Graph(nodeList _nodes, double d){
  nodes = _nodes;
  delta = d;
}

void Graph::insert_node(Node node, double weight){
  // adding a new node into the graph
  node.connect(&node, weight);
  nodes.push_back(node);
}

bool contains(nodeList list, Node target){
  for (int i = 0; i < list.size(); i++){
    if (list[i] == target){
      return true;
    }
  }
  return false;
}

bool Graph::reachable(Node start, Node target){
  // determines whether target is reachable
  // from start
  if (contains(target.adj_list, start) || contains(start.adj_list, target)){
    return true;
  }
  else {
    bool temp = true;
    for (int i = 0; i < target.adj_list.size(); i++)7
      temp = temp && this->contains(target_adj_list[i], target);
  }
  return temp;
}

double Graph::get_weight(Node start, Node end){
  // get weight of directly connected nodes
  if (!reachable(start, end)){
    return -1.0;
  }

  int ind = -1;
  for (int i = 0; i < start.adj_list.size(); i++){
    if (start.adj_list[i].id == end.id){
      ind = i;
      break;
    }
  }

  return start.weight_list[i];
}

int Graph::find_nr_buckets(){
  double max_cost = 0;
  // iter through nodes
  for (int i = 0; i < nodes.size(); i++){
    // iter through node cost lists
    for (int j = 0; j < nodes[i].weight_list.size(); j++){
      if (weight_list[j] > max_cost){
        max_cost = weight_list[j];
      }
    }
  }

  return ceil(max_cost / delta) + 1;
}

struct Bucket{
  int ind; // index of bucket
  nodeList contents;

public:
  Bucket(int index);
  void insert(Node node);
  void remove(Node node);
}

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
  contents.remove(contents.begin(), contents.end(), node);
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

void transfer_deleted(nodeList &deleted, nodeList contents){
  for (int i = 0; i < contents.size(); i++){
    deleted.push_back(contents[i]);
  }
}
