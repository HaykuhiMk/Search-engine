#ifndef PDF_READER_H
#define PDF_READER_H
#include "text.h"

class PDFReader : public Text
{
public:
    virtual ~PDFReader() = default;
    void readFile(const std::string&) override;
};

#endif  //PDF_READER_H