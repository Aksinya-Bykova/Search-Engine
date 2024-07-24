#ifndef LABWORK11_DIRECTORY_WALK_H
#define LABWORK11_DIRECTORY_WALK_H

#include <filesystem>
#include <iostream>
#include <functional>

namespace fs = std::filesystem;

void recursive_directory_walk(const fs::path& path,
                              const std::function<void(const fs::path&)>& file_processor) {
    for (const auto& entry: fs::directory_iterator(path)) {
        if (fs::is_directory(entry)) {
            recursive_directory_walk(entry, file_processor);
        } else {
            try {
                file_processor(entry);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}

void recursive_directory_walk(const fs::path& path,
                              const std::function<void(const fs::path&, const std::string&,
                                                        std::map<std::string, std::vector<size_t>>& index)>& file_processor,
                              const std::string& word,
                                      std::map<std::string, std::vector<size_t>>& index) {
    for (const auto& entry: fs::directory_iterator(path)) {
        if (fs::is_directory(entry)) {
            recursive_directory_walk(entry, file_processor, word, index);
        } else {
            try {
                file_processor(entry, word, index);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}

#endif //LABWORK11_DIRECTORY_WALK_H
