// File: query_processor.cpp

#include "query_processor.h"
#include <sstream>
#include <unordered_map>

QueryProcessor::QueryProcessor(const InvertedIndex& index) : index(index) {}

std::vector<int> QueryProcessor::processQuery(const std::string& query) const {
    std::vector<std::string> terms = parseQuery(query);
    std::vector<int> resultIds = searchTerms(terms);
    rankResults(resultIds);
    return resultIds;
}

void QueryProcessor::rankResults(std::vector<int>& resultIds) const {
    // Implement ranking logic based on term frequency, document relevance, etc.
    // For simplicity, you might initially just sort the document IDs
    std::sort(resultIds.begin(), resultIds.end());
    // Eliminate duplicates
    resultIds.erase(std::unique(resultIds.begin(), resultIds.end()), resultIds.end());
}

std::vector<std::string> QueryProcessor::parseQuery(const std::string& query) const {
    std::istringstream iss(query);
    std::vector<std::string> terms;
    std::string term;
    while (iss >> term) {
        terms.push_back(term);
    }
    return terms;
}

std::vector<int> QueryProcessor::searchTerms(const std::vector<std::string>& terms) const {
    std::unordered_map<int, int> docFrequency;

    for (const auto& term : terms) {
        // Assuming 'index' can return a list of document IDs for each term
        auto docIds = index.search(term); 
        if (docIds) {
            for (const auto& docId : *docIds) {
                docFrequency[docId]++;
            }
        }
    }

    std::vector<int> resultIds;
    for (const auto& entry : docFrequency) {
        resultIds.push_back(entry.first); // or use some threshold based on entry.second (frequency)
    }

    return resultIds;
}
