#ifndef LABWORK11_CSV_GENERATE_H
#define LABWORK11_CSV_GENERATE_H

#include <fstream>
#include "rangement.h"

void generate_csv_file(const std::string& filename,
                       const std::map<std::string, std::vector<size_t>>& data) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error creating CSV file: " + std::string(filename));
    }

    file_length[filename] = data.size();

    file << "Key,Values\n";

    for (const auto& entry: data) {
        file << entry.first << ",";
        for (size_t i = 0; i < entry.second.size(); ++i) {
            file << entry.second[i];
            if (i < entry.second.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
}

void generate_csv_file(const std::string& filename,
                       const std::vector<std::pair<std::string, std::vector<size_t>>>& data) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error creating CSV file: " + std::string(filename));
    }

    file << "Key,Values\n";

    for (const auto& entry: data) {
        if (entry.second.size() == 0) {
            continue;
        }
        file << entry.first << ",";
        for (size_t i = 0; i < entry.second.size(); ++i) {
            file << entry.second[i];
            if (i < entry.second.size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }

    file.close();
}

#endif //LABWORK11_CSV_GENERATE_H
