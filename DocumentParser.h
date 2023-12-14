#ifndef DOCUMENT_PARSER_H
#define DOCUMENT_PARSER_H

#include "Document.h"
#include "avl_tree_map.h"
#include <string>
#include <vector>
#include <set>

class DocumentParser {
public:
    void parseFile(const std::string& filepath,
                   AVLTreeMap<std::string, std::map<std::string, int>>& terms,
                   AVLTreeMap<std::string, std::vector<std::string>>& organizations,
                   AVLTreeMap<std::string, std::vector<std::string>>& persons);

private:
    std::vector<std::string> tokenize(const std::string& text);
    void removeStopWords(std::vector<std::string>& tokens, const std::set<std::string>& stopWords);
    void stemWords(std::vector<std::string>& tokens);
    void indexDocument(const Document& doc,
                       AVLTreeMap<std::string, std::map<std::string, int>>& terms,
                       AVLTreeMap<std::string, std::vector<std::string>>& organizations,
                       AVLTreeMap<std::string, std::vector<std::string>>& persons);
    std::set<std::string> loadStopWords(const std::string& filepath);
};

#endif // DOCUMENT_PARSER_H
