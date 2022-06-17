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


//we conseptioally have 3 vectors: tentative,queued,setelled
//practically, setelled is the output

// vector<pair<int, int> > tent;//this is the tentetive weight vector, first 
// //elemnt is the number of the vertex, second is the distance from the source


//In step one we want to find the globaly mimnimal L
int global_L = INT_MAX;//this will be the only part that is exclusive read/write
std::mutex global_L_mutex;
std::mutex global_request_mutex;



//try to implement using Fibonnaci heap, if doesn't work, use min heap

typedef std::priority_queue<pair<int,int>, vector<pair<int,int>>,
    std::greater<pair<int,int>>> MinHeap;
typedef int Node;
typedef int Weight;
typedef int Distance;
typedef vector<pair<Node, Distance> > ReqSet;
typedef vector<Distance> Tent;


//this graph implementation is taken from Shiran Afergan's video on Dijkstra's
//algorithm on Youtube: 
//https://www.youtube.com/watch?v=pLElbKBc4RU&t=169s&ab_channel=ShiranAfergan


class Graph{
    public:
        vector<vector<std::pair<int, int>>> adj;
        vector<vector<std::pair<int, int>>> buf;//gonna use later according to the buffers on the paper
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

void find_mininmal_L(Graph g,vector<MinHeap>::iterator start, vector<MinHeap>::iterator end);
void remove_not_minimal(Graph g, vector<int> tent, vector<MinHeap>::iterator start,
 vector<MinHeap>::iterator end, vector<pair<int,int> > requests);
void gen_req_set(Graph g, ReqSet set, vector<pair<int,int> >::iterator start,
vector<pair<int,int> >::iterator end,vector<pair<int,int> > requests,Tent tent);
void place_into_buffer(Graph g,ReqSet set,ReqSet::iterator start,
ReqSet::iterator end,vector<std::mutex> mutex_vec);


//four steps of a phse according to the paper:
//step1: find the global minumum L of all elements in all Q_star queues
//should be preformed in Ologp <= Ologn time 
void parallel_coordinator(size_t num_threads,Graph g, int source){
    
    unsigned long const block_size = g.adj.size()/num_threads;//do we add -1 to vectors?
    // auto startIter = tent.begin();//I should make sure that start iter
    // // is the source for each of the queue pairs 
    
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

    Tent tent(g.adj.size());//it is not stated clearly at the paper
    // but I assume that this vector should be constatnly maintained
    for(int weight:tent){
        tent[weight] = INT_MAX;
    }
    tent[source]  = 0;
    //at the first iteration the distance of all nodes from the source is 
    //the maximum available

    auto startIter = q_and_q_star.begin();

    vector<std::mutex> mutex_vec(g.adj.size());

    while(!q_and_q_star.empty()){//as the paper states
        for(int j=0; j<num_threads-1;j++){//maybe put num_threads-1?
            if(!q_and_q_star[j].empty()){
                auto endIter = startIter + block_size;
                workers[j] = std::thread(&find_mininmal_L,g,startIter,endIter);//this is first step
            }
            startIter = q_and_q_star.begin() + j*block_size;
        }
        find_mininmal_L(g,startIter,q_and_q_star.end());
        for (size_t i = 0; i < num_threads - 1; ++i) {
            workers[i].join();
        }
        //Here I should implement step 2
        vector<pair<int,int> > requests;
        startIter = q_and_q_star.begin();
        for(int j=0; j<num_threads-1; j++){//maybe put num_threads-1?
            if(!q_and_q_star[j].empty()){
                auto endIter = startIter + block_size;
                workers[j] = std::thread(&remove_not_minimal,g,tent,startIter,
                endIter, std::ref(requests),
                std::ref(q_and_q_star));
            }
            startIter = q_and_q_star.begin() + j*block_size;
        }
        remove_not_minimal(g,tent,startIter,q_and_q_star.end(),
        std::ref(requests));
        for(size_t i = 0 ; i< num_threads - 1; ++i){
            workers[i].join();
        }
        ReqSet req;
        auto startIter_requests = requests.begin();
        int block_size_requests = requests.size()/num_threads;
        for(int j=0; j<num_threads-1; j++){//maybe put num_threads-1?
            auto endIter_requests = startIter_requests + block_size_requests;
            workers[j] = std::thread(&gen_req_set,g,std::ref(req),startIter_requests,
            endIter_requests,requests,tent);
            startIter_requests = endIter_requests;
        }
        gen_req_set(g,std::ref(req),startIter_requests,requests.end(),requests,tent);
        for(size_t i = 0 ; i< num_threads - 1; ++i){
            workers[i].join();
        }
        auto startIter_req = req.begin();
        int block_size_req = req.size()/num_threads;
        for(int j=0; j<num_threads-1;j++){
            auto endIter_req = startIter_req + block_size_req;
            workers[j] = std::thread(&place_into_buffer,std::ref(g),
            req,startIter_req,endIter_req,std::ref(mutex_vec));
            startIter_req = endIter_req;
        }
        place_into_buffer(std::ref(g),req,startIter_req,req.end(),
        std::ref(mutex_vec));
        for(size_t i = 0 ; i< num_threads - 1; ++i){
            workers[i].join();
        }
    }
}



//remove if not minimal
void remove_not_minimal(Graph g,vector<int> tent,
vector<MinHeap>::iterator start,
vector<MinHeap>::iterator end,vector<pair<int,int> > requests){
    while(start!=end){
        auto curDist = start->top().first;
        auto curNode = start->top().second;
        if(tent[curNode]<=global_L){
            global_request_mutex.lock();
            requests.push_back({curNode,curDist});
            start->pop();
            global_request_mutex.unlock();
        }
        start++;
    }
}

//finds minimal L by comparing the global L to the local distances in the 
//q,q_star pairs
void find_mininmal_L(Graph g,vector<MinHeap>::iterator start,
vector<MinHeap>::iterator end){
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

void gen_req_set(Graph g, ReqSet set, vector<pair<int,int> >::iterator start,
vector<pair<int,int> >::iterator end, vector<pair<int,int> > requests,
Tent tent){
    while(start!=end){
        for(auto& x : g.adj[start->first]){
            auto nextNode = x.first;
            auto nextWeight = x.second;
            global_request_mutex.lock();
            set.push_back({start->first,tent[start->first]+nextWeight});
            global_request_mutex.unlock();
        }
        start++;
    }
}

void place_into_buffer(Graph g,ReqSet set,ReqSet::iterator start,
ReqSet::iterator end,vector<std::mutex> mutex_vec){
    while(start!=end){
        mutex_vec[start->first].lock();
        int temp = start->first;
        g.buf[start->first].push_back({start->first,start->second});
        start++;
        mutex_vec[temp].unlock();
    }
}