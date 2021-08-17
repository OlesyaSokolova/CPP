#include "classes.h"
#include "functions.h"
#include "consts.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian"); 

	ifstream input;
	ofstream output;
	

	if (argc < consts::NECESSARY_NUMBER_OF_FILES)
	{
		cout << "Not enough files." << endl;
		getchar();
		return -1;
	}

	if (argc > consts::NECESSARY_NUMBER_OF_FILES)
	{
		cout << "Too many files. Only two first will be used." << endl;
		getchar();
	}

	input.open(argv[consts::INPUT_FILE_INDEX]);
	if (!input.is_open())
	{
		cout << "Error: input-file can't be opened." <<endl;
		getchar();
		return -2;
	}

	output.open(argv[consts::OUTPUT_FILE_INDEX]);
	if (!output.is_open())
	{
		cout << "Error: output-file can't be opened." << endl;
		getchar();
		return -3;
	}
	
	classes::WordsArray chart;
	functions::ReadingFile(input, &chart);
	chart.SortingArray();
	functions::PrintingResult(output, &chart);

	return 0;
}
