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
#include <limits>

#define INT_MAX std::numeric_limits<int>::max()

using std::vector;
using std::pair;
//the algorithm keeps a global array for all tentative distance values
//each processor is responsible for two sequential priority queues

vector<int> tent;


//In step one we want to find the globaly mimnimal L
int global_L = INT_MAX;//this will be the only part that is exclusive read/write
std::mutex global_L_mutex;



//try to implement using Fibonnaci heap, if doesn't work, use min heap

typedef std::priority_queue<pair<int,int>, vector<pair<int,int>>,
    std::greater<pair<int,int>>> MinHeap;


//this graph implementation is taken from Shiran Afergan's video on Dijkstra's
//algorithm on Youtube: 
//https://www.youtube.com/watch?v=pLElbKBc4RU&t=169s&ab_channel=ShiranAfergan


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
vector<MinHeap>::iterator start, vector<MinHeap>::iterator end );

void find_mininmal_L(Graph g, int source,vector<MinHeap>::iterator start, vector<MinHeap>::iterator end);

void can_be_deleted();


//four steps of a phse according to the paper:
//step1: find the global minumum L of all elements in all Q_star queues
//should be preformed in Ologp <= Ologn time 
void parallel_coordinator(size_t num_threads,Graph g, int source){
    
    unsigned long const block_size = tent.size()/num_threads;//do we add -1 to vectors?
    auto startIter = tent.begin();//I should make sure that start iter
    //is the source for each of the queue pairs 
    
    vector<std::thread> workers(num_threads - 1);//excluding the thread we 
    // vector<pair<vector<int>,vector<int> > > q
    // (num_threads-1, pair<vector<int>,vector<int> >(block_size-1,block_size-1));
    vector<MinHeap> q_and_q_star(num_threads-1);//vector of priority queue pairs realized by a heap
    //vector of pairs of vectors
    //each pair consists of a distance and a node vector
    //each pair is managed by one of the threads
    //all queues are initialized empty;


    q_and_q_star[0].push({0,source});//adding source node and it's distance
    //from the source, which is 0.

    while(!q_and_q_star.empty()){//as the paper states
        for(int j=0; j<num_threads;j++){
            if(!q_and_q_star[j].empty()){
                auto endIter = startIter + block_size;
                workers[j] = std::thread(&find_mininmal_L,g,source+j*block_size
                ,startIter,endIter);//this is first step
            }
            startIter = startIter + j*block_size;
        }
        for (size_t i = 0; i < num_threads - 1; ++i) {
            workers[i].join();
        }
        //Here I should implement step 2
    }
}



//remove if not minimal
std::pair<vector<int>,vector<int> > remove_not_minimal(Graph g, int source,
int dist_source, vector<MinHeap>::iterator start,
 vector<MinHeap>::iterator end){
    int length = std::distance(start,end);
    MinHeap minHeap;
    vector<int> dist(length-1, INT_MAX);
    vector<int> prev(length-1, -1);
    vector<bool> visited(length-1, false);

    dist[source] = dist_source;
    minHeap.push({dist_source, source});

    while(!minHeap.empty()){
        auto curDist = minHeap.top().first;
        auto curNode = minHeap.top().second;
        minHeap.pop();
        if(visited[curNode]) continue;
        for (auto &x: g.adj[curNode]){//first is node second is weight
            auto nextNode = x.first;
            auto nextWeight = x.second;
            int nextDist = curDist + nextWeight;
            if(not (visited[nextNode]) and (nextDist < global_L)){
                dist[nextNode] = nextDist;
                prev[nextNode] = curNode;
                minHeap.push({nextDist, nextNode});
            }
        }
    }
    return {dist, prev};

}

std::pair<vector<int>,vector<int> > parallel_dijkstra (Graph g, int source,
vector<MinHeap>::iterator start, vector<MinHeap>::iterator end ){


    int length = std::distance(start,end);
    //distance from a source to itself should be zero
    MinHeap minHeap;
    vector<int> dist(length-1, INT_MAX);
    vector<int> prev(length-1, -1);
    vector<bool> visited(length-1, false);

    dist[source] = 0;
    minHeap.push({0, source});

    while(!minHeap.empty()){
        auto curDist = minHeap.top().first;
        auto curNode = minHeap.top().second;
        minHeap.pop();
        if(visited[curNode]) continue;
        for (auto &x: g.adj[curNode]){//first is node second is weight
            auto nextNode = x.first;
            auto nextWeight = x.second;
            int nextDist = curDist + nextWeight;
            if(not (visited[nextNode]) and (nextDist< dist[nextNode])){
                dist[nextNode] = nextDist;
                prev[nextNode] = curNode;
                minHeap.push({nextDist, nextNode});
            }
        }
    }
    return {dist, prev};
}

//finds minimal L by comparing the global L to the local distances in the 
//q,q_star pairs
void find_mininmal_L(Graph g, int source,vector<MinHeap>::iterator start, vector<MinHeap>::iterator end){
    while(start!=end){
        auto curDist = start->top().first;
        auto curNode = start->top().second;
        global_L_mutex.lock();
        if(curDist<global_L){
            global_L = curDist;
        }
        global_L_mutex.unlock();
        start++;
    }
}