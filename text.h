#ifndef TEXT_H
#define TEXT_H
#include <unordered_set>
#include "word.h"

class Text
{
public:
    void addWord(const std::string& word, const std::string& fileName);
    virtual ~Text() = default;
    virtual void readFile(const std::string&) = 0;
    std::string cleanWord(const std::string&);
    std::string toLow(const std::string& word); 
    std::string toUpp(const std::string& word); 
    bool checkDir(const std::string&, const std::string&);
    void searchWord(const std::string& word);
    void print();

protected:
    std::unordered_set<Word, HashWord> mWords;

};

#endif  //TEXT_H
