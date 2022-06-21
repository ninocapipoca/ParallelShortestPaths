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

#define LIGHT   true
#define HEAVY   false



requestList findRequests(nodeList V_p, bool kind, Graph graph){
  // kind is either light or heavy

  requestList res = {};
  // iterate through nodes in graph
  for (int i = 0; i < graph.nodes.size(); i++){
    nodeList reachable_nodes = {};

    // iterate through nodes in node list
    for (int j = 0; j < V_p.size(); j++){

      // if reachable
      if (graph.reachable(V_p[j], graph.nodes[i])){

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

    return res;
}

void relax(double delta, std::vector<Bucket> &bucketList, Node &w, double x){
  if (x < w.estimate){
    int in = floor(w.estimate / delta);
    if (contains(bucketList[in].contents, w)){
      bucketList[in].contents.remove(w);
    }
    bucketList[floor(x/delta)].contents.insert(w);
  }
}

void relaxRequests(std::vector<Request> requests){

}



// return path of nodes one needs
// to follow shortest path
nodeList delta_stepping(Graph* graph, Node* start, Node* dest){
  std::vector<Bucket> bucketList;
  // initialise list of buckets
  int nr_buckets = graph.find_nr_buckets();
  for (int n = 0; n < nr_buckets; n++){
    bucketList.push_back(Bucket(n));
  }

  nodeList unvisited = graph->nodes;
  // first make sure all tentative distances are infinity
  for (int i = 0; i < graph->nodes.size(); i++){
    if (graph->nodes[i].estimate != inf){
      graph->nodes[i].estimate = inf;
    }
  }

  Node sourceNode = Node();
  // relax (s,0)
  relax(delta, &bucketList, &sourceNode, 0);
  while (unvisited.size() > 0){
    int smallest = smallest_nonempty(bucketList);
    nodeList deleted = {};
    while (bucketList[smallest].contents.size() != 0){
      requestList requests = findRequests(bucketList[smallest].content, LIGHT, graph);
      transfer_deleted(&deleted, bucketList[smallest].contents);
      bucketList[smallest].contents = {}; // make bucket empty


      // do relaxRequests(req)
      // UNFINISHED
      // double delta, std::vector<Bucket> &bucketList, Node &w, double x
      for (int i = 0; i < requests.size(); i++){
        relax(graph.delta, &bucketList, &(requests[i].end_node), requests[i].calculated_value);
      }

      requests = findRequests(deleted, HEAVY);
      for (int i = 0; i < requests.size(); i++){
        relax(graph.delta, &bucketList, &(requests[i].end_node), requests[i].calculated_value);
      }
    }
  }
