#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <stdio.h>
#include <stdlib.h>


// actually int and double matrices respectively, but whatever
using binaryMatrix = std::vector<std::vector<int>>;
using Matrix = std::vector<std::vector<double>>;


double inf = numeric_limits<double>::max();

template <typename T>
bool g_contains(T item, std::vector<T> l){
  for (int i = 0; i < l.size(); i++){
    if (item == vector[i]){
      return true;
    }
  }

  return false;
}

template <typename T> // this shld work for both ints & floats
std::vector<std::vector<T>> create_zero_mat(int n){
  std::vector<T> zeroes;
  for (int i = 0; i < n; i++){
    zeroes.push_back(0);
  }

  std::vector<T> final;
  for (int j = 0;j < n; j++){
    final.push_back(zeroes);
  }

  return final;
}

struct nodeVals{
  // cost to get to node
  // whether it is adjacent
  // distance to this node
  int id;
  int cost, adj, dist;

nodeVals(){
  cost = 0;
  adj = 0;
  dist = inf;

}
nodeVals(int c, int a, int d){
  cost = c;
  adj = a;
  dist = d;
}
};

class _Graph{
  nodeValsMatrix mat;
  std::vector<int> used_ids;

_Graph();
_Graph(nodeValsMatrix m, std::vector<int> ids){
  mat = m;
  used_ids = ids;
}

_Graph(nodeValsMatrix m){
  mat = m;
  std::vector<int> empty = {};
  used_ids = empty;
}

};

using nodeValsMatrix = std::vector<std::vector<nodeVals>>;

// TODO - write a func that makes the graph matrix
nodeValsMatrix generate_graph_mat(std::vector<nodeVals> nodes){
  int n = nodes.size;

  nodeValsMatrix res;

  return res;
}




/////////////////
// STORING OLD CODE HERE - delta stepping old implementation
// int get_node_index(Node target, nodeList nodelist){
//   if (!contains(nodelist, target)){
//     return -1
//   }
//
//   for (int i = 0; i < nodelist.size(); i++){
//     if (nodelist[i] == target){
//       return i;
//     }
//   }
// }
//
//
// std::vector<std::pair<Node, int>> compute_leads_to(Node dest, Graph graph){
// // THIS IS BROKEN. NEEDS UPDATING.
// // also code not tested, likely doesn't work.
//
//
//   std::vector<std::pair<Node, int>> res = {};
//   for (int i = 0; i < graph.nodes.size(); i++ ){
//     // for every list of nodes
//     nodeList currlist = graph.nodes[i];
//
//     if (currlist.head == dest){ // don't check itself
//       continue;
//     }
//
//     for (int j = 0; j < currlist[i].size(); j++){
//       // if dest node is in [some node]'s adjacency list,
//       if (contains(currlist, dest)){ // add it
//         int index = get_node_index(dest);
//         int cost = currlist.edge_weights[index]; // get cost of going from source to dest
//         int tentative = currlist.head.value; //assigned distance of source
//
//         res.push_back(std::make_pair(currlist[j], tentative+cost));
//       }
//     }
//
//   }
//
//   return res;
// }
//
// std::vector<std::pair<Node, int>> findRequests(Graph graph, nodeList Vprime, int kind){
//   // returns set of (w, tent(v) + c(v, w)) s.t. v in V' and (v,w) edge is of type [kind]
//   std::vector<std::pair<Node, int>> request_set;
//
//   // if (!graph.check_assigned()){
//   //   graph.assign(); // assign if needed
//   // }
//
//   for (int i = 0; i < graph.nodes.size(); i++){ // for every list of nodes
//     for (int j = 0; j < graph.nodes[i].size(); j++){ // for every node
//
//       if ((kind == LIGHT && graph.nodes[i].value <= graph.delta) || ((kind == HEAVY) && graph.nodes[i].value > graph.delta)){
//         // criterion #1 hit! it is of the correct kind
//         if (contains(Vprime, graph.nodes[i])){ // if node is in Vprime
//           // criterion #2 hit!
//
//           // add it to the request set
//           std::vector<std::pair<Node, int>> connected = compute_leads_to(graph.nodes[i], graph); // connected gives us the list of w's.
//           for (auto it = connected.begin(); it < connected.end(); it++){
//
//             request_set.push_back(*it);
//           }
//
//         }
//
//       }
//
//     }
//   }
//   return request_set;
//
// }
