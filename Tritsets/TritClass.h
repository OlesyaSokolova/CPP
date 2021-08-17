#pragma once
#include "TritSet.h"
namespace TritSets {
	class TritClass {
	public:
		TritClass();
		Trit TritReconstruction(const TritSet& other, uint block, int index);
		void InitTrit(Trit trit);
		void ChangeTrit(Trit trit);
		Trit GetTrit() const;
		Trit operator &(const TritClass& AnotherTrit);
		Trit operator |(const TritClass& AnotherTrit);
		Trit operator ~();
		void operator=(TritProxy proxy);
	private:
		Trit trit_;
		const TritSet & trit_set_;
	};
}