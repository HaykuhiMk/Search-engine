// #ifndef INVERTED_INDEX_H
// #define INVERTED_INDEX_H
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

struct DocumentList 
{
    std::vector<std::string> documents;
};

class InvertedIndex
{
public:
    void addWord(const std::string& word, const std::string& document)
    {
        index[word].push_back(document);
    }
private:
    std::unordered_map<std::string, std::vector<std::string>> index;
};

// #endif  //INVERTED_INDEX_H