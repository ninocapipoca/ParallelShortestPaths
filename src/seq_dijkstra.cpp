#include <vector>
#include <algorithm>
#include <queue>
#include <initializer_list> 

#define INT_MAX 255


using std::vector;
using std::pair;

typedef std::priority_queue<pair<int,int>, vector<pair<int,int>>,
    std::greater<pair<int,int>>> MinHeap;
//The heap sorting criteria will be the distance as indicated in the paper


//this implementation is taken from Shiran Afergan's video on Dijkstra's
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

std::pair<vector<int>,vector<int>> dijkstra(Graph g, int source){
    //Create minHeap sorted by distance
    MinHeap minHeap;
    vector<int> dist(g.nNodes+1, INT_MAX);
    vector<int> prev(g.nNodes+1, -1);
    vector<bool> visited(g.nNodes+1, false);

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
            if(not visited[nextNode] and nextDist< dist[nextNode]){
                dist[nextNode] = nextDist;
                prev[nextNode] = curNode;
                minHeap.push({nextDist, nextNode});
            }
        }
    }
    return {dist, prev};
}