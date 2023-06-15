#ifndef TEXT_READER_H
#define TEXT_READER_H
#include "text.h"

class TextReader : public Text
{
public:
    virtual ~TextReader() = default;
    void readFile(const std::string&) override;
};

#endif  //TEXT_READER_H