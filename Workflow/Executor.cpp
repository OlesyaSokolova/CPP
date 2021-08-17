#include "Executor.h"
#include "worker.h"
#include "WkfExceptions.h"
#include <functional>
#include <vector>

using namespace consts;
namespace workflow {
	Executor::Executor(
		const std::vector<string_list>& commands, 
		std::function<Worker*(const string_list&)> creatorFunction)
		:commands_(commands), data_prev_(std::nullopt) , creatorFunction_(creatorFunction) {}

	void Executor::run()
	{
		Worker *w = nullptr;
		try
		{
			for (auto i = 0; i < commands_.size(); i++)
			{
				w = creatorFunction_(commands_[i]);
				w->validate(data_prev_);
				data_prev_ = w->doSomeWork(data_prev_);
			}
		}
		catch (const WkfException& ex)
		{
			if (w != nullptr)
			{
				delete w;
			}
			throw ex;
		}
		catch (const std::exception& ex)
		{
			if (w != nullptr)
			{
				delete w;
			}
			throw ex;
		}
	}
}