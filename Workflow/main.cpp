#include <fstream>
#include <iostream>
#include <string>
#include "worker.h"
#include "Executor.h"
#include "Parser.h"
#include "WkfExceptions.h"
#include "Functions.h"
#include <exception>

using namespace consts;
using namespace workflow;

void validateInOutParameters(int argc)
{
	if (argc < MIN_NUMBER_OF_ARGUMENTS)
	{
		throw std::exception(ARGUMENTS_DEFICIENCY.c_str());
	}
	if (argc > MAX_NUMBER_OF_ARGUMENTS)
	{
		std::cout << ARGUMENTS_EXCESS << std::endl;
	}
}

std::pair<std::string, std::string> extractInOutFilenames(int argc, char ** argv)
{
	std::string inputFile;
	std::string outputFile;
	int NUMBER_OF_ARGUMENTS = argc;
	for (int i = FIRST_ARGUMENT_NUMBER; i < NUMBER_OF_ARGUMENTS; i++)
	{
		if (argv[i] == INPUT_KEY)
		{
			inputFile = argv[i + DELIMITER_2.length()];
		}
		if (argv[i] == OUTPUT_KEY)
		{
			outputFile = argv[i + DELIMITER_2.length()];
		}
	}
	return std::pair(inputFile, outputFile);
}

int main(int argc, char ** argv)
{
	try
	{
		validateInOutParameters(argc);

		std::ifstream workflow;
		std::string wkfFile = argv[1];
		
		std::string inputFileName = EMPTY_STRING;
		std::string outputFileName = EMPTY_STRING;

		if (argc > MIN_NUMBER_OF_ARGUMENTS)
		{
			auto inOutFileNames = extractInOutFilenames(argc, argv);
			inputFileName = inOutFileNames.first;
			outputFileName = inOutFileNames.second;
		}

		Parser p;
		p.parsing(wkfFile, inputFileName, outputFileName);

		Executor ex(p.getCommands(), workerFactory);
		ex.run();
	}
	catch (const std::iostream::failure& ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << ex.code() << std::endl;
		getchar();
		return -1;
	}
	catch (const WkfException& ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << ex.mistakeStage() << std::endl;
		getchar();
		return -1;
	}
	catch (const std::exception &ex)
	{
		std::cout << ex.what() << std::endl;
		getchar();
		return -1;
	}
	catch (...)
	{
		std::cout << UNKNOWN_ERROR << std::endl;
		getchar();
		return -1;
	}

	return 0;
}