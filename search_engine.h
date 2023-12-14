// File: search_engine.h

#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "index_builder.h"
#include "query_processor.h"
#include <string>
#include <vector>

class SearchEngine {
public:
    SearchEngine();
    void indexDirectory(const std::string& dir);
    std::vector<int> query(const std::string& queryString);
    void loadIndex(const std::string& file);
    void saveIndex(const std::string& file);
    void printStats();
    void userInterface();

private:
    IndexBuilder indexBuilder;
    InvertedIndex invertedIndex;
    QueryProcessor* queryProcessor;
    // Other members related to file IO, stats, etc.
};

#endif // SEARCH_ENGINE_H
