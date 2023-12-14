#include "document.h"
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"

bool Document::parse(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        return false;  // File opening failed
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    rapidjson::Document d;
    d.Parse(buffer.str().c_str());

    if (d.HasParseError()) {
        return false;  // JSON parsing failed
    }

    // Extracting fields from JSON
    if (d.HasMember("uuid") && d["uuid"].IsString()) {
        uuid_ = d["uuid"].GetString();
    }

    if (d.HasMember("title") && d["title"].IsString()) {
        title_ = d["title"].GetString();
    }

    if (d.HasMember("published") && d["published"].IsString()) {
        date_ = d["published"].GetString();
    }

    if (d.HasMember("url") && d["url"].IsString()) {
        url_ = d["url"].GetString();
    }

    if (d.HasMember("text") && d["text"].IsString()) {
        content_ = d["text"].GetString();
    }

    // Parsing organizations
    if (d.HasMember("organizations") && d["organizations"].IsArray()) {
        for (const auto& org : d["organizations"].GetArray()) {
            if (org.HasMember("name") && org["name"].IsString() &&
                org.HasMember("sentiment") && org["sentiment"].IsString()) {
                Organization organization{org["name"].GetString(), org["sentiment"].GetString()};
                organizations_.push_back(organization);
            }
        }
    }

    // Parsing persons
    if (d.HasMember("persons") && d["persons"].IsArray()) {
        for (const auto& per : d["persons"].GetArray()) {
            if (per.HasMember("name") && per["name"].IsString() &&
                per.HasMember("sentiment") && per["sentiment"].IsString()) {
                Person person{per["name"].GetString(), per["sentiment"].GetString()};
                persons_.push_back(person);
            }
        }
    }

    return true;
}
