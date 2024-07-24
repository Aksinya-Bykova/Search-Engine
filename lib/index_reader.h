#ifndef LABWORK11_INDEX_READER_H
#define LABWORK11_INDEX_READER_H

#include "directory_walk.h"

void parse_csv(const fs::path& path, const std::string& word, std::vector<size_t>& list) {
    std::string filename = path.string();
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::string line;
    std::getline(file, line);

    std::vector<std::string> tokens;
    bool found = false;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        while (std::getline(ss, token, ',')) {
            if (found) {
                tokens.push_back(token);
            }
            if (token == word) {
                found = true;
            }
        }
        if (found) {
            break;
        }

        std::vector<size_t> result = {};
    }

    if (tokens.empty()) {
        return;
    }

    for (size_t i = 0; i < tokens.size(); ++i) {
        list.push_back(std::stoi(tokens[i]));
    }
    std::cout << std::endl;

    file.close();
}

void get_positions(const fs::path& path, const std::string& word,
                          std::map<std::string, std::vector<size_t>>& index) {
    std::vector<size_t> list;
    parse_csv(path, word, list);
    index[path] = list;
}

std::map<std::string, std::vector<size_t>> read(const fs::path& path, const std::string& word) {
    std::map<std::string, std::vector<size_t>> index;
    recursive_directory_walk(path, get_positions, word, index);
    return index;
}

#endif //LABWORK11_INDEX_READER_H
