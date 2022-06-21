// source -https://www.sciencedirect.com/science/article/pii/S0196677403000762?via%3Dihub

// TO DO - Implement sequential algorithm first maybe (or at least understand it)
// TO DO - Implement parallel algorithm

// NOTATION
// c(v, w) is the cost of the edge between c and w
// w is a vertex, v is a vertex
// tent(v) is the tentative distance to v relative to some node

// CONCEPTS
// 1. Buckets
// Buckets store vertices that are queued and have a tentative value within an interval
// The i-th bucket stores the vertices with *tentative assigned value* in [i*delta, (i+1)*delta)
//
// 2. Delta
// A positive real number representing the step (or "bucket") width
//
// 3. Re-using empty buckets
// One can reduce the number of buckets needed to
// b = max (ceil(cost(edge) / delta)) + 1
// [max on edges]
// in which case B[i] holds the vertices with tentative value in
// [(j*b + i)*delta, (j*b + i + 1)*delta)
// for all j >= 0.
//
// 4. To relax an edge
// To insert or move weight w in B if x < tentative_val(w)
//
// 5. Heavy / light edges
// If cost of the edge is <= delta, it is LIGHT. Otherwise, HEAVY


// THE IDEAS
// Algo removes all nodes from first nonempty bucket (current) and relaxes
// all light edges out of these nodes. This may result in new nodes
// entering the current bucket which are deleted in the next phase. Nodes
// previously deleted may be reinserted if their tentative distance
// has been improved by the previous phase.
// Once the current bucket remains empty after a phase, all nodes in its
// distance range have been assigned their final distance values during the
// previous phases.
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include "graphclass2.cpp"
#include <utility>      // std::pair, std::make_pair

//double inf = std::numeric_limits<double>::max();
using nodeList = std::vector<Node>;
using requestList = std::vector<Request>;

#define LIGHT   true
#define HEAVY   false
using namespace std;


requestList findRequests(nodeList V_p, bool kind, Graph graph){
  // kind is either light or heavy

  requestList res = {};
  // iterate through nodes in graph
  for (int i = 0; i < graph.nodes.size(); i++){
    nodeList reachable_nodes = {};

    // iterate through nodes in node list
    for (int j = 0; j < V_p.size(); j++){

      // if reachable
      if (graph.reachable(V_p[j], graph.nodes[i], 0)){

        // do calculations
        double weight = graph.get_weight(V_p[j], graph.nodes[i]);
        double val = V_p[j].estimate + weight;
        Request addme = Request(V_p[j], graph.nodes[i], val);

        // add if criteria all met
        if (kind == LIGHT && weight <= graph.delta){
          res.push_back(addme);
        }

        else if (kind == HEAVY && weight > graph.delta){
          res.push_back(addme);
        }
      }
    }
  }
    return res;
}

void relax(double delta, std::vector<Bucket> bucketList, Node w, double x){
  cout << "relaxing node " << w.id << " with weight " << x << endl;
  if (x < w.estimate){
    int in = floor(w.estimate / delta);
    cout << "before the if condition" << endl;
    if (in >= 0 && in < bucketList.size() && w.contained_in(bucketList[in].contents)){
      cout << "removing from current bucket" << endl;
      bucketList[in].remove(w);
      cout << "is w still in this bucket? " << w.contained_in(bucketList[in].contents) << endl;
    }
    cout << "placing in new bucket" << endl;
    bucketList[floor(x/delta)].insert(w);
    cout << "updating the estimate!!" << endl;
    cout << "previous: " << w.estimate << endl;
    (&w)->estimate = x;
    cout << "current estimate: " << w.estimate << endl;
  }
}

void relaxRequests(std::vector<Request> requests){
  // turns out this function is kind of unnecessary
}

bool bucketlist_empty(std::vector<Bucket> bucketList){
  // is a list of buckets empty? (ie all buckets empty?)
  cout << "checking if bucket list is completely empty" << endl;
  for (int i = 0; i < bucketList.size(); i++){
    if (bucketList[i].contents.size() != 0){
      cout << "bucketlist is NOT fully empty" << endl;
      return false;
    }
  }
  cout << "bucketlist is FULLY empty" << endl;
  return true;
}


// return path of nodes one needs
// to follow shortest path
void delta_stepping(Graph graph, Node start, Node dest){
  std::vector<Bucket> bucketList;
  // initialise list of buckets
  int nr_buckets = graph.find_nr_buckets();
  for (int n = 0; n < nr_buckets; n++){
    bucketList.push_back(Bucket(n));
  }

  // first make sure all tentative distances are infinity
  for (int i = 0; i < graph.nodes.size(); i++){
    if (graph.nodes[i].estimate != inf){
      graph.nodes[i].estimate = inf;
    }
  }

  Node sourceNode = Node();
  // relax (s,0)
  relax(graph.delta, bucketList, sourceNode, 0.0);
  while (!bucketlist_empty(bucketList)){ // while all buckets are not empty
    int smallest = smallest_nonempty(bucketList);
    nodeList deleted = {};
    while (bucketList[smallest].contents.size() != 0){
      requestList requests = findRequests(bucketList[smallest].contents, LIGHT, graph);
      transfer_deleted(deleted, bucketList[smallest].contents);
      bucketList[smallest].contents = {}; // make bucket empty

      for (int i = 0; i < requests.size(); i++){
        relax(graph.delta, bucketList, (requests[i].end_node), requests[i].calculated_value);
      }

      requests = findRequests(deleted, HEAVY, graph);
      for (int i = 0; i < requests.size(); i++){
        relax(graph.delta, bucketList, (requests[i].end_node), requests[i].calculated_value);
      }

    }
  }
}

  int main(){
  //  basic test code
    cout << "creating nodes" << endl;
    Node node1 = Node();
    Node node2 = Node();
    Node node3 = Node();
    Node node4 = Node();

    cout << "connecting nodes" << endl;
    node1.connect(node2, 1.0);
    node2.connect(node4, 2.0);
    node4.connect(node3, 3.0);
    node3.connect(node1, 4.0);

    nodeList nodes = {node1, node2, node3, node4};
    Graph graph = Graph(nodes, 1.0);
    cout << graph.reachable(node1, node2, 0) << endl;

    cout << "running delta stepper" << endl;
    cout << node2.estimate << endl;
    delta_stepping(graph, node1, node2);
    cout << node2.estimate << endl;

  }
