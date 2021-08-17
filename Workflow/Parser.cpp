#include <fstream>
#include <iostream>
#include <unordered_map>
#include "Parser.h"
#include "Functions.h"
using namespace consts;
namespace workflow {
	
	std::vector<std::string> ParsingString(std::string commandDescription, std::string delim)
	{
		std::vector<std::string> result;
		int pos = commandDescription.find(delim);
		while (pos != std::string::npos)
		{
			result.push_back(commandDescription.substr(0, pos));
			commandDescription.erase(0, pos + delim.length());
			pos = commandDescription.find(delim);
		}
		result.push_back(commandDescription.substr(0, pos));
		return result;
	}
	void Parser::parsingWorkflowFile(const std::string& filename)
	{
		validateFile(filename);

		std::vector<std::string> sequence;
		std::string exString = EMPTY_STRING;
		
		std::ifstream wkfFile;
		wkfFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			wkfFile.open(filename);
		}
		catch (const std::ifstream::failure&)
		{
			exString = filename + FILE_CANNOT_BE_OPENED;
			throw std::ifstream::failure(exString);
		}
		std::string line;
		std::string id;
		std::string commandDescription;
		std::map <std::string, std::vector<std::string>> commands_map;

		getline(wkfFile, line);
		if (line == DESCRIPTION_BEGIN)
		{
			getline(wkfFile, line);
			while (line != DESCRIPTION_END)
			{
				id = line.substr(0, line.find(DELIMITER_1));
				commandDescription = line.substr(DELIMITER_1.length() + id.length(), line.find(LINE_DELIMITER));
				commands_map[id] = ParsingString(commandDescription, DELIMITER_2);
				getline(wkfFile, line);
			}
		}
		getline(wkfFile, line);
		string_list command;
		sequence = ParsingString(line, DELIMITER_3);
		for (auto i = 0; i < sequence.size(); i++)
		{	
			command = commands_map[sequence[i]];
			if (command.size() == 0)
			{
				exString = COMMAND_DESCRIPTION_ERROR + sequence[i];
				throw std::exception(exString.c_str());
			}
			commands_.push_back(command);
		}
	}
	void Parser::parsing(const std::string& filename, const std::string& inputFile, const std::string& outputFile)
	{
		std::vector<std::string> sequence;
		std::string exString = EMPTY_STRING;

		parsingWorkflowFile(filename);

		if (inputFile != EMPTY_STRING && outputFile != EMPTY_STRING)
		{
			std::vector <std::string> read_file = { WORKER_READ, inputFile };
			std::vector <std::string> write_file = { WORKER_WRITE, outputFile };
			
			for (int i = 0; i < commands_.size(); i++)
			{
				if (commands_[i][0] == WORKER_READ)
				{
					exString = INPUT_FILE_CONFLICT;
					throw std::exception(exString.c_str());
				}
				else if (commands_[i][0] == WORKER_WRITE)
				{
					exString = OUTPUT_FILE_CONFLICT;
					throw std::exception(exString.c_str());
				}
			}			
			commands_.insert(commands_.begin(), read_file);
			for (int i = 0; i < commands_.size(); i++)
			{
				if (commands_[i][0] == WORKER_DUMP)
				{
					commands_[i].push_back(outputFile);
				}
			}
			commands_.insert(commands_.end(), write_file);
		}
	}
	std::vector <string_list> Parser::getCommands() const
	{
		return commands_;
	}
}
