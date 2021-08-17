#pragma once
#include <vector>
#include "TritSet.h"
#include "Consts.h"
using namespace consts;
namespace TritSets {
	
	struct Mask
	{
		//False = 01
		//Unknown = 00
		//True = 10
		int first_;
		int second_;
	};

	class TritSet;

	class TritProxy
	{
	public:
		TritProxy(uint& block, uint pos, TritSet * trit_set, uint proxyCounter, uint proxyDataSize, Trit trit);
		void operator=(Trit trit);
		Mask getMask(Trit trit);
		Trit GetTrit();
		bool operator==(Trit trit);
		bool operator!=(Trit trit);
		operator Trit() const;
	private:
		uint& block_;
		uint pos_;
		TritSet * trit_set_;
		uint proxyCounter_;
		uint proxyDataSize_;
		Trit trit_;
	};
}