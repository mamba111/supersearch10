#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <string>
#include <vector>

// Define the Organization struct
struct Organization {
    std::string name;
    std::string sentiment;
};

// Define the Person struct
struct Person {
    std::string name;
    std::string sentiment;
};

// Define the Document class
class Document {
private:
    std::string uuid_;
    std::string title_;
    std::string date_;
    std::string url_;
    std::string content_;
    int relevanceScore_;  // Added relevance score
    std::vector<Organization> organizations_;
    std::vector<Person> persons_;

public:
    Document() : relevanceScore_(0) {} // Initialize relevanceScore_ to 0

    // Method to parse a file and populate the Document object
    bool parse(const std::string& filepath);

    // Getter and setter methods for each field
    const std::string& getUuid() const { return uuid_; }
    const std::string& getTitle() const { return title_; }
    const std::string& getDate() const { return date_; }
    const std::string& getUrl() const { return url_; }
    const std::string& getContent() const { return content_; }
    int getRelevanceScore() const { return relevanceScore_; }
    void setRelevanceScore(int score) { relevanceScore_ = score; }
    const std::vector<Organization>& getOrganizations() const { return organizations_; }
    const std::vector<Person>& getPersons() const { return persons_; }
};

#endif // DOCUMENT_H
