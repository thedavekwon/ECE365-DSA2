//
// Created by Do Hyung Kwon on 9/15/19.
//

#include <iostream>
#include "../include/hash.h"

// https://planetmath.org/goodhashtableprimes
std::vector<int> hashTable::primes = {24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469};

// hash function
unsigned int hashTable::hash(const std::string &key) {
    unsigned int hashVal = 0;
    for (auto c : key)
        hashVal = 37 * hashVal + c;
    return hashVal % capacity;
}

unsigned hashTable::findPos(const std::string &key) {
    unsigned int currentPos = hash(key);
    while (data[currentPos].isOccupied && !data[currentPos].isDeleted && data[currentPos].key != key) {
        currentPos = (currentPos + 1) % capacity;
    }
    return currentPos;
}

bool hashTable::rehash() {
    std::vector<hashItem> oldData = data;
    // check memory error
    try {
        unsigned int new_size = getPrime(capacity + 1);
        data.resize(new_size);
        capacity = new_size;
    } catch (std::bad_alloc &exc) {
        return false;
    }

    filled = 0;
    for (auto &item : data) {
        item.isOccupied = false;
        item.isDeleted = false;
    }
    for (auto &item : oldData) {
        if (!item.isDeleted && item.isOccupied) insert(item.key, item.pv);
    }
    return true;
}

unsigned int hashTable::getPrime(int size) {
    return *lower_bound(primes.begin(), primes.end(), size);
}

hashTable::hashTable(int size) {
    data.resize(size);
    capacity = size;
    filled = 0;
}

int hashTable::insert(const std::string &key, void *pv) {
    unsigned int currentPos = findPos(key);
    if (data[currentPos].isOccupied && data[currentPos].key == key) return 1;

    data[currentPos].key = key;
    data[currentPos].isOccupied = true;
    data[currentPos].isDeleted = false;
    data[currentPos].pv = pv;

    if (++filled > capacity / 2)
        if (!rehash())
            return 2;

    return 0;
}

bool hashTable::contains(const std::string &key) {
    auto pos = findPos(key);
    return data[pos].isOccupied && !data[pos].isDeleted;
}

void *hashTable::getPointer(const std::string &key, bool *b) {
    unsigned int currentPos = findPos(key);
    if (b != nullptr) *b = false;
    if (!data[currentPos].isOccupied) { return nullptr; }
    if (b != nullptr) *b = true;
    return data[currentPos].pv;
}

int hashTable::setPointer(const std::string &key, void *pv) {
    unsigned int currentPos = findPos(key);
    if (!data[currentPos].isOccupied) return 1;
    data[currentPos].pv = pv;
    return 0;
}

bool hashTable::remove(const std::string &key) {
    unsigned int currentPos = findPos(key);
    if (!data[currentPos].isOccupied) return false;
    data[currentPos].isDeleted = true;
    data[currentPos].isOccupied = false;
    return true;
}

void hashTable::printContent() {
    for (auto &item : data) std::cout << item.isOccupied << " ";
    std::cout << std::endl;

    for (auto &item : data) std::cout << item.isDeleted << " ";
    std::cout << std::endl;

    for (auto &item : data) {
        if (item.key == "") std::cout << " ";
        std::cout << item.key << " ";
    }
    std::cout << std::endl;

    std::cout << filled << "/" << capacity << std::endl;
}