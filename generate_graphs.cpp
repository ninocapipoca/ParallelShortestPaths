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

int main(int argc, char *argv[]){
  if (argv > 1){
    std::cout << "too many arguments. use: [nr of nodes]" << endl;
  }
}
