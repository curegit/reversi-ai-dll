#include "stdafx.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReversiAiDllTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: テスト コードをここに挿入します

			Assert::AreEqual(choose_move(3, 4, 5), 0);
		}

	};
}