//
// Created by Do Hyung Kwon on 9/15/19.
//
#include "../include/hash.h"

#include <iostream>
#include <fstream>

int main() {
    std::string dictionary_file, input_file, output_file;

    std::cout << "Enter name of dictionary: ";
    std::cin >> dictionary_file;

    std::cout << "Enter name of input file: ";
    std::cin >> input_file;

    std::cout << "Enter name of output file: ";
    std::cin >> output_file;

    auto dict = new hashTable(hashTable::primes[0]);

    std::ifstream dictionary(dictionary_file);
    int cnt = 0;
    if (dictionary.is_open()) {
        std::string s;
        while (dictionary >> s) {
            dict->printContent();
            dict->insert(s);
            cnt++;
        }
    }
    dict->printContent();

    std::cout << cnt << std::endl;
    dict->printContent();
}