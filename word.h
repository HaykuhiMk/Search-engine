#ifndef WORD_H
#define WORD_H
#include <string>
#include <vector>

class Word
{
public:
    Word(const std::string&, const std::string&);
    bool operator==(const Word&) const;
    const std::string& getData() const;
    void setData(const std::string& data);
    const std::vector<std::string>& getFileNames() const;
    void addFileName(const std::string& file);

private:
    std::string mData;
    std::vector<std::string> mFileNames;
};

struct HashWord
{
    std::size_t operator()(const Word&) const;
};

#endif  //WORD_H

