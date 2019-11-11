#include <iostream>

//#include "list.h"
#include "arrList.h"

enum errCode {
    TESTS_FAILED = 13,
};

//bool findElemChecker(List <int> *list, int val);
//
//bool getElemChecker(List <int> *list, int awaitVal);
//
//bool pushFrontChecker(List <int> *list, int awaitVal);
//
//bool pushBackChecker(List <int> *list, int awaitVal);
//
//bool insertAfterChecker(List <int> *list, Node <int> *node, int awaitVal);
//
//bool insertBeforeChecker(List <int> *list, Node <int> *node, int awaitVal);

int tests();

int main() {
//    int failedTests = tests();
//    if (failedTests) {
//        printf("\n%d tests failed\n", failedTests);
//        return TESTS_FAILED;
//    }
//    auto *myList = new List <int> (3);
//
//    myList->pushFront(2);
//    myList->pushBack(5);
//    myList->pushBack(7);
//
//    Node <int> *node = myList->findElem(5);
//
//    myList->insertAfter(node, 6);
//    myList->insertBefore(node, 4);

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

//    myList->clear();
//    myList->pushFront(100);
//
//    myList->dump();
//    myList->listOk();
//    delete myList;

    auto *arrList = new ArrList <int> (100);

    arrList->pushBack(50);
    arrList->pushFront(15);
    arrList->pushFront(10);
    arrList->pushBack(60);

    size_t elem = arrList->elemAfter(arrList->getHead());

    arrList->insertAfter(elem, 55);
    arrList->insertBefore(elem, 40);
//    arrList->deleteElem(elem);

//    arrList->sort();

    arrList->dump();
    arrList->listOk();

    delete arrList;
    return 0;
}

//int tests() {
//    auto *testList = new List <int> (5);
//    int errors = 0;
//
//    printf("1 ");
//    !findElemChecker(testList, 5) ? errors++ : NULL;
//
//    printf("2 ");
//    !getElemChecker(testList, 5) ? errors++ : NULL;
//
//    printf("3 ");
//    !pushFrontChecker(testList, 2) ? errors++ : NULL;
//
//    printf("4 ");
//    !pushBackChecker(testList, 10) ? errors++ : NULL;
//
//    printf("5 ");
//    !insertAfterChecker(testList, testList->getTail(), 55) ? errors++ : NULL;
//
//    printf("6 ");
//    !insertBeforeChecker(testList, testList->getHead(), 3) ? errors++ : NULL;
//
//    testList->dump();
//
//    delete testList;
//    return errors;
//}
//
//bool findElemChecker(List <int> *list, int val) {
//    Node <int> *foundElem = list->findElem(val);
//
//    if (!foundElem) {
//        printf("Error:\n"
//               "Elem not found\n");
//        return false;
//    }
//    printf("success\n");
//    return true;
//}
//
//bool getElemChecker(List <int> *list, int awaitVal) {
//    Node <int> *foundElem = list->findElem(awaitVal);
//    int getVal = list->getValue(foundElem);
//
//    if (getVal != awaitVal) {
//        printf("Error:\n"
//               "Got value is not awaited:\n"
//               "  got: %d\n"
//               "await: %d\n", getVal, awaitVal);
//        return false;
//    }
//
//    printf("success\n");
//    return true;
//}
//
//bool pushFrontChecker(List <int> *list, int awaitVal) {
//    list->pushFront(awaitVal);
//    int gotVal = list->getValue(list->getHead());
//
//    if (gotVal != awaitVal) {
//        printf("Error:\n"
//               "Push front failed:\n"
//               "  got: %d\n"
//               "await: %d\n", gotVal, awaitVal);
//        return false;
//    }
//
//    printf("success\n");
//    return true;
//}
//
//bool pushBackChecker(List <int> *list, int awaitVal) {
//    list->pushBack(awaitVal);
//    int gotVal = list->getValue(list->getTail());
//
//    if (gotVal != awaitVal) {
//        printf("Error:\n"
//               "Push back failed:\n"
//               "  got: %d\n"
//               "await: %d\n", gotVal, awaitVal);
//        return false;
//    }
//
//    printf("success\n");
//    return true;
//}
//
//bool insertAfterChecker(List <int> *list, Node <int> *node, int awaitVal) {
//    list->insertAfter(node, awaitVal);
//    int gotVal = list->getValue(list->elemAfter(node));
//
//    if (gotVal != awaitVal) {
//        printf("Error:\n"
//               "Insert after failed:\n"
//               "  got: %d\n"
//               "await: %d\n", gotVal, awaitVal);
//        return false;
//    }
//
//    printf("success\n");
//    return true;
//}
//
//bool insertBeforeChecker(List <int> *list, Node <int> *node, int awaitVal) {
//    list->insertBefore(node, awaitVal);
//    int gotVal = list->getValue(list->elemBefore(node));
//
//    if (gotVal != awaitVal) {
//        printf("Error:\n"
//               "Insert before failed:\n"
//               "  got: %d\n"
//               "await: %d\n", gotVal, awaitVal);
//        return false;
//    }
//
//    printf("success\n");
//    return true;
//}
