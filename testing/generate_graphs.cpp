// class Graph{
//     public:
//         vector<vector<pair<int, int>>> adj;
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
using namespace std;

vector<int> generate_intlist(int maxlen){
  // generates a sequential list of integers
  vector<int> res;
  for (int i = 0; i < maxlen; i++){
    res.push_back(i);
  }
  return res;
}

bool list_contains(vector<int> list, int target){
  // returns whether list contains target
  for (int i = 0; i < list.size(); i++){
    if (list[i] == target){
      return true;
    }
  }
  return false;
}

vector<int> generate_random_intlist(int maxlen){
  // generates a random list of integers
  vector<int> result;
  for (int i = 0; i < maxlen; i++){
    int random_int = rand() % maxlen; // generates random int between 0 & maxlen
    while (list_contains(result, random_int)){
      random_int = rand() % maxlen;
    }
    result.push_back(random_int);
  }
  return result;
}

void print_int_vect(vector<int> input_vect){
  for (int i = 0; i < input_vect.size(); i++){
    cout << input_vect[i] << " , ";
  }
}

void print_pair_vect(vector<pair<int, int>> input_vect){
  for (int i = 0; i < input_vect.size(); i++){
    cout << input_vect[i].first << " " << input_vect[i].second << endl;
  }
  }


void print_mat(vector<vector<pair<int,int>>> input_mat){
  for (int i = 0; i < input_mat.size(); i++){
    cout << i << endl;
    print_pair_vect(input_mat[i]);
  }
}

sequentialGraph generate_sequentialGraph(int maxint){ // BROKEN FUNCTION - to be fixed soon
  sequentialGraph result = sequentialGraph();
  vector<int> random_starts = generate_random_intlist(maxint);
  vector<int> random_dests = generate_random_intlist(maxint);
  vector<int> random_weights = generate_random_intlist(maxint);
  vector<vector<int>> input = { {} };
  cout << "random starts are" << endl;
  print_int_vect(random_weights);
  cout << " we made it!" << endl;

  for (int i = 0; i < maxint; i++){
    cout << "inside the loop " << i << endl;
    vector<int> row = {random_starts[i], random_dests[i], random_weights[i]};
    cout << "row created" << endl;
    print_int_vect(row);
    cout << "row printed" << endl;
    for (int j = 0; j < 3; j++){
      cout << "pushing back.. " << j << endl;
      input[i].push_back(row[j]);
      cout << "pushed" << endl;
    }

  }

  result.generateGraph(input, maxint);

return result;
}




int main(){
  bool sequential = true;
  int maxint = 5;

  if (sequential){
    cout << "inside if" << endl;
    sequentialGraph first = generate_sequentialGraph(maxint);
    cout << "we made it this far" << endl;
    print_mat(first.adj);
  }

}
