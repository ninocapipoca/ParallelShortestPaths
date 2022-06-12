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

using nodeList = std::vector<Node>;
using requestList = std::vector<Request>;

// REQUEST STRUCT
// start node, end node, cost of going from start to end, and tentative value
// double t_value;
// in order: t_value, start, end, cost

// NOTE - for a node, the 'weight' property describes the weight
// of the edge to get to that node

// find all nodes that have an edge to dest. node
// and the cost of those edges tent(source) + c(source, dest)
int get_node_index(Node target, nodeList nodelist){
  if (!contains(nodelist, target)){
    return -1
  }

  for (int i = 0; i < nodelist.size(); i++){
    if (nodelist[i] == target){
      return i;
    }
  }
}


std::vector<std::pair<Node, int>> compute_leads_to(Node dest, Graph graph){
// THIS IS BROKEN. NEEDS UPDATING.
// also code not tested, likely doesn't work.


  std::vector<std::pair<Node, int>> res = {};
  for (int i = 0; i < graph.nodes.size(); i++ ){
    // for every list of nodes
    nodeList currlist = graph.nodes[i];

    if (currlist.head == dest){ // don't check itself
      continue;
    }

    for (int j = 0; j < currlist[i].size(); j++){
      // if dest node is in [some node]'s adjacency list,
      if (contains(currlist, dest)){ // add it
        int index = get_node_index(dest);
        int cost = currlist.edge_weights[index]; // get cost of going from source to dest
        int tentative = currlist.head.value; //assigned distance of source

        res.push_back(std::make_pair(currlist[j], tentative+cost));
      }
    }

  }

  return res;
}

std::vector<std::pair<Node, int>> findRequests(Graph graph, nodeList Vprime, int kind){
  // returns set of (w, tent(v) + c(v, w)) s.t. v in V' and (v,w) edge is of type [kind]
  std::vector<std::pair<Node, int>> request_set;

  if (!graph.check_assigned()){
    graph.assign(); // assign if needed
  }

  for (int i = 0; i < graph.nodes.size(); i++){ // for every list of nodes
    for (int j = 0; j < graph.nodes[i].size(); j++){ // for every node

      if ((kind == LIGHT && graph.nodes[i].value <= graph.delta) || ((kind == HEAVY) && graph.nodes[i].value > graph.delta)){
        // criterion #1 hit! it is of the correct kind
        if (contains(Vprime, graph.nodes[i])){ // if node is in Vprime
          // criterion #2 hit!

          // add it to the request set
          std::vector<std::pair<Node, int>> connected = compute_leads_to(graph.nodes[i], graph);
          for (auto it = connected.begin(); it < connected.end(); it++){
            request_set.push_back(*it);
          }

        }

      }

    }
  }
  return request_set;

}
