// source -https://www.sciencedirect.com/science/article/pii/S0196677403000762?via%3Dihub

// TO DO - Implement sequential algorithm first maybe (or at least understand it)
// TO DO - Implement parallel algorithm

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

requestList findRequests(Graph graph, nodeList V_prime, bool kind){
  // if node is in the nodelist AND is of type [kind] then add it
  requestList request_set;

  // check that all nodes have been assigned a label
  if (!graph.check_assigned()){
    graph.assign(); // assign if needed
  }

  // ok. now all labelled. iterate through nodes and check conditions
  for (auto ptr = graph.nodes.begin(); ptr < graph.nodes.end(); ptr++){
    if (ptr->light == NULL){ // if even 1 not assigned, return false
      return false;
    }
  }
}
