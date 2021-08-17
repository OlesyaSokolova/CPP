#include "TritSet.h"
#include "TritClass.h"
#include <algorithm>
namespace TritSets {
	void TritSet::ChangeTrit(Trit trit, uint i, int j)
	{
		int pos1 = j * 2 + 1;
		int pos2 = j * 2;
		if (trit == False)
		{//set  01
			data_[i] &= ~(1 << (pos1));
			data_[i] |= (0 << pos1);

			data_[i] &= ~(1 << (pos2));
			data_[i] |= (1 << pos2);
		}
		if (trit == True)
		{//set 10
			data_[i] &= ~(1 << (pos1));
			data_[i] |= (1 << pos1);

			data_[i] &= ~(1 << (pos2));
			data_[i] |= (0 << pos2);
		}
		if (trit == Unknown)
		{//set  00
			data_[i] &= ~(1 << (pos1));
			data_[i] |= (0 << pos1);

			data_[i] &= ~(1 << (pos2));
			data_[i] |= (0 << pos2);
		}
	}

	TritSet::TritSet(uint countTrits)
	{
		countTrits_ = 0;
		int x = sizeNeeded(countTrits);
		data_.resize(x, 0);
	}

	uint TritSet::sizeNeeded(uint countTrits)
	{
		return ((countTrits % TRITS_IN_UINT) == 0) ? (countTrits / TRITS_IN_UINT) : (countTrits / TRITS_IN_UINT) + 1;
	}

	uint TritSet::capacity() const
	{
		return data_.size()* TRITS_IN_UINT;
	}

	uint TritSet::GetDataSize() const
	{
		return data_.size();
	}

	uint TritSet::GetCountTrits() const
	{
		return countTrits_;
	}

	uint TritSet::GetDataValue(uint i) const
	{
		return data_[i];
	}

	void TritSet::ChangeCountTrits(uint newCounter)
	{
		countTrits_ = newCounter;
	}

	void TritSet::DataResize(uint newSize)
	{
		data_.resize(newSize);
	}

	void TritSet::shrink()
	{//обрезка всей лишней памяти
		int emptyBlocks = 0;
		for (int i = data_.size() - 1; i >= 0; i--)
		{
			if (data_[i] == 0)
				emptyBlocks++;
			else break;
		}
		data_.resize(data_.size() - emptyBlocks);
		countTrits_ = std::min(countTrits_, this->capacity());
	}

	void TritSet::trim(size_t lastIndex)
	{
		uint block = lastIndex / TRITS_IN_UINT;
		uint index = lastIndex % TRITS_IN_UINT;
		for (int k = index + 1; k < TRITS_IN_UINT; k++)
		{
			this->ChangeTrit(Unknown, block, k);
		}
		for (uint i = block + 1; i < data_.size(); i++)
		{
			data_[i] = 0;
		}
		countTrits_ = lastIndex + 1;
	}

	size_t TritSet::cardinality(Trit value) const
	{
		uint k = 0;
		uint counter = 0;
		for (uint i = 0; i < this->data_.size(); i++)
		{
			for (int j = 0; j < TRITS_IN_UINT && k < this->countTrits_; j++)
			{
				k++;
				TritClass NewTrit;
				Trit trit = NewTrit.TritReconstruction(*this, i, j);
				if (trit == value)
				{
					counter++;
				}
			}
		}
		return counter;
	}

	size_t TritSet::length() const
	{
		return countTrits_;
	}

	std::unordered_map<Trit, int, std::hash<int> > TritSet::cardinality() const
	{
		std::unordered_map<Trit, int, std::hash<int>> result;
		result.insert({ False, 0 });
		result.insert({ Unknown, 0 });
		result.insert({ True, 0 });
		uint k = 0;
		for (uint i = 0; i < this->data_.size(); i++)
		{
			for (int j = 0; j < TRITS_IN_UINT && k < this->countTrits_; j++)
			{
				k++;
				TritClass NewTrit;
				Trit trit = NewTrit.TritReconstruction(*this, i, j);
				result[trit]++;
			}
		}
		return result;
	}
}