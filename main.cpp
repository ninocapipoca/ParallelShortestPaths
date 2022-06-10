#include "graphclass.cpp"

int main()
{
    std::cout << "running main" << std::endl;

    //tester code for printing func
    Node node1(1);
    Node node2(2);
    Node node3(3);


    adjacencyList test = {node2, node3};

    node1.adjList = test;
    node1.printNode();

    std::cout << "-----------" << std::endl;
    std::vector<Node> list = {node1, node2, node3};
    printAdjList(list);


    return 0;
}
