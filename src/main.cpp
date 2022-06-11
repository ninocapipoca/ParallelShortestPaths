#include "graphclass.cpp"

using nodeList = std::vector<Node>;
using listVector = std::vector<linkedList>;

int main()
{
    std::cout << "running main" << std::endl;

    Node n1(1,1), n2(2,2), n3(3,3);
    nodeList test1 = { n2, n3};
    linkedList test = linkedList(n1, test1);

    nodeList test2 = {n1, n3};
    linkedList second_test = linkedList(n2, test2);

    n1.printNode();
    test.printLinkedList();

    std::cout << "\n testing graph print \n" << std::endl;
    listVector listvect = {test, second_test};
    Graph test_graph = Graph(listvect, 1.5);
    test_graph.printGraph();


    return 0;
}
