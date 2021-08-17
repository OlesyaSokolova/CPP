#include "TritClass.h"
namespace TritSets {

	TritClass::TritClass()
		:trit_set_(NULL), trit_(Unknown) {}
	Trit TritClass::GetTrit() const
	{
		return trit_;
	}
	void TritClass::ChangeTrit(Trit trit)
	{
		this->trit_ = trit;
	}

	Trit TritClass::TritReconstruction(const TritSet&  other, uint block, int index)
	{
		int pos1, pos2;
		int bit1, bit2;
		pos1 = index * 2 + 1;
		pos2 = index * 2;
		bit1 = (other.GetDataValue(block) & (1 << pos1)) > 0 ? 1 : 0;
		bit2 = (other.GetDataValue(block) & (1 << pos2)) > 0 ? 1 : 0;

		if (bit1 == 0 && bit2 == 1)
			return False;
		if (bit1 == 0 && bit2 == 0)
			return Unknown;
		if (bit1 == 1 && bit2 == 0)
			return True;
	}

	void TritClass::InitTrit(Trit trit)
	{
		this->trit_ = trit;
	}

	Trit TritClass::operator &(const TritClass& AnotherTrit)
	{
		Trit result;
		if (this->trit_ == False && AnotherTrit.GetTrit() == False)
		{
			result = False;
		}
		if (this->trit_ == False && AnotherTrit.GetTrit() == Unknown)
		{
			result = False;
		}
		if (this->trit_ == False && AnotherTrit.GetTrit() == True)
		{
			result = False;
		}
		/////////////////////////////////////////////////
		if (this->trit_ == Unknown && AnotherTrit.GetTrit() == False)
		{
			result = False;
		}
		if (this->trit_ == Unknown && AnotherTrit.GetTrit() == Unknown)
		{
			result = Unknown;
		}
		if (this->trit_ == Unknown && AnotherTrit.GetTrit() == True)
		{
			result = Unknown;
		}
		/////////////////////////////////////////////////
		if (this->trit_ == True && AnotherTrit.GetTrit() == False)
		{
			result = False;
		}
		if (this->trit_ == True && AnotherTrit.GetTrit() == Unknown)
		{
			result = Unknown;
		}
		if (this->trit_ == True && AnotherTrit.GetTrit() == True)
		{
			result = True;
		}
		return result;
	}

	Trit TritClass::operator |(const TritClass& AnotherTrit)
	{
		Trit result;
		if (this->trit_ == False && AnotherTrit.GetTrit() == False)
		{
			result = False;
		}
		if (this->trit_ == False && AnotherTrit.GetTrit() == Unknown)
		{
			result = Unknown;
		}
		if (this->trit_ == False && AnotherTrit.GetTrit() == True)
		{
			result = True;
		}
		/////////////////////////////////////////////////
		if (this->trit_ == Unknown && AnotherTrit.GetTrit() == False)
		{
			result = Unknown;
		}
		if (this->trit_ == Unknown && AnotherTrit.GetTrit() == Unknown)
		{
			result = Unknown;
		}
		if (this->trit_ == Unknown && AnotherTrit.GetTrit() == True)
		{
			result = True;
		}
		/////////////////////////////////////////////////
		if (this->trit_ == True && AnotherTrit.GetTrit() == False)
		{
			result = True;
		}
		if (this->trit_ == True && AnotherTrit.GetTrit() == Unknown)
		{
			result = True;
		}
		if (this->trit_ == True && AnotherTrit.GetTrit() == True)
		{
			result = True;
		}
		return result;
	}

	Trit TritClass::operator ~()
	{
		Trit result;
		if (this->trit_ == False)
		{
			result = True;
		}
		if (this->trit_ == Unknown)
		{
			result = Unknown;
		}
		if (this->trit_ == True)
		{
			result = False;
		}
		return result;
	}
	void TritClass::operator=(TritProxy proxy)
	{
		this->ChangeTrit(proxy.GetTrit());
	}
}
