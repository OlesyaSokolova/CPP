#pragma once
#include "functions.h"
#include "consts.h"
#include <list>
using namespace std;

namespace functions{
void PrintingResult(ofstream &output, classes::WordsArray *chart)
{
	int i;
	int sum = 0;

	for (i = 0; i < chart->GetCounter(); i++) 
	{
		sum += chart->GetWordFreq(i);
	}

	for (i = 0; i < chart->GetCounter(); i++)
	{
		output << chart->GetWord(i) << consts::COMMA << chart->GetWordFreq(i)
			<< consts::COMMA << (double)(chart->GetWordFreq(i) * consts::HUNDRED_PERCENT / sum) << consts::PERCENT << endl;
	}
}

void ReadingFile(ifstream &input, classes::WordsArray *chart)
{
	string newString;
	list<string> lst;
	bool endOfFile = input.eof();
	while(!endOfFile)
	{
		    getline(input, newString);
			lst.push_back(newString);
			endOfFile = input.eof();
	}

	for (auto j = lst.begin(); j != lst.end(); j++)
	{
		classes::LongString String(*j);
		String.Fragmentation();

		for (auto i = 0; i < String.GetCounter(); i++)
		{
			chart->AddWord(String.GetWord(i));
		}
	}
}
bool isDigit(unsigned char c)
{
	return (c >= '0' && c <= '9');
}
bool isAlpha(unsigned char c)
{
	bool check1 = (c >= 'A'&& c <= 'Z');
	bool check2 = (c >= 'a'&& c <= 'z');
	bool check3 = (c >= 192 && c <= 255);//192 - 'A', 255 - 'ÿ'
	bool check4 = (c == 168 || c == 184);//168 - '¨', 184 - '¸'
	return (check1 || check2 || check3 || check4);
}
}