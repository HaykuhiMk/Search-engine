#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <aspell.h>
#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "text.h"
#include "textReader.h"

void PDFReader::readFile(const std::string& fileName)
{
    std::string check(fileName.end() - 4, fileName.end());
    if (check != ".pdf")
    {
        throw std::invalid_argument("The file must be in .pdf format");
    }
    std::ifstream fileStream(fileName, std::ios::binary);
    if (!fileStream)
    {
        std::cerr << "Failed to open the PDF file." << std::endl;
        return;
    } 
    std::stringstream pdfContent;
    pdfContent << fileStream.rdbuf();
    std::string content = pdfContent.str();
    poppler::document::load_from_data dataLoader(content);
    auto document = dataLoader.load();
    if (!document)
    {
        std::cerr << "Failed to analyze the PDF file." << std::endl;
        return;
    }
    for (int i = 0; i < document->pages(); ++i)
    {
        const auto page = document->create_page(i);
        if (!page)
        {
            continue;
        }
        std::string pageText = page->text().to_string();
        std::istringstream iss(pageText);
        std::string word;
        while (iss >> word)
        {
            std::string clnWord = cleanWord(word);
            if (!clnWord.empty() && checkDir(clnWord, "words_alpha.txt"))
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
    }
    fileStream.close();
    std::ofstream outFile("output.txt");
    if (!outFile)
    {
        std::cerr << "Failed to open the output file." << std::endl;
        return;
    }
    for (const auto& word : mWords)
    {
        outFile << word << std::endl;
    }
    outFile.close();
    delete_aspell_speller("words_alpha.txt");
    delete_aspell_config(spellChecker);
    std::cout << "Words saved to output.txt" << std::endl;
}
