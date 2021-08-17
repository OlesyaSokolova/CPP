#include "Functions.h"
#include "Consts.h"
using namespace consts;
bool isFileFormatCorrect(std::string filename)
{
	int nameLength = filename.length();

	char check1 = filename[nameLength - 1];
	char check2 = filename[nameLength - 2];
	char check3 = filename[nameLength - 3];

	return (check1 == 't' && check2 == 'x' && check3 == 't');
}
void validateFile(std::string filename)
{
	std::string exString = EMPTY_STRING;
	if (filename == EMPTY_STRING)
	{
		exString = filename + FILE_DOES_NOT_EXIST;
		throw std::exception(exString.c_str());
	}
	else if(isFileFormatCorrect(filename) == false)
	{
		exString =  filename + WRONG_FILE_FORMAT;
		throw std::exception(exString.c_str());
	}
}
