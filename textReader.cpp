#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "text.h"
#include "textReader.h"

void TextReader::readFile(const std::string& fileName)
{
    std::string check(fileName.end() - 4, fileName.end());
    if (check != ".txt") 
    {
        throw std::invalid_argument("The file must be in .txt format");
    }
    int fI = std::stoi(fileName.substr(0, fileName.find('.')));

    std::ifstream inFile(fileName);
    if (!inFile) 
    {
        std::cerr << "Failed to open the input file." << std::endl;
        return;
    }
    std::string word;
    while (inFile >> word) 
    {
        std::string clnWord = cleanWord(word);
        if (clnWord.empty())
        {
            continue;
        }
        if (checkDir(clnWord, "words_alpha.txt"))
        {
            Word tmpWord(clnWord, fileName);
            auto res = mWords.insert(tmpWord);
            if (!res.second)
            {
                Word& exWord = const_cast<Word&>(*res.first);
                exWord.addFileName(fileName);
            }
        }
    }

    inFile.close();
    std::ofstream outFile("db.txt", std::ios::app);
    if (!outFile) 
    {
        std::cerr << "Failed to open the output file." << std::endl;
        return;
    }
    for (const Word& word : mWords) 
    {
        const std::vector<std::string>& fileNamesStr = word.getFileNames();
        outFile << word.getData() << ": ";
        for (const std::string& fileNameStr : fileNamesStr)
        {
            int fileName = std::stoi(fileNameStr);
            outFile << fileName << " ";
        }
        outFile << std::endl;
    }
    outFile.close();
    std::cout << "Words saved to db.txt." << std::endl;
}