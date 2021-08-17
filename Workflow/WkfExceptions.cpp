#include "WkfExceptions.h"
namespace workflow {
	WkfException::WkfException(std::string message, std::string workerName)
		:std::exception(message.c_str()), workerName_(workerName) {}

	std::string WkfException::mistakeStage() const
	{
		return "Stage: " + workerName_;
	}
}