#pragma once
#include "classes.h"
#include "consts.h"
#include <algorithm>
#include "functions.h"
using namespace std;
namespace classes{

Word::Word(const string &str)
	: word(str), freq(1) {}
Word::Word()
{
	this->freq = 0;
	this->word = consts::EMPTY_STRING;
}
string Word::GetWord() const
{
	return this->word;
}
void Word::IncreaseFreq()
{
	this->freq++;
}

int Word::GetFreq() const
{
	return this->freq;
}

void WordsArray::AddWord(string newWord)
{
	int i;
	for (i = 0; i < words.size(); i++)
	{
		if (newWord == this->words[i].GetWord())
		{
			this->words[i].IncreaseFreq();
			return;
		}
	}
	Word newOne(newWord);
	words.push_back(newOne); 
	return;
}
string  WordsArray::GetWord(int k) const
{
	return words[k].GetWord();
}
int WordsArray::GetWordFreq(int k) const
{
	return words[k].GetFreq();
}
int WordsArray::GetCounter() const
{
	return words.size();
}

void WordsArray::SortingArray()
{
	std::sort(words.begin(), words.end(), [](const Word& left, const Word& right)
	{
		return (right.GetFreq() < left.GetFreq());
	});
}

LongString::LongString(const string &str)
	: receivedString(str) {}
void LongString::Fragmentation()
{
	string currentWord = consts::EMPTY_STRING;
	int i;
	unsigned char c;
	for (i = 0; i < size(this->receivedString)+1; i++)
	{
		c = (unsigned char)receivedString[i];
		if (functions::isAlpha(c)|| functions::isDigit(c))
		{
			currentWord += c;
		}
		else
		{
			if (currentWord != consts::EMPTY_STRING)
			{
				this->severalWords.push_back(currentWord);
				currentWord.clear();
			}			
		}
	}
}
int LongString::GetCounter() const
{
	return severalWords.size();
}

string LongString::GetWord(int k) const
{
	return severalWords[k];
}
}