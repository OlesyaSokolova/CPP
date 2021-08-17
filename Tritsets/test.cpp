#include "pch.h"
#include <gtest/gtest.h>
#include <ctime>
#include <algorithm>

#include "../new/Consts.h"
#include "../new/TritSetOperators.cpp"
#include "../new/TritSetFunctions.cpp"
#include "../new/TritProxy.cpp"
#include "../new/TritClass.cpp"

using namespace consts;
using namespace TritSets;
	TEST(TritSetFunctions, Constructor)
	{
		srand(time(NULL));
		uint x = rand() % 100000;
		TritSet TestSet(x);
		ASSERT_EQ(TestSet.GetCountTrits(), 0);
		size_t allocLength = TestSet.capacity();
		assert(allocLength >= 32 * 2 / 8 / sizeof(uint));
	}
	TEST(TritSetFunctions, Shrink)
	{
		srand(time(NULL));
		uint x = rand() % 100000;
		TritSet TestSet(x);
		TestSet.shrink();
		ASSERT_EQ(TestSet.GetDataSize(), 0);
	}
	TEST(TritSetFunctions, Cardinality)
	{
		TritSet TestSetA(5);
		TestSetA[0] = Unknown;
		TestSetA[1] = True;
		TestSetA[2] = False;
		TestSetA[3] = Unknown;
		TestSetA[4] = True;
		ASSERT_EQ(TestSetA.cardinality(True), 2);
		ASSERT_EQ(TestSetA.cardinality(Unknown), 2);
		ASSERT_EQ(TestSetA.cardinality(False), 1);
		std::unordered_map<Trit, int, std::hash<int> > table = TestSetA.cardinality();
		ASSERT_EQ(table[True], 2);
		ASSERT_EQ(table[False], 1);
		ASSERT_EQ(table[Unknown], 2);
	}
	TEST(TritSetFunctions, LogicalLength)
	{
		TritSet TestSetA(67);
		TestSetA[0] = Unknown;
		TestSetA[1] = True;
		TestSetA[2] = False;
		TestSetA[3] = Unknown;
		TestSetA[4] = True;
		ASSERT_EQ(TestSetA.length(), 5);
	}
	TEST(TritSetFunctions, Trim)
	{
		TritSet TestSetA(5);
		TestSetA[0] = Unknown;
		TestSetA[1] = True;
		TestSetA[2] = False;
		TestSetA[3] = Unknown;
		TestSetA[4] = True;
		TestSetA.trim(2);
		ASSERT_EQ(TestSetA.GetDataValue(0), 24);
		ASSERT_EQ(TestSetA.GetCountTrits(), 3);
	}
	TEST(TritSetServiceMethods, GetCountTrits)
	{
		TritSet TestSetA(5);
		TestSetA[0] = Unknown;
		TestSetA[1] = True;
		TestSetA[2] = False;
		TestSetA[3] = Unknown;
		TestSetA[4] = True;
		int i = rand() % 1000;
		Trit trit = (Trit)(rand() % 3);
		TestSetA[i] = trit;
		if (trit == Unknown)
		{
			ASSERT_EQ(TestSetA.GetCountTrits(), 5);
		}
		else
		{
			ASSERT_EQ(TestSetA.GetCountTrits(), i + 1);
		}
	}
	TEST(TritSetServiceMethods, ChangeCountTrits)
	{
		TritSet TestSetA(5);
		uint y = rand() % 10000;
		TestSetA.ChangeCountTrits(y);
		ASSERT_EQ(TestSetA.GetCountTrits(), y);
	}
	TEST(TritSetServiceMethods, GetDataSize)
	{
		TritSet TestSetA(5);
		ASSERT_EQ(TestSetA.GetDataSize(), (TestSetA.capacity() / TRITS_IN_UINT));
	}
	TEST(TritSetServiceMethods, GetDataValue)
	{
		TritSet TestSetA(5);
		TestSetA[0] = Unknown;
		TestSetA[1] = True;
		TestSetA[2] = False;
		TestSetA[3] = Unknown;
		TestSetA[4] = True;
		ASSERT_EQ(TestSetA.GetDataValue(0), 536);
	}
	TEST(TritSetServiceMethods, ChangeTrit)
	{
		TritSet TestSetA(5);
		Trit trit = (Trit)(rand() % 3);
		uint index = rand() % 16;
		uint block = rand() % (TestSetA.capacity() / TRITS_IN_UINT);
		TestSetA.ChangeTrit(trit, block, index);
		TritProxy ProxySet = TestSetA[block*TRITS_IN_UINT + index];
		ASSERT_EQ(ProxySet.GetTrit(), trit);
	}
	TEST(TritSetServiceMethods, DataResize)
	{
		TritSet TestSetA(5);
		int newSize = rand() % 10000;
		TestSetA.DataResize(newSize);
		ASSERT_EQ(TestSetA.GetDataSize(), newSize);
	}
	TEST(TritSetOperators, IndexationOperator1)
	{
		uint x = rand() % 10000;
		TritSet TestSet(x);
		size_t allocLength = TestSet.capacity();
		TestSet[10000000] = Unknown;
		assert(allocLength == TestSet.capacity());
		TestSet[10000000] = True;
		assert(allocLength < TestSet.capacity());

		TritSet TestSetA(5);
		TestSetA[0] = Unknown;
		TestSetA[1] = True;
		TestSetA[2] = False;
		TestSetA[3] = Unknown;
		TestSetA[4] = True;
		ASSERT_EQ(TestSetA.GetDataValue(0), 536);
	}
	TEST(TritSetOperators, IndexationOperator2)
	{
		TritSet TestSetA(5);
		int i = rand() % 1000;
		Trit trit = (Trit)(rand() % 3);
		TestSetA[i] = trit;
		Trit trit1;
		trit1 = (Trit)TestSetA[i];
		ASSERT_EQ(trit1, trit);
	}


	TEST(TritSetOperators, Not)
	{
		TritSet TestSetA(5);
		TestSetA[0] = Unknown;
		TestSetA[1] = True;
		TestSetA[2] = False;
		TestSetA[3] = Unknown;
		TestSetA[4] = True;

		TritSet TestSetB(1);
		TestSetB[0] = True;
		TestSetB[1] = True;
		TestSetB[2] = Unknown;
		TestSetB[3] = False;
		TestSetB[4] = True;
		TestSetB[5] = True;
		TestSetB[6] = False;

		ASSERT_EQ((TestSetB).GetDataValue(0), 6730);
		// ~
		ASSERT_EQ((~TestSetA).GetDataValue(0), 292);
	}
	TEST(TritSetOperators, And)
	{
		TritSet TestSet1(1);
		TestSet1[0] = Unknown;
		TestSet1[1] = True;
		TestSet1[2] = False;
		TestSet1[3] = Unknown;
		TestSet1[4] = True;

		TritSet TestSet2(1);
		TestSet2[0] = True;
		TestSet2[1] = True;
		TestSet2[2] = Unknown;
		TestSet2[3] = False;
		TestSet2[4] = True;
		TestSet2[5] = True;
		TestSet2[6] = False;
		TritSet TestSet3 = TestSet1 & TestSet2;
		EXPECT_EQ((TestSet2).GetDataValue(0), 6730);
		EXPECT_EQ((TestSet3).GetDataValue(0), 4696);
		assert(TestSet3.capacity() == (std::max(TestSet1.capacity(), TestSet2.capacity())));
	}
	TEST(TritSetOperators, Or)
	{
		TritSet TestSet1(1);
		TestSet1[0] = Unknown;
		TestSet1[1] = True;
		TestSet1[2] = False;
		TestSet1[3] = Unknown;
		TestSet1[4] = True;

		TritSet TestSet2(1);
		TestSet2[0] = True;
		TestSet2[1] = True;
		TestSet2[2] = Unknown;
		TestSet2[3] = False;
		TestSet2[4] = True;
		TestSet2[5] = True;
		TestSet2[6] = False;

		TritSet TestSet3 = TestSet1 | TestSet2;
		ASSERT_EQ((TestSet3).GetDataValue(0), 2570);
		assert(TestSet3.capacity() == (std::max(TestSet1.capacity(), TestSet2.capacity())));
	}
	TEST(TritSetOperators, AssignmentOperator)
	{
		TritSet TestSetA(5);
		TestSetA[0] = Unknown;
		TestSetA[1] = True;
		TestSetA[2] = False;
		TestSetA[3] = Unknown;
		TestSetA[4] = True;

		TritSet TestSetB(7);
		TestSetB[0] = True;
		TestSetB[1] = True;
		TestSetB[2] = Unknown;
		TestSetB[3] = False;
		TestSetB[4] = True;
		TestSetB[5] = True;
		TestSetB[6] = False;

		TestSetA = TestSetB;
		ASSERT_EQ((TestSetB).GetDataValue(0), (TestSetA).GetDataValue(0));
		ASSERT_EQ((TestSetB).GetCountTrits(), (TestSetA).GetCountTrits());
		ASSERT_EQ((TestSetB).capacity(), (TestSetA).capacity());
	}
	TEST(TritSetOperators, CopyOperator)
	{
		TritSet TestSetB(7);
		TestSetB[0] = True;
		TestSetB[1] = True;
		TestSetB[2] = Unknown;
		TestSetB[3] = False;
		TestSetB[4] = True;
		TestSetB[5] = True;
		TestSetB[6] = False;

		TritSet TestSetD(TestSetB);
		ASSERT_EQ(TestSetD.GetDataValue(0), TestSetB.GetDataValue(0));
		ASSERT_EQ(TestSetD.GetCountTrits(), TestSetB.GetCountTrits());
		ASSERT_EQ(TestSetD.capacity(), TestSetB.capacity());
	}
	TEST(TritSetOperators, IsEqualOperator)
	{
		TritSet TestSetA(1);
		int i = rand() % 1000;
		Trit trit = (Trit)(rand() % 3);
		TestSetA[i] = trit;
		ASSERT_EQ(TestSetA[i] == trit, true);
	}
	TEST(TritSetOperators, IsNotEqualOperator)
	{
		TritSet TestSetA(1);
		int i = rand() % 1000;
		Trit trit = (Trit)(rand() % 3);
		TestSetA[i] = (Trit)((trit + 1) % 3);
		ASSERT_EQ(TestSetA[i] != trit, true);
	}
	int main(int argc, char **argv) {
		::testing::InitGoogleTest(&argc, argv);
		return RUN_ALL_TESTS();
	}