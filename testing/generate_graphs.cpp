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
  cout << "sizes: " << input_mat.size() << "x" << input_mat[0].size() << endl;  
  for (int i = 0; i < input_mat.size(); i++){
    for (int j = 0; j < input_mat[0].size(); j++){
      cout << "pair at " << i << "," << j << input_mat[i][j].first << input_mat[i][j].second << endl;
    }
  }
  cout << "end of print" << endl;
}

sequentialGraph generate_sequentialGraph(int maxint){ // BROKEN FUNCTION - to be fixed soon
  sequentialGraph result = sequentialGraph();
  vector<int> random_starts = generate_random_intlist(maxint);
  vector<int> random_dests = generate_random_intlist(maxint);
  vector<int> random_weights = generate_random_intlist(maxint);
  vector<vector<int>> input(maxint);
  cout << "random starts, dests and weights are" << endl;
  print_int_vect(random_starts);
  cout << "\n" << endl;
  print_int_vect(random_dests);
  cout << "\n" << endl;
  print_int_vect(random_weights);
  cout << "\n" << endl;
  cout << " we made it!" << endl;
  cout << "input size is" << input.size() << "x" << input[0].size() << endl;

  for (int i = 0; i < maxint; i++){
    cout << "inside the loop " << i << endl;
    vector<int> row = {random_starts[i], random_dests[i], random_weights[i]};
    for (int j = 0; j < 3; j++){
      cout << "pushing back.. " << j << endl;
      input[i].push_back(row[j]);
      cout << "pushed" << endl;
    }


  }

  cout << "printing input matrix" << endl;
  for (int i = 0; i < input.size(); i++){
    for (int j = 0; j < input[0].size(); j++){
      cout << "pos " << i << "," << j << ": " << input[i][j] << endl;
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
