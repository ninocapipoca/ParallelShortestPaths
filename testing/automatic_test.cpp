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

bool seq_correct(sequentialGraph graph, int start, DijkstraResult expected){
  DijkstraResult algo_res = dijkstra(graph, start);
  return algo_res == expected;
}

bool autotest_sequential(){
  //dijkstra(sequentialGraph g, int source)
  // FOR GRAPHS OF 1 NODE
  vector<vector<int>> input = {{1, 1, 2}} // starts at 1, ends at 1, cost is 2
  DijkstraResult expected = make_pair(1,2);
  if (!seq_correct(graph1, expected)){
    cout << "failed on test 1 of 1 node graphs" << endl;
    return false;
  }

  // FOR GRAPHS OF 5 NODES
  vector<vector<int>> input = {{1, 1, 2}} // starts at 1, ends at 1, cost is 2
  sequentialGraph graph_1 = sequentialGraph(&input, 1);

  // FOR GRAPHS OF 10 NODES

  // FOR GRAPHS OF 15 NODES

}
