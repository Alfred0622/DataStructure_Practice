#include "Red_Black_Tree.h"

int main()
{
	std::cout << "Initiate Tree1"<< std::endl;
    RBT tree1;

    std::cout << "Initiate Node1"<< std::endl;
    Node node1 ;
    std::cout << "Initiate Node2 as 5"<< std::endl;

    Node node2(5);

    std::cout << "Initiate Tree2"<< std::endl;
    RBT tree2(&node2);

    tree2.print();   

    std::cout << "insert 1,8,9,4"<< std::endl;
    tree2.insert(1);
    tree2.print();    
    std::cout << "insert 8,9,4"<< std::endl;
    tree2.insert(8);
    std::cout << "insert 9,4"<< std::endl;
    tree2.insert(9);
    std::cout << "insert 4"<< std::endl;
    tree2.insert(4);

    std::cout << "search 4,3 "<< std::endl;
    tree2.search(4);
    tree2.search(3);

    std::cout << "erase 9 , 4"<< std::endl;
    tree2.erase(9);
    tree2.erase(4);
    
    std::cout << "print tree2"<< std::endl;
    tree2.print();

    return 0;
}