#include "inverted_index.h"

void InvertedIndex::addTerm(const std::string& term, const std::string& documentUuid) {
    termIndex[term][documentUuid]++;
}

void InvertedIndex::addOrganization(const std::string& organization, const std::string& documentUuid) {
    organizationIndex[organization].push_back(documentUuid);
}

void InvertedIndex::addPerson(const std::string& person, const std::string& documentUuid) {
    personIndex[person].push_back(documentUuid);
}

const std::map<std::string, int>* InvertedIndex::searchTerm(const std::string& term) const {
    return termIndex.search(term);
}

const std::vector<std::string>* InvertedIndex::searchOrganization(const std::string& organization) const {
    return organizationIndex.search(organization);
}

const std::vector<std::string>* InvertedIndex::searchPerson(const std::string& person) const {
    return personIndex.search(person);
}