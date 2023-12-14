#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H

#include <string>
#include <vector>
#include <map>
#include "AVLTreeMap.h"
#include "Document.h"

class InvertedIndex {
private:
    AVLTreeMap<std::string, std::map<std::string, int>> termIndex; // Terms with document UUIDs and frequencies
    AVLTreeMap<std::string, std::vector<std::string>> organizationIndex; // Organizations with document UUIDs
    AVLTreeMap<std::string, std::vector<std::string>> personIndex; // Persons with document UUIDs

public:
    void addTerm(const std::string& term, const std::string& documentUuid);
    void addOrganization(const std::string& organization, const std::string& documentUuid);
    void addPerson(const std::string& person, const std::string& documentUuid);

    // Methods for searching and retrieving data
    const std::map<std::string, int>* searchTerm(const std::string& term) const;
    const std::vector<std::string>* searchOrganization(const std::string& organization) const;
    const std::vector<std::string>* searchPerson(const std::string& person) const;
};

#endif // INVERTED_INDEX_H