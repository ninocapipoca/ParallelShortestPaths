//this algorithm is build on a octa core processor

#include <vector>
#include <algorithm>
#include <queue>
#include <algorithm>
#include <atomic>
#include <mutex>
#include <thread>
#include <numeric>
#include <boost/pending/relaxed_heap.hpp>


//the algorithm keeps a global array for all tentative distance values
//each processor is responsible for two sequential priority queues
using std::vector;
using std::pair;
 
// typedef relaxed_heap<Vertex, IndirectCmp, IndexMap> MutableQueue;



//try to implement using Fibonnaci heap, if doesn't work, use min heap

typedef std::priority_queue<pair<int,int>, vector<pair<int,int>>,
    std::greater<pair<int,int>>> MinHeap;

class Graph{
    public:
        vector<vector<std::pair<int, int>>> adj;
        int nNodes;
        void generateGraph(vector<vector<int>> &input, int n){
            nNodes = n;
            adj.resize(nNodes+1);
            for(int i=0; i<input.size(); i++){
                adj[input[i][0]].push_back({input[i][1], input[i][2]});
            }
        }
        void clear(){
            adj.clear();
        }
};


std::pair<vector<int>,vector<int>> p_dijkstra(Graph g, int source){
    relaxed_heap 



}

for(size_t i=0; i<num_threads-1; ++i){
        NumIter end_block = start_block + block_size; 
        workers[i] = std::thread(&SumMapThread, start_block, end_block,f,
        std::ref(results[i]));
        start_block = end_block;
    }