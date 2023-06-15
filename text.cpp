#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "text.h"

void Text::print()
{
    for (const auto& word : mWords) 
    {
        std::cout << word.getData() << std::endl;
    }
}

void Text::addWord(const std::string& word, const std::string& fileName)
{
    std::string clnWord = cleanWord(word);
    Word tmpWord(clnWord, fileName);
    auto res = mWords.insert(tmpWord);
    if (!res.second)
    {
        Word& exWord = const_cast<Word&>(*res.first);
        exWord.addFileName(fileName);
    }
}

std::string Text::toLow(const std::string& word) 
{
    std::string tmp = word;
    for (char& ch : tmp) 
    {
        if (ch >= 'A' && ch <= 'Z') 
        {
            ch = ch + 32;
        }
    }
    return tmp;
}

bool Text::checkDir(const std::string& word, const std::string& file)
{
    std::ifstream dirFile(file);
    if (!dirFile.is_open()) 
    {
        std::cerr << "Failed to open the dictionary file." << std::endl;
        return false;
    }
    std::string dWord;
    while (dirFile >> dWord) 
    {
        if (dWord == word) 
        {
            dirFile.close();
            return true;
        }
    }
    dirFile.close();
    return false;
}

std::string Text::toUpp(const std::string& word) 
{
    std::string tmp = word;
    for (char& ch : tmp) 
    {
        if (ch >= 'a' && ch <= 'z') 
        {
            ch = ch - 32;
        }
    }
    return tmp;
}


std::string Text::cleanWord(const std::string& word)
{
    std::string clnWord;
    for (char ch : word) 
    {
       if (std::isalpha(ch)) 
        {
            clnWord += ch;
        }
    }
    return toLow(clnWord);
}

void Text::searchWord(const std::string& word)
{
    std::ifstream inFile("db.txt");
    if (!inFile)
    {
        std::cerr << "Failed to open the db.txt file." << std::endl;
        return;
    }
    std::string line;
    std::vector<std::string> fileNames;

    while (std::getline(inFile, line))
    {
        std::string dbWord = line.substr(0, line.find(":"));
        if (dbWord == word) {
            std::cout << "Files that contain the word '" << word << "':" << std::endl;
            std::string fileNames = line.substr(line.find(":") + 1);
            std::replace(fileNames.begin(), fileNames.end(), ',', ' ');
            std::cout << fileNames << std::endl;
            return;
        }
    }
    std::cout << "The word '" << word << "' was not found in the database." << std::endl;
}
