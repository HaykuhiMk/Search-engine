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
#include "pdfReader.h"


int main()
{
    PDFReader pdf;
    pdf.readFile(1.pdf);
    // TextReader text;
    // text.readFile("1.txt");
    // text.readFile("2.txt");
    // text.searchWord("solve");
    // text.print();

    return 0;
}
