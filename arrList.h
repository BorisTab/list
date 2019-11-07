//
// Created by boristab on 07.11.2019.
//

#include <iostream>
#include <stack>
#include <fstream>
#include <cassert>

enum errors {
    SUCCESS = 0,
    FILE_OPEN_FAILED = 1,
};

const char dumpFilePath[FILENAME_MAX] = "../ArrListDumpFile.txt";

template <class elemType>
class ArrNode {
public:
    elemType value = {};
    size_t next = 0;
    size_t prev = 0;
};

template <class elemType>
class ArrList {
private:
    size_t size = 0;
    size_t maxSize = 0;
    ArrNode <elemType> *nodeArray = nullptr;
    size_t head = 0;
    size_t tail = 0;
    std::stack <size_t> freePosStack = {};

    size_t setNewVal(elemType val) {
        size_t freePos = freePosStack.top();
        freePosStack.pop();

        nodeArray[freePos].value = val;

        return freePos;
    }

public:
    explicit ArrList(size_t maxSize) {
        this->maxSize = maxSize;
        nodeArray = new ArrNode <elemType> [maxSize] ();

        nodeArray[0].next = 0;
        nodeArray[0].prev = 0;

        for (size_t i = maxSize; i > 0; i--) {
            freePosStack.push(i);
        }
    }

    ~ArrList() {
        delete [] nodeArray;
        head = 0;
        tail = 0;
        maxSize = 0;
    }

    void pushBack(elemType val) {
        size_t elemPos = setNewVal(val);

        if (size == 0) {
            head = elemPos;
        } else {
            nodeArray[elemPos].next = 0;
            nodeArray[elemPos].prev = tail;
            nodeArray[tail].next = elemPos;
        }

        tail = elemPos;
        size++;
    }

    void pushFront(elemType val) {
        size_t elemPos = setNewVal(val);

        if (size == 0) {
            tail = elemPos;
        } else {
            nodeArray[elemPos].next = head;
            nodeArray[elemPos].prev = 0;
            nodeArray[head].prev = elemPos;
        }

        head = elemPos;
        size++;
    }

    void insertAfter(size_t insertAfterNode, elemType val) {
        assert(insertAfterNode);

        size_t elemPos = setNewVal(val);

        nodeArray[elemPos].next = nodeArray[insertAfterNode].next;
        nodeArray[elemPos].prev = insertAfterNode;
        nodeArray[nodeArray[insertAfterNode].next].prev = elemPos;
        nodeArray[insertAfterNode].next = elemPos;
        size++;
    }

    void insertBefore(size_t insertBeforeNode, elemType val) {
        assert(insertBeforeNode);

        size_t elemPos = setNewVal(val);

        nodeArray[elemPos].next = insertBeforeNode;
        nodeArray[elemPos].prev = nodeArray[insertBeforeNode].prev;
        nodeArray[nodeArray[insertBeforeNode].prev].next = elemPos;
        nodeArray[insertBeforeNode].prev = elemPos;
        size++;
    }

    size_t getHead() {
        return head;
    }

    size_t getTail() {
        return tail;
    }

    size_t getSize() {
        return size;
    }

    size_t elemAfter(size_t elemPos) {
        assert(elemPos);

        return nodeArray[elemPos].next;
    }

    size_t elemBefore(size_t elemPos) {
        assert(elemPos);

        return nodeArray[elemPos].prev;
    }

    void deleteElem(size_t elemPos) {
        assert(elemPos);

        if (nodeArray[elemPos].prev) {
            nodeArray[nodeArray[elemPos].prev].next = nodeArray[elemPos].next;

        }

        if (nodeArray[elemPos].next) {
            nodeArray[nodeArray[elemPos].next].prev = nodeArray[elemPos].prev;
        }

        freePosStack.push(elemPos);
        size--;
    }

    size_t findElem(elemType val) {
        size_t valPos = 0;

        size_t currentPos = head;
        while (currentPos) {
            if (nodeArray[currentPos].value == val) {
                valPos = currentPos;
                break;
            }
            currentPos = nodeArray[currentPos].next;
        }

        return valPos;
    }

    size_t getElemById(size_t id) {
        size_t idNode = head;

        for(size_t i = 0; i < id; i++) {
            idNode = nodeArray[idNode].next;
        }

        return idNode;
    }

    void clear() {
        if (!head) return;

        size_t currentPos = head;

        while (currentPos) {
            size_t nextPos = nodeArray[currentPos].next;
            deleteElem(currentPos);
            currentPos = nextPos;
        }

        head = 0;
        tail = 0;
    }

    elemType getValue(size_t elemPos) {
        return nodeArray[elemPos].value;
    }

    void dump() {
        std::ofstream dumpFile (dumpFilePath);
        if (!dumpFile) {
            std::cout << "File isn't open\n";
            exit(FILE_OPEN_FAILED);
        }

        dumpFile << "digraph G{\n";
        dumpFile << "\"Size: " << size <<"\";\n";

        if (head) {
            size_t elemPos = head;
            while (elemPos) {
                dumpFile << "node_" << elemPos << " [shape=record, label=\" " << elemPos << " | Val: " << nodeArray[elemPos].value << " \"];\n";
                elemPos = nodeArray[elemPos].next;
            }

            dumpFile << "head->node_" << head << ";\n";
            elemPos = head;
            while (nodeArray[elemPos].next) {
                dumpFile << "node_" << elemPos << "->node_" << nodeArray[elemPos].next << ";\n";
                dumpFile << "node_" << nodeArray[elemPos].next << "->node_" << elemPos << ";\n";
                elemPos = nodeArray[elemPos].next;
            }
            dumpFile << "node_" << tail << "->tail;\n";
        }

        dumpFile << "}\n";

        dumpFile.close();

        char dotCommand[FILENAME_MAX] = "";
        sprintf(dotCommand, "dot -Tpng -O %s", dumpFilePath);
        std::system(dotCommand);
    }

    int listOk() {
        size_t sizeChecker = 0;
        size_t currentPos = head;
        int errCount = 0;

        while (currentPos) {
            sizeChecker++;
            currentPos = nodeArray[currentPos].next;
        }

        if (sizeChecker != size) {
            printf("Wrong size:\n "
                   "  got: %ld\n"
                   "await: %ld\n", sizeChecker, size);
            errCount++;
        }

        currentPos = head;
        for (size_t i = 1; i < size; i++) {
            if (!currentPos) {
                printf("Wrong pointer to node\n");
                errCount++;
            }
            currentPos = nodeArray[currentPos].next;
        }

        if (currentPos != tail) {
            printf("List doesn't reach the tail\n");
            errCount++;
        }

        for (size_t i = 1; i < size; i++) {
            if (!currentPos) {
                printf("Wrong pointer to node\n");
                errCount++;
            }
            currentPos = nodeArray[currentPos].prev;
        }

        if (currentPos != head) {
            printf("List doesn't reach the head\n");
            errCount++;
        }

        if(errCount) {
            printf("%d errors\n", errCount);
        } else {
            printf("List is OK\n");
        }

        return errCount;
    }
};