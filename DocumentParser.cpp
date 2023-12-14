#include "DocumentParser.h"
#include "document.h"
#include <fstream>
#include <filesystem>
#include <sstream>
#include <string>
#include <set>
#include <cctype>
#include <algorithm>

// RapidJSON headers for parsing.
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/document.h"

using namespace std;
using namespace rapidjson;

void DocumentParser::readJsonFile(const string &path, AvlTree<string, map<string, int>> &wordTree, AvlTree<string, set<string>> &peopleMap, AvlTree<string, set<string>> &orgsMap, AvlTree<string, string> &stopWordTree, AvlTree<string, document> &docTree) {
    ifstream input(path);
    if (!input.is_open()) {
        cerr << "Cannot open file: " << path << endl;
        return;
    }

    IStreamWrapper isw(input);
    Document d;
    d.ParseStream(isw);

    string val = d["uuid"].GetString();
    string words = d["text"].GetString();
    string author = d["author"].GetString();
    string title = d["title"].GetString();
    string published = d["published"].GetString();
    document doc(title, val, published, author, words);
    docTree[val] = doc;

    processEntities(d, "persons", peopleMap, val);
    processEntities(d, "organizations", orgsMap, val);

    vector<string> content = tokenize(words);
    indexWords(content, wordTree, val);

    input.close();
}

void DocumentParser::processEntities(const Document& d, const string& entityKey, AvlTree<string, set<string>>& entityMap, const string& documentUuid) {
    if (d.HasMember(entityKey.c_str()) && d[entityKey.c_str()].IsArray()) {
        for (const auto& entity : d[entityKey.c_str()].GetArray()) {
            string name = entity["name"].GetString();
            transform(name.begin(), name.end(), name.begin(), ::tolower);
            replace(name.begin(), name.end(), ' ', '-');
            entityMap[name].insert(documentUuid);
        }
    }
}

vector<string> DocumentParser::tokenize(const string &text) {
    vector<string> words;
    stringstream ss(text);
    string token;
    while (ss >> token) {
        transform(token.begin(), token.end(), token.begin(), ::tolower);
        if (isalnum(token.back())) {
            words.push_back(token);
        }
    }
    return words;
}

void DocumentParser::indexWords(const vector<string>& words, AvlTree<string, map<string, int>>& wordTree, const string& documentUuid) {
    for (const auto& word : words) {
        wordTree[word].emplace(documentUuid, 0);
        wordTree[word][documentUuid]++;
    }
}

void DocumentParser::fileSystem(const string &directoryPath, AvlTree<string, map<string, int>> &wordTree, AvlTree<string, set<string>> &peopleMap, AvlTree<string, set<string>> &orgsMap, AvlTree<string, string> &stopWordTree, AvlTree<string, document> &docTree) {
    for (const auto &entry : filesystem::recursive_directory_iterator(directoryPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            readJsonFile(entry.path(), wordTree, peopleMap, orgsMap, stopWordTree, docTree);
        }
    }
}

AvlTree<string, string> &DocumentParser::readStopWords(AvlTree<string, string> &stopWordTree) {
    ifstream input("../stopwords.txt");
    if (!input) {
        throw runtime_error("Could not open stopwords file.");
    }
    string word;
    while (getline(input, word)) {
        stopWordTree.insert(word);
    }
    return stopWordTree;
}
