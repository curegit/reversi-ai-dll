// DLLアプリケーションの単体テストを記述します

// プリコンパイル済みヘッダー
#include "stdafx.h"

// 単体テストモジュール
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReversiAiDllTest
{
	// テストメソッドを定義するクラス
	TEST_CLASS(UnitTest)
	{
	public:
		// 
		TEST_METHOD(PositionEncoderTestMethod)
		{
			// 

			// 

			// 
			Assert::AreEqual(decode_position_i(encode_position(3, 5)), 3);
			Assert::AreEqual(decode_position_j(encode_position(3, 5)), 5);
			// 
		}

		//
		TEST_METHOD(NegaMaxTestMethod)
		{

		}
	};
}
