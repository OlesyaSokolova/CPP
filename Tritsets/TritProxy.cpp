#include <algorithm>
#include "TritSet.h"
#include "TritProxy.h"
#include "TritClass.h"
namespace TritSets {
	TritProxy::TritProxy(uint& block, uint pos, TritSet * trit_set, uint proxyCounter, uint proxyDataSize, Trit trit)
		: block_(block), pos_(pos), trit_set_(trit_set), proxyCounter_(proxyCounter), proxyDataSize_(proxyDataSize), trit_(trit) {}
	Trit TritProxy::GetTrit()
	{
		return this->trit_;
	}
	Mask TritProxy::getMask(Trit trit)
	{
		Mask mask;
		switch (trit)
		{
		case False:
			mask.first_ = 0;
			mask.second_ = 1;
			break;
		case Unknown:
			mask.first_ = 0;
			mask.second_ = 0;
			break;
		case True:
			mask.first_ = 1;
			mask.second_ = 0;
			break;
		}
		return mask;
	}

	void TritProxy::operator=(Trit trit)
	{
		if (this->trit_set_->GetCountTrits() < proxyCounter_ && trit == Unknown)
		{
			this->trit_set_->DataResize(proxyDataSize_);
			return;
		}
		this->trit_set_->ChangeCountTrits(proxyCounter_);
		// set mask:
		Mask mask = getMask(trit);
		// calculate first bit position:
		int pos_1 = pos_ * 2 + 1;
		// calculate second bit position:
		int pos_2 = pos_ * 2;

		// set first bit:
		block_ &= ~(1 << (pos_1));
		block_ |= (mask.first_ << pos_1);
		//set second bit:
		block_ &= ~(1 << (pos_2));
		block_ |= (mask.second_ << pos_2);
	}

	bool TritProxy::operator==(Trit trit)
	{
		return (this->trit_ == trit);
	}
	bool TritProxy::operator!=(Trit trit)
	{
		return !(this->trit_ == trit);
	}
	TritProxy::operator Trit() const
	{
		return this->trit_;
	}
}