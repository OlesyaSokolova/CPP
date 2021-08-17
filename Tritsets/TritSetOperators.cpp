#include "TritSet.h"
#include "TritClass.h"
#include <algorithm>
using namespace consts;
namespace TritSets {

	Trit TritSet::getTrit(uint indexTrit)
	{
		uint indexBlock = (indexTrit / TRITS_IN_UINT);
		uint blockPosTrit = indexTrit % TRITS_IN_UINT;
		TritClass ProxyTrit;
		return ProxyTrit.TritReconstruction(*this, indexBlock, blockPosTrit);
	}
	TritProxy TritSet::operator[](uint indexTrit)
	{
		int proxyDataSize = this->data_.size();
		if (indexTrit > this->capacity() - 1)
		{
			int x = sizeNeeded(indexTrit + 1);
			data_.resize(x, 0);
		}
		int proxyCounter = std::max(indexTrit + 1, countTrits_);
		uint indexBlock = (indexTrit / TRITS_IN_UINT);
		uint blockPosTrit = indexTrit % TRITS_IN_UINT;
		TritClass ProxyTrit;
		Trit trit = ProxyTrit.TritReconstruction(*this, indexBlock, blockPosTrit);
		TritProxy result(data_[indexBlock], blockPosTrit, this, proxyCounter, proxyDataSize, trit);
		return result;
	}
	TritSet::TritSet(const TritSet& other)
	{
		this->countTrits_ = other.GetCountTrits();
		this->data_.resize(other.GetDataSize());
		for (uint i = 0; i < other.GetDataSize(); i++)
		{
			this->data_[i] = other.GetDataValue(i);
		}
	}
	void TritSet::operator =(const TritSet& other)
	{
		this->countTrits_ = other.GetCountTrits();
		this->data_.clear();
		this->data_.resize(other.GetDataSize());
		for (uint i = 0; i < other.GetDataSize(); i++)
		{
			this->data_[i] = other.GetDataValue(i);
		}
	}
	TritSet TritSet::operator ~()
	{
		TritSet result(*this);
		uint k = 0;
		for (uint i = 0; i < this->data_.size(); i++)
		{
			for (int j = 0; j < TRITS_IN_UINT && k <= this->countTrits_; j++)
			{
				k++;
				TritClass NewTrit;
				NewTrit.InitTrit(NewTrit.TritReconstruction(*this, i, j));
				Trit trit = ~NewTrit;
				result.ChangeTrit(trit, i, j);
			}
		}
		return result;
	}

	TritSet TritSet::operator |(const TritSet& B)
	{
		TritSet C((uint)std::max(this->capacity(), B.capacity()));
		C.ChangeCountTrits(std::max(this->countTrits_, B.GetCountTrits()));
		uint k = 0;
		for (uint i = 0; i < C.GetDataSize(); i++)
		{
			for (int j = 0; j < TRITS_IN_UINT && k < C.GetCountTrits(); j++)
			{
				k++;
				TritClass NewTrit1;
				TritClass NewTrit2;
				NewTrit1.InitTrit(NewTrit1.TritReconstruction(*this, i, j));
				NewTrit2.InitTrit(NewTrit1.TritReconstruction(B, i, j));
				Trit trit = NewTrit1 | NewTrit2;
				C.ChangeTrit(trit, i, j);
			}
		}
		return C;
	}
	TritSet TritSet::operator &(const TritSet& B)
	{
		TritSet C((uint)std::max(this->capacity(), B.capacity()));
		C.ChangeCountTrits(std::max(this->countTrits_, B.GetCountTrits()));
		uint k = 0;
		for (uint i = 0; i < C.GetDataSize(); i++)
		{
			for (int j = 0; j < TRITS_IN_UINT && k < C.GetCountTrits(); j++)
			{
				k++;
				TritClass NewTrit1;
				TritClass NewTrit2;
				NewTrit1.InitTrit(NewTrit1.TritReconstruction(*this, i, j));
				NewTrit2.InitTrit(NewTrit1.TritReconstruction(B, i, j));
				Trit trit = NewTrit1 & NewTrit2;
				C.ChangeTrit(trit, i, j);
			}
		}
		return C;
	}
	
}