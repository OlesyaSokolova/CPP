#pragma once
#include <vector>
#include  <string>

using namespace std;
namespace classes{
class Word
{
public:
	Word(const string &str);
	Word();
	string GetWord() const;
	void IncreaseFreq();
	int GetFreq() const;
private:
	string word;
	int freq;
};

class WordsArray
{
public:
    void AddWord(string NewWord);
	string GetWord(int k) const;
	int GetWordFreq(int k) const;
	int GetCounter() const;
	void SortingArray();
private:
	std::vector <Word> words;
};

class LongString
{
public:
	LongString(const string &str);
	void Fragmentation();
	int GetCounter() const;
	string  GetWord(int k) const;
private:
	std::vector <string> severalWords;
	string receivedString;
};
}