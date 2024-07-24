#ifndef LABWORK11_RANGEMENT_H
#define LABWORK11_RANGEMENT_H

#include <map>
#include <algorithm>
#include <cmath>

const double k = 1; // align parameter, effect of repeated terms on relevance
const double b = 1; // align parameter, effect of document length on relevance
double dl_avg; // average document length

std::map<std::string, double> file_length; // pair document-dl (length)
double N = file_length.size(); // number of documents

double score(double tf, double df, double dl) {
    return (tf * (k + 1) * log(N / df)) / (tf + k * (1 - b + b * dl / dl_avg));
}

void set_metrics() {
    for (auto el : file_length) {
        dl_avg += el.second / N;
    }
}

bool compare(const std::pair<std::string, double>& p1,
             const std::pair<std::string, double>& p2) {
    return p1.second < p2.second;
}

std::vector<std::pair<std::string, std::vector<size_t>>>
range(std::map<std::string, std::vector<size_t>>& index) {
    std::vector<std::pair<std::string, double>> doc_scores;
    double df = index.size();

    for (auto el: index) {
        std::string document = el.first;
        double tf = el.second.size();
        double dl = file_length[el.first];
        doc_scores.push_back({el.first, score(tf, df, dl)});
    }

    sort(doc_scores.begin(), doc_scores.end(), compare);

    std::vector<std::pair<std::string, std::vector<size_t>>> result;

    for (auto el: doc_scores) {
        result.push_back({el.first, index[el.first]});
    }

    return result;
}

#endif //LABWORK11_RANGEMENT_H
