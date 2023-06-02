#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "invertedIndex.h"

void addToInvertedIndex(std::unordered_map<std::string, std::vector<std::string> >& invertedIndex, const std::string& word, const std::string& fileName)
{
    std::string normalizedWord = word;
    auto it = invertedIndex.find(normalizedWord);
    if (it != invertedIndex.end())
    {
        it->second.push_back(fileName);
    }
    else
    {
        invertedIndex.insert(std::make_pair(normalizedWord, std::vector<std::string>{fileName}));
    }
}

void toInvInd()
{
    std::ifstream inFile("db.txt");
    if (!inFile)
    {
        std::cerr << "Failed to open the input file." << std::endl;
        return;
    }

    std::unordered_map<std::string, std::vector<std::string> > invertedIndex;

    std::string line;
    while (std::getline(inFile, line))
    {
        std::istringstream iss(line);
        std::string word;
        std::string fileName;
        if (iss >> word >> fileName)
        {
            addToInvertedIndex(invertedIndex, word, fileName);
        }
    }

    inFile.close();

    for (const auto& entry : invertedIndex)
    {
        std::cout << entry.first << ": ";
        for (const auto& fileName : entry.second)
        {
            std::cout << fileName << " ";
        }
        std::cout << std::endl;
    }
}

int main()
{
    toInvInd();
    return 0;
}
