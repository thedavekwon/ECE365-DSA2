//
// Created by dodo on 10/5/19.
//

#ifndef SPELLCHECK_HEAP_H
#define SPELLCHECK_HEAP_H

#include <limits>
#include <iostream>
#include <string>
#include <vector>
#include <utility>

#include "../include/hash.h"

#define DEBUG false

class heap {
public:
    // heap - The constructor allocates space for the nodes of the heap
    // and the mapping (hash table) based on the specified capacity
    explicit heap(int capacity);

    // insert - Inserts a new node into the binary heap
    //
    // Inserts a node with the specified id string, key,
    // and optionally a pointer. Then key is used to
    // determine the final position of the new node.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is already filled to capacity
    //   2 if a node with the given id already exists (but the heap
    //     is not filled to capacity)
    int insert(const std::string &id, int key, void *pv = nullptr);

    // setKey - set the key of the specified node to the specified value
    //
    // I have decided that the class should provide this member function
    // instead of two separate increaseKey and decreaseKey functions.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    int setKey(const std::string &id, int key);

    // deleteMin - return the data associated with the smallest key
    //             and delete that node from the binary heap
    //
    // If pId is supplied (i.e., it is not nullptr), write to that address
    // the id of the node being deleted. If pKey is supplied, write to
    // that address the key of the node being deleted. If ppData is
    // supplied, write to that address the associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if the heap is empty
    int deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr);

    // remove - delete the node with the specified id from the binary heap
    //
    // If pKey is supplied, write to that address the key of the node
    // being deleted. If ppData is supplied, write to that address the
    // associated void pointer.
    //
    // Returns:
    //   0 on success
    //   1 if a node with the given id does not exist
    int remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr);

    bool isempty();
private:
    class node {
    public:
        std::string id;
        int key;
        void *pData;

        node();

        node(std::string _id, int _key, void *_pData);
    };

    std::vector<node> data;
    hashTable hTable;
    int currentSize;

    int increaseKey(int pos, int keyDiff);

    int decreaseKey(int pos, int keyDiff);

    int percolateUp(int curPos);

    int percolateDown(int curPos);

    int getPos(node *pn);

    void print();
};

#endif //SPELLCHECK_HEAP_H
