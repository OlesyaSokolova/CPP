#pragma once
#include <map>
#include <vector>
#include <string>
namespace consts {

	using string_list = std::vector<std::string>;

	const std::string EMPTY_STRING = "";
	const std::string DELIMITER_1 = " = ";
	const std::string DELIMITER_2 = " ";
	const std::string DELIMITER_3 = " -> ";
	const std::string LINE_DELIMITER = "\n";

	const std::string INPUT_KEY = "-i";
	const std::string OUTPUT_KEY = "-o";

	const std::string DESCRIPTION_BEGIN = "desc";
	const std::string DESCRIPTION_END = "csed";

	const std::string WORKER_READ = "readfile";
	const std::string WORKER_WRITE = "writefile";
	const std::string WORKER_REPLACE = "replace";
	const std::string WORKER_SORT = "sort";
	const std::string WORKER_GREP = "grep";
	const std::string WORKER_DUMP = "dump";

	const std::string WRONG_FILE_FORMAT = ": this file has wrong file format. It should be \"txt\"!";
	const std::string FILE_DOES_NOT_EXIST = ": this file is not found.";
	const std::string FILE_CANNOT_BE_OPENED = ": this file cannot be opened";
	const std::string COMMAND_DESCRIPTION_ERROR = "Description of some command is not found. Command id: ";
	const std::string INPUT_FILE_CONFLICT = "Conflict: input file is already specified in the readfile-command description.";
	const std::string OUTPUT_FILE_CONFLICT = "Conflict: output file is already specified in the writefile-command description.";
	const std::string WRONG_INPUT = "Wrong input.";
	const std::string ARGUMENTS_DEFICIENCY = "Not enough arguments to do work.";
	const std::string ARGUMENTS_EXCESS = "Too many files. Only necessary number of files will be used.";
	const std::string UNKNOWN_ERROR = "Something went wrong!";

	const int FIRST_ARGUMENT_NUMBER = 1;

	const int MIN_NUMBER_OF_ARGUMENTS = 2;
	const int MAX_NUMBER_OF_ARGUMENTS = 6;
}	