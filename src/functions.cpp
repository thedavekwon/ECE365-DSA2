#include "../include/functions.h"

bool check_valid_word(const std::string& s) {
    if (s.size() > 20) return false;
    for (auto c : s) if (check_invalid_character(c)) return false;
    return true;
}

bool check_invalid_character(char c) {
    return !isdigit(c) && !isalpha(c) && c != '-' && c != '\'';
}

void create_dictionary(const std::string& dictionary_file, hashTable* dict) {
    auto start = std::chrono::system_clock::now();
    std::ifstream dictionary(dictionary_file);
    int cnt = 0;
    if (dictionary.is_open()) {
        std::string word;
        while (dictionary >> word) {
            if (check_valid_word(word)) {
                to_lower_case(word);
                dict->insert(word);
                cnt++;
            }
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Total time (in seconds) to load dictionary:";
    std::cout << elapsed.count() << std::endl;
}

void spell_check(const std::string& input_file, const std::string& output_file, hashTable* dict) {
    auto start = std::chrono::system_clock::now();
    std::ifstream input(input_file);
    std::ofstream output(output_file);

    int line_cnt = 0;
    if (input.is_open()) {
        std::string line;
        while (std::getline(input, line)) {
            line_cnt++;
            auto parsed = split(line);
            for (auto &word : parsed) {
                to_lower_case(word);
                if (word.size() > 20) report_error(output, word, line_cnt, true);
                else if (!dict->contains(word)) report_error(output, word, line_cnt, false);
            }
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Total time (in seconds) to check document: ";
    std::cout << elapsed.count() << std::endl;
}

std::vector<std::string> split(const std::string &line) {
    std::vector<std::string> tokens;
    int idx = 0;
    for (int i = 0; i < line.size(); i++) {
        if (check_invalid_character(line[i])|| line[i] == ' ') {
            if (i != idx) tokens.push_back(line.substr(idx, i-idx));
            idx = i+1;
        }
    }
    if (idx != line.size()) tokens.push_back(line.substr(idx, line.size()-idx));
    return tokens;
}

void to_lower_case(std::string &word) {
    for (auto &w : word) {
        w = tolower(w);
    }
}

void report_error(std::ofstream &output, const std::string &word, int line_cnt, bool is_long) {
    if (is_long) {
        output << "Long word at line " << line_cnt << ", starts: " << word.substr(0, 20) << std::endl;
    } else {
        output << "Unknown word at line " << line_cnt << ": " << word << std::endl;
    }
}