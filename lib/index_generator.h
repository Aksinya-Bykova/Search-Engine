#ifndef LABWORK11_INDEX_GENERATOR_H
#define LABWORK11_INDEX_GENERATOR_H

#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <sys/stat.h>
#include "directory_walk.h"
#include "csv_generate.h"

std::string replace_substring(const std::string& str, const std::string& old_str, const std::string& new_str) {
    std::string res = str;
    size_t pos = 0;
    while ((pos = res.find(old_str, pos)) != std::string::npos) {
        res.replace(pos, old_str.length(), new_str);
        pos += new_str.length();
    }

    return res;
}

std::string change_file_extension(const std::string& filename, const std::string& new_extension) {
    fs::path file_path(filename);
    file_path.replace_extension(new_extension);
    return file_path.string();
}

void set_index(const fs::path& path,
               const std::map<std::string, std::vector<size_t>>& index) {
    std::string meta_path = replace_substring(std::string(path), "FILES", "META");
    meta_path = change_file_extension(meta_path, "csv");

    fs::path p(meta_path);
    std::string directory_path = p.parent_path().string();
    try {
//        std::cout << directory_path << "\n";
        fs::create_directories(directory_path);
//        mkdir(directory_path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        generate_csv_file(meta_path, index);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void parse_words_from_line(const std::string& line, size_t pos,
                           std::map<std::string, std::vector<size_t>>& index) {
    std::istringstream iss(line);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    for (const auto& w: words) {
        index[w].push_back(pos);
    }
}

void process(const fs::path& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + std::string(path));
    }

    std::map<std::string, std::vector<size_t>> index;

    std::string line;
    size_t pos = 0;
    while (std::getline(file, line)) {
        parse_words_from_line(line, pos, index);
        ++pos;
    }

    file.close();
    set_index(path, index);
}

void generate(const fs::path& path) {
    recursive_directory_walk(path, process);
}

#endif //LABWORK11_INDEX_GENERATOR_H