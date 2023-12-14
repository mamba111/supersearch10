#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "IndexBuilder.h"
#include "InvertedIndex.h"
#include "Document.h"

TEST_CASE("Document Tokenization", "[IndexBuilder]") {
    IndexBuilder indexBuilder;
    std::string content = "The quick brown fox jumps over the lazy dog";
    auto tokens = indexBuilder.tokenize(content);
    
    REQUIRE(tokens.size() == 9);
    REQUIRE(tokens[0] == "The");
    REQUIRE(tokens[1] == "quick");
    // Continue for all tokens
}

TEST_CASE("Stopword Removal", "[IndexBuilder]") {
    IndexBuilder indexBuilder;
    std::vector<std::string> tokens = {"the", "quick", "brown", "fox"};
    indexBuilder.removeStopwords(tokens);

    REQUIRE(tokens.size() == 3);
    REQUIRE(tokens[0] == "quick");
    REQUIRE(tokens[1] == "brown");
    REQUIRE(tokens[2] == "fox");
}

TEST_CASE("Stemming", "[IndexBuilder]") {
    IndexBuilder indexBuilder;
    std::vector<std::string> tokens = {"running", "jumps", "happily"};
    indexBuilder.stem(tokens);

    REQUIRE(tokens[0] == "run");
    REQUIRE(tokens[1] == "jump");
    REQUIRE(tokens[2] == "happi"); // Depending on the stemming algorithm used
}

TEST_CASE("Indexing of Terms", "[IndexBuilder]") {
    InvertedIndex invertedIndex;
    IndexBuilder indexBuilder;
    Document doc;
    doc.parse("path/to/test/document.json"); // Assuming this file exists and is properly formatted

    indexBuilder.indexDocument(invertedIndex, doc);

    // Assuming "fox" is a term in the document
    auto searchResult = invertedIndex.search("fox");
    REQUIRE(searchResult != nullptr);
    REQUIRE(!searchResult->empty());
}

TEST_CASE("Indexing of Organizations and Persons", "[IndexBuilder]") {
    InvertedIndex invertedIndex;
    IndexBuilder indexBuilder;
    Document doc;
    doc.parse("path/to/test/document_with_orgs_and_persons.json");

    indexBuilder.indexDocument(invertedIndex, doc);

    // Assuming "Google" is an organization in the document
    auto orgSearchResult = invertedIndex.searchOrganization("Google");
    REQUIRE(orgSearchResult != nullptr);
    REQUIRE(!orgSearchResult->empty());

    // Assuming "John Doe" is a person in the document
    auto personSearchResult = invertedIndex.searchPerson("John Doe");
    REQUIRE(personSearchResult != nullptr);
    REQUIRE(!personSearchResult->empty());
}

TEST_CASE("Handling of Edge Cases", "[IndexBuilder]") {
    InvertedIndex invertedIndex;
    IndexBuilder indexBuilder;
    Document doc;
    doc.parse("path/to/test/empty_document.json"); // An empty or malformed document

    indexBuilder.indexDocument(invertedIndex, doc);

    REQUIRE(invertedIndex.isEmpty());
}

TEST_CASE("Integration with Document and InvertedIndex", "[IndexBuilder]") {
    InvertedIndex invertedIndex;
    IndexBuilder indexBuilder;
    Document doc;
    doc.parse("path/to/test/document.json");

    indexBuilder.indexDocument(invertedIndex, doc);

    // Verify that the inverted index has been updated with terms from the document
    auto searchResult = invertedIndex.search("some_term_in_document");
    REQUIRE(searchResult != nullptr);
    REQUIRE(!searchResult->empty());
}

// Additional tests can be added as needed
