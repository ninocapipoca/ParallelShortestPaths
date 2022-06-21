#include <iostream>
#include <cmath>
#include <vector>
#include <limits>

#define UNDEF 3
#define _LIGHT 4
#define _HEAVY 5

using binaryMatrix = std::vector<std::vector<int>>;
using Matrix = std::vector<std::vector<double>>;

double inf = numeric_limits<double>::max();
int max_id = 0;




class matNode{
private:
  std::string id;
  int kind;
  double assigned_val;
  std::vector<double> edge_costs;
  std::vector<matNode> adj_nodes;
public:
  matNode();
  matNode(int k);
  matNode(int k, double val);
  matNode(int k, double val, std::vector<double> costs, std::vector<matNode> adj);
  ~matNode(); // destructor

  bool contained_in(std::vector<matNode> nodeList);


};
