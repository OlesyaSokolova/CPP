#pragma once
#include "Consts.h"
using namespace consts;
namespace workflow {
	class Parser {
	public:
		Parser() = default;
		void parsing(const std::string& filename, const std::string& inputFile, const std::string& outputFile);
		std::vector <string_list> getCommands() const;
	private:
		void parsingWorkflowFile(const std::string& filename);
		std::vector <string_list> commands_;
	};
}