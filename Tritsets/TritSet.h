#pragma once
#include <vector>
#include "TritProxy.h"
#include "Consts.h"
#include <unordered_map>
using namespace consts;
namespace TritSets {
	
	class TritSet
	{
	public:
		void ChangeTrit(Trit trit, uint i, int j);
		uint GetDataSize() const;
		uint GetDataValue(uint i) const;
		uint GetCountTrits() const;
		void ChangeCountTrits(uint newCounter);
		void DataResize(uint newSize);
		TritSet(const TritSet& other);
		TritSet(uint countTrits);
		

		void trim(size_t lastIndex);
		size_t cardinality(Trit value) const;
		size_t length() const;
		uint capacity() const;
		void shrink();
		std::unordered_map<Trit, int, std::hash<int>> cardinality() const;

		TritProxy operator[](uint indexTrit);
		void operator =(const TritSet& other);
		TritSet operator &(const TritSet& B);
		TritSet operator |(const TritSet& B);
		TritSet operator ~();
		operator Trit() const;
		Trit getTrit(uint indexTrit);
	private:
		uint sizeNeeded(uint countTrits);
	private:
		uint countTrits_;
		std::vector<uint> data_;
	};
}
