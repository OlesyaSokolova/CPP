#pragma once
#include <optional>
#include "Consts.h"
#include <functional>
#include "Worker.h"

using namespace consts;
namespace workflow {
	class Executor {
	public:
		Executor(const std::vector<string_list>& commands, std::function<Worker*(const string_list&)> creatorFunction);
		void run();
	private:
		std::vector<string_list> commands_;
		std::optional <string_list> data_prev_;
		std::function<Worker *(const string_list&)> creatorFunction_;
	};
}