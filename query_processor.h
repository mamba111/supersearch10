// File: query_processor.h

#ifndef QUERY_PROCESSOR_H
#define QUERY_PROCESSOR_H

#include "inverted_index.h"
#include <string>
#include <vector>

class QueryProcessor {
public:
    QueryProcessor(const InvertedIndex& index);
    std::vector<int> processQuery(const std::string& query) const;
    void rankResults(std::vector<int>& resultIds) const;

private:
    const InvertedIndex& index;

    std::vector<std::string> parseQuery(const std::string& query) const;
    std::vector<int> searchTerms(const std::vector<std::string>& terms) const;
};

#endif // QUERY_PROCESSOR_H
