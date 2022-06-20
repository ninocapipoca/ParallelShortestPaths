// class Graph{
//     public:
//         vector<vector<std::pair<int, int>>> adj;
//         int nNodes;
//         void generateGraph(vector<vector<int>> &input, int n){
//             nNodes = n;
//             adj.resize(nNodes+1);
//             for(int i=0; i<input.size(); i++){
//                 adj[input[i][0]].push_back({input[i][1], input[i][2]});
//             }
//         }
//         void clear(){
//             adj.clear();
//         }
// };

#include <cstdlib> // for randomness
#include <iostream>
#include "../src/seq_dijkstra.cpp" // sequential implementation
#include "../src/parallel_dijkstra.cpp" // parallel implementation
#include "generate_graphs.cpp"
using namespace std;

using DijkstraResult = std::pair<vector<int>,vector<int>>;

// bool seq_correct(sequentialGraph graph, int start, DijkstraResult expected){
//   DijkstraResult algo_res = dijkstra(graph, start);
//   return algo_res == expected;
// }

// these tests will not work yet
// they assume that the dijkstra algorithm has a start and end node
bool autotest_sequential(){
  //dijkstra(sequentialGraph g, int source)
  // FOR GRAPHS OF 1 NODE

  vector<vector<int>> input = {{1, 1, 2}}
  vector<int> nodes_passed = {1};
  vector<int> edges_passed = {2};
  DijkstraResult expected = make_pair(nodes_passed,edges_passed);

  sequentialGraph graph = sequentialGraph(&input, input.size());
  if (expected != dijkstra(graph, 1, 1)){
    cout << "failed test 1 of 20" << endl;
    return false;
  }


  input = {{0, 1, 3},
          {0, 3, 2},
          {0, 8, 4},
          {8, 4, 8},
          {3, 4, 1},
          {3, 2, 6},
          {1, 7, 4},
          {7, 2, 2},
          {6, 5, 8},
          {5, 2, 1}};

  // from node 0 to node 7

  nodes_passed = {1, 7}; // nodes to pass through
  edges_passed = {3, 4}; // weights
  graph = sequentialGraph(&input, input.size());
  expected = make_pair(nodes_passed, edges_passed); // for start at 0
  if (expected != dijkstra(graph, 0, 7)){
    cout << "failed test 2 of 20" << endl;
    return false;
  }

  // from node 5 to node 8
  nodes_passed = {2, 7, 1, 0, 8};
  edges_passed = {1, 2, 4, 3, 4};
  expected = make_pair(nodes_passed, edges_passed); // for start at 0
  if (expected != dijkstra(graph, 5, 8)){
    cout << "failed test 3 of 20" << endl;
    return false;
  }

  input = {{1, 2, 1},
           {1, 3, 2},
           {1, 4, 3},
           {2, 3, 5},
           {3, 4, 8},
           {4, 5, 10},
           {5, 1, 4},
           {2 ,4, 6},
           {3, 5, 9},
           { }}

  // FOR GRAPHS OF 10 NODES

  // FOR GRAPHS OF 15 NODES

}
