#include <iostream>

#include "list.h"

int main() {
    auto *myList = new List <int> (3);

    myList->pushFront(2);
    myList->pushBack(5);
    myList->pushBack(7);

    Node <int> *node = myList->findElem(5);

    myList->insertAfter(node, 6);
    myList->insertBefore(node, 4);

//    std::cout << "head: " << myList->getHead() << "\ntail: " << myList->getTail() << "\nsize: " << myList->getSize();
//
//    myList->deleteElem(node->nextPointer);
//
//    Node <int> *nodeAfter = myList->elemAfter(node);
//    Node <int> *nodeBefore = myList->elemBefore(node);
//
//    std::cout << "\nafter: " << nodeAfter << "\nbefore: " << nodeBefore;
//
//    Node <int> *nodeById = myList->getElemById(1);
//
//    std::cout << "\n1: " << nodeById;

    myList->dump();
    myList->listOk();

    delete myList;
    return 0;
}
