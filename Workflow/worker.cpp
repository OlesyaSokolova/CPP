#include <algorithm>
#include "worker.h"
#include "WkfExceptions.h"
#include "Functions.h"
using namespace consts;
namespace workflow
{
	Worker::Worker(const std::optional <string_list>& parameters)
		: parameters_(parameters) {}

	Worker::~Worker() {}

	Replace::Replace(const std::optional <string_list>& parameters)
		: Worker(parameters) {}

	Writefile::Writefile(const std::optional <string_list>& parameters)
		: Worker(parameters) {}

	Readfile::Readfile(const std::optional <string_list>& parameters)
		: Worker(parameters) {}

	Grep::Grep(const std::optional <string_list>& parameters)
		: Worker(parameters) {}

	Dump::Dump(const std::optional <string_list>& parameters)
		: Worker(parameters) {}

	Sort::Sort(const std::optional <string_list>& parameters)
		: Worker(parameters) {}

	void Readfile::validate(const std::optional <string_list>& data) const
	{
		std::string exString = EMPTY_STRING;
		std::string workerName = WORKER_READ;
		if (data.has_value())
		{
			exString = WRONG_INPUT;
			throw WkfException(exString, workerName);
		}
		std::string originalFile = parameters_.value()[1];
		validateFile(originalFile);	
	} 

	void Writefile::validate(const std::optional <string_list>& data) const
	{
		std::string exString = EMPTY_STRING;
		std::string workerName = WORKER_WRITE;
		if (!data.has_value())
		{
			exString = WRONG_INPUT;
			throw WkfException(exString, workerName);
		}
		std::string resultFile = parameters_.value()[1];
		validateFile(resultFile);
	}
	
	void Grep::validate(const std::optional <string_list>& data) const
	{
		std::string exString = EMPTY_STRING;
		std::string workerName = WORKER_GREP;
		if (!data.has_value())
		{
			exString = WRONG_INPUT;
			throw WkfException(exString, workerName);
		}
		std::string pattern = parameters_.value()[1];
		if (pattern == consts::EMPTY_STRING)
		{
			exString = ARGUMENTS_DEFICIENCY;
			throw WkfException(exString, workerName);
		}
	}

	void Replace::validate(const std::optional <string_list>& data) const
	{
		std::string exString = EMPTY_STRING;
		std::string workerName = WORKER_REPLACE;
		if (!data.has_value())
		{
			exString = WRONG_INPUT;
			throw WkfException(exString, workerName);
		}
		std::string wordBefore = parameters_.value()[1];
		if (wordBefore == consts::EMPTY_STRING)
		{
			exString = ARGUMENTS_DEFICIENCY;
			throw WkfException(exString, workerName);
		}
	}

	void Sort::validate(const std::optional <string_list>& data) const
	{
		std::string exString = EMPTY_STRING;
		std::string workerName = WORKER_SORT;
		if (!data.has_value())
		{
			exString = WRONG_INPUT;
			throw WkfException(exString, workerName);
		}
	}

	void Dump::validate(const std::optional <string_list>& data) const
	{
		std::string exString = EMPTY_STRING;
		std::string workerName = WORKER_DUMP;
		if (!data.has_value())
		{
			exString = WRONG_INPUT;
			throw WkfException(exString, workerName);
		}
	}
	
