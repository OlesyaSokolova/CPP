#pragma once
#include "classes.h"
#include <fstream>
using namespace std;
namespace functions{
void ReadingFile(ifstream &input, classes::WordsArray *chart);
void PrintingResult(ofstream &output, classes::WordsArray *chart);
bool isAlpha(unsigned char c);
bool isDigit(unsigned char c);
}