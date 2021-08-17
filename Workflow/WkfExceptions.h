#pragma once
#include <fstream>
#include <iostream>
namespace workflow {
	class WkfException : public std::exception
	{
	public:
		WkfException(std::string message, std::string workerName);
		std::string mistakeStage() const;
	private:
		std::string workerName_;
	};
}