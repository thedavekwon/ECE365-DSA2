#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <locale>
#include <chrono>

#include "hash.h"

bool check_valid_word(const std::string& s);
bool check_digits(const std::string& s);
void create_dictionary(const std::string& dictionary_file, hashTable* dict);
void spell_check(const std::string& input_file, const std::string& output_file, hashTable* dict);
std::vector<std::string> split(const std::string &line);
bool check_invalid_character(char c);
void to_lower_case(std::string &word);
void report_error(std::ofstream &output, const std::string &word, int line_cnt, bool is_long);

#endif
