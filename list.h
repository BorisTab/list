//
// Created by boristab on 06.11.2019.
//
#include <iostream>
#include <fstream>
#include <cassert>

enum errors {
    SUCCESS = 0,
    FILE_OPEN_FAILED = 1,
};

const char dumpFilePath[FILENAME_MAX] = "../ListDumpFile.txt";

template <class elemType>
class Node {
public:
    Node <elemType> *nextPointer = nullptr;
    Node <elemType> *previousPointer = nullptr;
    elemType value = {};

    explicit Node(elemType value) {
        this->value = value;
    }
};

template <class elemType>
class List {
private:
    Node <elemType> *head = nullptr;
    Node <elemType> *tail = nullptr;
    size_t size = 0;

    Node<elemType> *newNode(elemType val) {
        return new Node <elemType> (val);
    }

public:
    explicit List(elemType val){
        auto *node = newNode(val);

        head = node;
        tail = node;
        size = 1;
    }

    List() = default;

    ~List() {
        Node<elemType> *currentNode = head;
        while (currentNode->nextPointer) {
            currentNode = currentNode->nextPointer;
            delete currentNode->previousPointer;
        }
        delete tail;
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    void pushBack(elemType val) {
        auto *node = newNode(val);

        if (size == 0) {
            head = node;
            tail = node;
        } else {
            node->nextPointer = nullptr;
            node->previousPointer = tail;
            tail->nextPointer = node;
            tail = node;
        }
        size++;
    }

    void pushFront(elemType val) {
        auto *node = newNode(val);

        if (size == 0) {
            head = node;
            tail = node;
        } else {
            node->nextPointer = head;
            node->previousPointer = nullptr;
            head->previousPointer = node;
            head = node;
        }
        size++;
    }

    void insertAfter(Node <elemType> *insertAfterNode, elemType val) {
        assert(insertAfterNode);

        auto *node = newNode(val);

        node->nextPointer = insertAfterNode->nextPointer;
        node->previousPointer = insertAfterNode;
        (*(insertAfterNode->nextPointer)).previousPointer = node;
        insertAfterNode->nextPointer = node;
        size++;
    }

    void insertBefore(Node <elemType> *insertBeforeNode, elemType val) {
        assert(insertBeforeNode);

        auto *node = newNode(val);

        node->nextPointer = insertBeforeNode;
        node->previousPointer = insertBeforeNode->previousPointer;
        (*(insertBeforeNode->previousPointer)).nextPointer = node;
        insertBeforeNode->previousPointer = node;
        size++;
    }

    Node <elemType> *getHead() {
        return head;
    }

    Node <elemType> *getTail() {
        return tail;
    }

    size_t getSize() {
        return size;
    }

    Node <elemType> *elemAfter(Node <elemType> *node) {
        assert(node);

        return node->nextPointer;
    }

    Node <elemType> *elemBefore(Node <elemType> *node) {
        assert(node);

        return node->previousPointer;
    }

    void deleteElem(Node <elemType> *node) {
        assert(node);

        (*(node->previousPointer)).nextPointer = node->nextPointer;
        (*(node->nextPointer)).previousPointer = node->previousPointer;

        delete node;
    }

    Node <elemType> *findElem(elemType val) {
        Node <elemType> *valPointer = nullptr;

        Node <elemType> *currentPointer = head;
        while (currentPointer) {
            if (currentPointer->value == val) {
                valPointer = currentPointer;
                break;
            }
            currentPointer = currentPointer->nextPointer;
        }

        return valPointer;
    }

    Node <elemType> *getElemById(size_t id) {
        Node <elemType> *idNode = head;

        for (size_t i = 0; i < id; i++) {
            idNode = idNode->nextPointer;
        }

        return idNode;
    }

    void dump() {
        std::ofstream  dumpFile (dumpFilePath);
        if (!dumpFile) {
            std::cout << "File isn't open\n";
            exit(FILE_OPEN_FAILED);
        }

        dumpFile << "digraph G{\n";
        dumpFile << "\"Size: " << size <<"\";\n";

        Node<elemType> *currentNode = head;
        while (currentNode) {
            dumpFile << "node_" << currentNode << " [shape=record, label=\" " <<  currentNode << " | Val: " << currentNode->value <<" \"];\n";

            currentNode = currentNode->nextPointer;
        }

        dumpFile << "head->node_" << head << ";\n";
        currentNode = head;
        while (currentNode->nextPointer) {
            dumpFile << "node_" << currentNode << "->" << "node_" << currentNode->nextPointer << ";\n";
            dumpFile << "node_" << currentNode->nextPointer << "->" << "node_" << currentNode << ";\n";

            currentNode = currentNode->nextPointer;
        }
        dumpFile << "node_" << tail << "->tail;";
        dumpFile << "\n}\n";

        dumpFile.close();

        char dotCommand[FILENAME_MAX] = "";
        sprintf(dotCommand, "dot -Tpng -O %s", dumpFilePath);
        std::system(dotCommand);
    }

    void listOk() {
        size_t sizeChecker = 0;
        Node <elemType> *currentNode = head;

        while (currentNode) {
            sizeChecker++;
            currentNode = currentNode->nextPointer;
        }

        if (sizeChecker != size) {
            printf("Wrong size:\n "
                   "  got: %ld\n"
                   "await: %ld\n", sizeChecker, size);
        }

        currentNode = head;
        for (size_t i = 1; i < size; i++) {
            if (!currentNode) {
                printf("Wrong pointer to node\n");
            }
            currentNode = currentNode->nextPointer;
        }

        if (currentNode != tail) {
            printf("List doesn't reach the tail\n");
        }

        for (size_t i = 1; i < size; i++) {
            if (!currentNode) {
                printf("Wrong pointer to node\n");
            }
            currentNode = currentNode->previousPointer;
        }

        if (currentNode != head) {
            printf("List doesn't reach the head\n");
        }
    }
};
