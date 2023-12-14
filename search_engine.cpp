// File: search_engine.cpp

#include "search_engine.h"
#include <iostream>
// Other necessary includes

SearchEngine::SearchEngine() {
    // Initialize indexBuilder, invertedIndex, and queryProcessor
    queryProcessor = new QueryProcessor(invertedIndex);
}

SearchEngine::~SearchEngine() {
    delete queryProcessor;
}

void SearchEngine::indexDirectory(const std::string& dir) {
    // Assuming 'dir' is a directory path containing JSON files
    std::vector<Document> documents;
    
    // Code to iterate over files in the directory and parse them
    for (const auto& file : /* Directory iterator for 'dir' */) {
        Document doc;
        doc.parse(file.path().string());
        documents.push_back(doc);
    }

    // Build the index with the parsed documents
    invertedIndex = indexBuilder.build(documents);
}

std::vector<int> SearchEngine::query(const std::string& queryString) {
    // Process the query using the QueryProcessor
    auto resultIds = queryProcessor->processQuery(queryString);

    // Optionally, rank the results based on relevance
    queryProcessor->rankResults(resultIds);

    return resultIds;
}

void SearchEngine::loadIndex(const std::string& file) {
    // Load the index from a file
    // This would involve file IO and deserialization
}

void SearchEngine::saveIndex(const std::string& file) {
    // Save the index to a file
    // This would involve file IO and serialization
}

void SearchEngine::printStats() {
    // Print statistics about the index, such as number of documents, index size, etc.
}

void SearchEngine::userInterface() {
    while (true) {
        std::cout << "Search Engine\n";
        std::cout << "1. Index Directory\n";
        std::cout << "2. Search Query\n";
        std::cout << "3. Load Index\n";
        std::cout << "4. Save Index\n";
        std::cout << "5. Print Stats\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter choice: ";

        int choice;
        std::cin >> choice;

        std::string input;
        switch (choice) {
            case 1:
                std::cout << "Enter directory path: ";
                std::cin >> input;
                indexDirectory(input);
                break;
            case 2:
                std::cout << "Enter search query: ";
                std::cin.ignore(); // To clear the newline character from the stream
                std::getline(std::cin, input);
                query(input);
                break;
            // Cases for load index, save index, print stats
            case 6:
                return; // Exit the program
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

