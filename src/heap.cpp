//
// Created by Do Hyung Kwon on 10/5/19.
//

#include "../include/heap.h"

#include <utility>

heap::node::node() = default;

heap::node::node(std::string _id, int _key, void *_pData) : id(std::move(_id)), key(_key), pData(_pData) {}

heap::heap(int capacity) : hTable(capacity * 2) {
    data.resize(capacity + 1);
    currentSize = 0;
}

int heap::insert(const std::string &id, int key, void *pv) {
    if (currentSize == data.size() - 1) return 1;
    if (hTable.contains(id)) return 2;
    if (DEBUG) print();
    data[0] = std::move(node(id, key, pv));
    int pos = ++currentSize;
    int newPos = percolateUp(pos);
    hTable.insert(id, &data[newPos]);
    if (DEBUG) print();
    return 0;
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (currentSize == 0) return 1;
    if (DEBUG) print();
    if (pId != nullptr) *pId = data[1].id;
    if (pKey != nullptr) *pKey = data[1].key;
    if (ppData != nullptr) *(static_cast<void **>(ppData)) = data[1].pData;
    hTable.remove(data[1].id);
    data[1] = std::move(data[currentSize--]);
    hTable.setPointer(data[1].id, &data[1]);
    percolateDown(1);
    if (DEBUG && pId) std::cout << *pId << std::endl;
    if (DEBUG && pKey) std::cout << *pKey << std::endl;
    if (DEBUG) print();
    return 0;
}

int heap::percolateUp(int curPos) {
    for (; data[0].key < data[curPos / 2].key; curPos /= 2) {
        data[curPos] = std::move(data[curPos / 2]);
        hTable.setPointer(data[curPos].id, &data[curPos]);
    }
    data[curPos] = std::move(data[0]);
    hTable.setPointer(data[curPos].id, &data[curPos]);
    return curPos;
}

int heap::percolateDown(int curPos) {
    int child;
    auto tmp = std::move(data[curPos]);
    for (; curPos * 2 <= currentSize; curPos = child) {
        child = curPos * 2;
        if (child != currentSize && data[child + 1].key < data[child].key) ++child;
        if (data[child].key < tmp.key) {
            data[curPos] = std::move(data[child]);
            hTable.setPointer(data[curPos].id, &data[curPos]);
        } else break;
    }
    data[curPos] = std::move(tmp);
    hTable.setPointer(data[curPos].id, &data[curPos]);
    return curPos;
}

int heap::getPos(heap::node *pn) {
    return static_cast<int>(pn - &data[0]);
}

int heap::setKey(const std::string &id, int key) {
    bool found;
    auto pv = static_cast<node *>(hTable.getPointer(id, &found));
    if (!found) return 1;
    int pos = getPos(pv);
    if (DEBUG) std::cout << "found pos: " << pos << std::endl;
    if (pv->key < key) increaseKey(pos, key);
    else if (pv->key > key) decreaseKey(pos, key);
    if (DEBUG) print();
    return 0;
}

int heap::decreaseKey(int pos, int key) {
    data[pos].key = key;
    data[0] = std::move(data[pos]);
    return percolateUp(pos);
}

int heap::increaseKey(int pos, int key) {
    data[pos].key = key;
    return percolateDown(pos);
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {
    bool found;
    auto pv = static_cast<node *>(hTable.getPointer(id, &found));
    if (!found) return 1;
    if (pKey) *pKey = pv->key;
    if (ppData) *(static_cast<void **>(ppData)) = pv->pData;
    int pos = getPos(pv);
    decreaseKey(pos, std::numeric_limits<int>::min());
    deleteMin();
    if (DEBUG) print();
    return 0;
}

void heap::print() {
    std::cout << "size: " << currentSize << std::endl;
    for (int i = 1; i <= currentSize; i++) {
        auto node = data[i];
        std::cout << node.key << " " << node.id << std::endl;
    }
}
