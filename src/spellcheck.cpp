//
// Created by Do Hyung Kwon on 9/15/19.
//
#include "../include/functions.h"

#include <iostream>

int main() {
    std::string dictionary_file, input_file, output_file;

    std::cout << "Enter name of dictionary: ";
    std::cin >> dictionary_file;

    std::cout << "Enter name of input file: ";
    std::cin >> input_file;

    std::cout << "Enter name of output file: ";
    std::cin >> output_file;

    auto dict = new hashTable(hashTable::primes[0]);

    create_dictionary(dictionary_file, dict);
    spell_check(input_file, output_file, dict);
}