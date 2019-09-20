//
// Created by Do Hyung Kwon on 9/15/19.
//

#include <iostream>
#include "../include/hash.h"

// https://planetmath.org/goodhashtableprimes
std::vector<int> hashTable::primes = {3, 7, 17, 33, 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157,
                                      98317};

// hash function
unsigned int hashTable::hash(const std::string &key) {
    unsigned int hashVal = 0;
    for (auto c : key)
        hashVal = 37 * hashVal + c;
    return hashVal % capacity;
}

unsigned hashTable::findPos(const std::string &key) {
    unsigned int currentPos = hash(key);
    while ((data[currentPos].isOccupied || data[currentPos].isDeleted) && data[currentPos].key != key) {
        currentPos = (currentPos + 1) % capacity;
    }
    return currentPos;
}

bool hashTable::rehash() {
    std::vector<hashItem> oldData = data;
    // check memory error
    try {
        unsigned int new_size = getPrime(capacity+1);
        data.resize(new_size);
        capacity = new_size;
    } catch (std::bad_alloc &exc) {
        return false;
    }

    filled = 0;
    for (auto &item : data) {
        item.isOccupied = false;
        item.isDeleted = false;
        item.key = "";
    }
    for (auto &item : oldData) {
        if (!item.isDeleted && item.isOccupied) insert(std::move(item.key));
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
    // for (auto &item : data) data.isOccupied = false;
}

int hashTable::insert(const std::string &key, void *pv) {
    unsigned int currentPos = findPos(key);
    if (data[currentPos].isOccupied && data[currentPos].key == key) return 1;

    // reset
    data[currentPos].key = key;
    data[currentPos].isOccupied = true;
    data[currentPos].isDeleted = false;

    if (++filled > capacity / 2)
        if (!rehash())
            return 2;

    return 0;
}

bool hashTable::contains(const std::string &key) {
    return data[findPos(key)].isOccupied;
}

void *hashTable::getPointer(const std::string &key, bool *b) {

}

int hashTable::setPointer(const std::string &key, void *pv) {

}

bool hashTable::remove(const std::string &key) {
    int currentPos = findPos(key);
    if (!data[currentPos].isOccupied) return false;
    data[currentPos].isDeleted = true;
    return true;
}

void hashTable::printContent() {
//    for (auto &item : data) {
//        std::cout << item.isOccupied << " ";
//    }
//    std::cout << std::endl;
//
//    for (auto &item : data) {
//        std::cout << item.isDeleted << " ";
//    }
//    std::cout << std::endl;
//
//    for (auto &item : data) {
//        if (item.key == "") std::cout << " ";
//        std::cout << item.key << " ";
//    }
//    std::cout << std::endl;
    std::cout << filled << "/" << capacity << std::endl;
}