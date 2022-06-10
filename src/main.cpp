#include "graphclass.cpp"

using nodeList = std::vector<Node>;

int main()
{
    std::cout << "running main" << std::endl;

    //tester code for printing funcs
    // Node node1(1);
    // Node node2(2);
    // Node node3(3);
    //
    //
    // adjacencyList test = {node2, node3};
    //
    // node1.adjList = test;
    // node1.printNode();
    //
    // std::cout << "-----------" << std::endl;
    // std::vector<Node> list = {node1, node2, node3};
    // printAdjList(list);


    // tester code for graphs & printing them
    Node node1(1, 1), node2(2, 2), node3(3, 3), node4(4, 4);
    std::cout << "testing insert" << std::endl;
    node1.insert(node4);

    nodeList for2 = {node4, node3};
    node2.insert_multiple(for2);

    nodeList for4 = {node1, node2};
    node4.insert_multiple(for4);

    node3.insert(node2);

    std::vector<Node> _nodes = {node1, node2, node3, node4};
    Graph _graph(_nodes);
    std::cout << _graph.is_empty() << endl;
    _graph.printGraph();



    return 0;
}
