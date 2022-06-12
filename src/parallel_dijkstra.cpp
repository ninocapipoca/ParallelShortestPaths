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
#include <iterator>

using std::vector;
using std::pair;
//the algorithm keeps a global array for all tentative distance values
//each processor is responsible for two sequential priority queues

 vector<int> tent;


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

std::pair<vector<int>,vector<int>> parallel_dijkstra (Graph g, int source,
auto start, auto end );

// Num SumParallel(NumIter begin, NumIter end, Num f(Num), size_t num_threads) {
//     // YOUR CODE HERE
//     unsigned long const length = std::distance(begin,end);//length of the vector
//     if(!length) return 0.;

//     unsigned long const block_size = length/num_threads;

//     std::vector<Num> results(num_threads, 0.);
//     std::vector<std::thread> workers(num_threads - 1);
//     NumIter start_block = begin;
//     for(size_t i=0; i<num_threads-1; ++i){
//         NumIter end_block = start_block + block_size; 
//         workers[i] = std::thread(&SumMapThread, start_block, end_block,f,
//         std::ref(results[i]));
//         start_block = end_block;
//     }
//     SumMapThread(start_block, end,f, results[num_threads - 1]);
//     for (size_t i = 0; i < num_threads - 1; ++i) {
//         workers[i].join();
//     }

//     Num total_result = 0.;
//     for (size_t i = 0; i < results.size(); ++i) {
//         total_result += results[i];
//     }
//     return total_result;
//     return 0;
// }



void parallel_coordinator(size_t num_threads,Graph g, int source){
    
    unsigned long const block_size = tent.size()/num_threads;//do we add -1 to vectors?
    auto startIter = tent.begin();
    
    vector<std::thread> workers(num_threads - 1);//excluding the thread we 
    //currently run in

    for(size_t i=0; i<num_threads; ++i){
        auto endIter = startIter + block_size;
        workers[i] = std::thread(&parallel_dijkstra,g,source,startIter,endIter);
        startIter = endIter;
    } 



}

