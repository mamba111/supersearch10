// main.cpp
#include <iostream>
#include "search_engine.h"

int main(int argc, char *argv[]) {
    // Instantiate the search engine
    SearchEngine searchEngine;

    // Command line interface logic
    if (argc > 1) {
        std::string command = argv[1];

        if (command == "index") {
            // Call index function with provided collection path
            if (argc > 2) {
                searchEngine.index(argv[2]);
            } else {
                std::cerr << "No collection path provided for indexing." << std::endl;
            }
        } else if (command == "query") {
            // Call query function with provided query string
            if (argc > 2) {
                searchEngine.query(argv[2]);
            } else {
                std::cerr << "No query provided." << std::endl;
            }
        } else if (command == "UI") {
            // Launch the interactive user interface
            searchEngine.ui();
        } else {
            std::cerr << "Invalid command. Use 'index', 'query', or 'UI'." << std::endl;
        }
    } else {
        std::cerr << "No command provided. Use 'index', 'query', or 'UI'." << std::endl;
    }

    return 0;
}