	std::optional <string_list> Readfile::doSomeWork(const std::optional <string_list>& data) const
	{//input - none; output - txt
		std::string exString = EMPTY_STRING;
		std::optional <string_list> resultData;
		std::string line;

		std::ifstream in;
		std::string originalFile = parameters_.value()[1];

		in.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			in.open(originalFile);
		}
		catch (const std::ifstream::failure&)
		{
			exString = originalFile + FILE_CANNOT_BE_OPENED;
			throw std::ifstream::failure(exString);
		}
		while (!in.eof())
		{
			getline(in, line);
			if (!resultData.has_value())
			{
				resultData.emplace(string_list());
			}
			resultData.value().push_back(line);
		}
		return resultData;
	}

	std::optional <string_list> Writefile::doSomeWork(const std::optional <string_list>& data) const
	{//input - txt; output - none 
		std::string exString = EMPTY_STRING;
		std::string workerName = WORKER_WRITE;
		
		std::ofstream out;
		std::string resultFile = parameters_.value()[1];

		out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try
		{
			out.open(resultFile);
		}
		catch (const std::ofstream::failure&)
		{
			exString = resultFile + FILE_CANNOT_BE_OPENED;
			throw std::ofstream::failure(exString);
		}
		int sizeWithoutLastline = data.value().size() - 1;
		for (auto i = 0; i < sizeWithoutLastline; i++)
		{
			out << data.value()[i] << std::endl;
		}
		out << data.value()[sizeWithoutLastline];
		return std::nullopt;
	}

	std::optional <string_list> Grep::doSomeWork(const std::optional <string_list>& data) const
	{//input - txt; output - txt
		std::string exString = EMPTY_STRING;
		std::string workerName = WORKER_GREP;	
		std::optional <string_list> resultData;
		std::string line;
		std::string pattern = parameters_.value()[1];
	
		for (auto i = 0; i < data.value().size(); i++)
		{
			line = data.value()[i];
			if (line.find(pattern, 0) != std::string::npos)
			{
				if (!resultData.has_value())
				{
					resultData.emplace(string_list());
				}
				resultData.value().push_back(line);
			}
		}
		return resultData;
	}

	std::optional <string_list> Replace::doSomeWork(const std::optional <string_list>& data) const
	{//input - txt; output - txt
		std::string exString = EMPTY_STRING;
		std::string workerName = WORKER_REPLACE;
		std::optional <string_list> resultData;
		std::string line;
		std::string wordBefore = parameters_.value()[1];
		std::string wordAfter = parameters_.value()[2];
		int length = wordBefore.length();
		int pos = 0;
		int startPos = 0;

		for (auto i = 0; i < data.value().size(); i++)
		{
			line = data.value()[i];
			startPos = 0;
			pos = line.find(wordBefore, startPos);
			while (pos < line.length())
			{
				pos = line.find(wordBefore, 0);
				if (pos != std::string::npos)
				{
					line.replace(pos, length, wordAfter);
				}
			}
			if (!resultData.has_value())
			{
				resultData.emplace(string_list());
			}
			resultData.value().push_back(line);
		}		
		return resultData;
	}

	std::optional <string_list> Sort::doSomeWork(const std::optional <string_list>& data) const
	{//input - txt; output - txt
		std::optional <string_list> resultData;
		resultData = data;
		std::sort(resultData.value().begin(), resultData.value().end());
		return resultData;
	}

	std::optional <string_list> Dump::doSomeWork(const std::optional <string_list>& data) const
	{//input - txt; output - txt
		std::string exString;
		std::string workerName = WORKER_DUMP;
		std::optional <string_list> resultData;

		std::ofstream out;
		std::string resultFile = parameters_.value()[1];
		
		out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
		try
		{
			out.open(resultFile);
		}
		catch (const std::ofstream::failure&)
		{
			exString = resultFile + FILE_CANNOT_BE_OPENED;
			throw std::ofstream::failure(exString);
		}

		int sizeWithoutLastline = data.value().size() - 1;
		for (auto i = 0; i < sizeWithoutLastline; i++)
		{
			out << data.value()[i] << std::endl;
		}
		out << data.value()[sizeWithoutLastline];

		resultData = data;
		return resultData;
	}

	Worker* workerFactoryBase(const string_list& parameters)
	{
		Worker * result = nullptr;
		std::string commandName = parameters[0];

		if (commandName == WORKER_WRITE)
		{
			result = new Writefile(parameters);
		}
		if (commandName == WORKER_READ)
		{
			result = new Readfile(parameters);
		}
		return result;
	}

	Worker* workerFactory(const string_list& parameters)
	{
		Worker * result = workerFactoryBase(parameters);

		if (result != nullptr)
		{
			return result;
		}

		std::string commandName = parameters[0];

		if (commandName == WORKER_REPLACE)
		{
			result = new Replace(parameters);
		}
		if (commandName == WORKER_GREP)
		{
			result = new Grep(parameters);
		}
		if (commandName == WORKER_SORT)
		{
			result = new Sort(parameters);
		}
		if (commandName == WORKER_DUMP)
		{
			result = new Dump(parameters);
		}
		return result;
	}
}