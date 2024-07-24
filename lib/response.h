#ifndef LABWORK11_RESPONSE_H
#define LABWORK11_RESPONSE_H

#include <unordered_set>
#include "request_parser.h"
#include "index_generator.h"
#include "index_reader.h"
#include "rangement.h"

const std::string META_PATH = "../META";
const std::string TEMPORARY_PATH = "../TEMPORARY/temporary_result.csv";

std::map<std::string, std::vector<size_t>> merge_maps(const std::map<std::string, std::vector<size_t>>& left_map,
                                                      const std::map<std::string, std::vector<size_t>>& right_map,
                                                      const std::string& operand) {
    if (operand.empty()) {
        return left_map;
    }

    if (operand == "OR") {
        std::map<std::string, std::vector<size_t>> res;

        for (const auto& pair: left_map) {
            std::unordered_set<size_t> uniqueValues(pair.second.begin(), pair.second.end());
            res[pair.first] = std::vector<size_t>(uniqueValues.begin(), uniqueValues.end());
        }

        for (const auto& pair: right_map) {
            for (size_t value: pair.second) {
                if (res[pair.first].end() == std::find(res[pair.first].begin(),
                                                       res[pair.first].end(), value)) {
                    res[pair.first].push_back(value);
                }
            }
        }

        return res;
    }

    std::map<std::string, std::vector<size_t>> res;

    for (const auto& pair: left_map) {
        auto it = right_map.find(pair.first);
        if (it != right_map.end()) {
            std::vector<size_t> commonValues;
            const std::vector<size_t>& vec1 = pair.second;
            const std::vector<size_t>& vec2 = it->second;
            std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::back_inserter(commonValues));
            if (!commonValues.empty()) {
                res[pair.first] = commonValues;
            }
        }
    }

    return res;
}

std::map<std::string, std::vector<size_t>> process_brackets(const Request<std::string>& request) {
    if (request.left.empty()) {
        return {};
    }
    if (request.operand.empty()) {
        return read(META_PATH, request.left);
    }

    return merge_maps(read(META_PATH, request.left),
                      read(META_PATH, request.right),
                      request.operand);
}

void response() {
    Input inp;
    Request<Request<std::string>> req = inp.get_request();

    std::map<std::string, std::vector<size_t>> left_map = process_brackets(req.left);
    std::map<std::string, std::vector<size_t>> right_map = process_brackets(req.right);
    std::map<std::string, std::vector<size_t>> result_map = merge_maps(left_map, right_map, req.operand);

    generate_csv_file(TEMPORARY_PATH, range(result_map));
}

#endif //LABWORK11_RESPONSE_H
