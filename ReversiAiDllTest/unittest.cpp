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
		// 位置座標とビット番号の相互変換テスト
		TEST_METHOD(PositionConversionTest)
		{
			// 位置座標からビット番号への変換テスト
			Assert::AreEqual(position_to_index(0, 0), 0);
			Assert::AreEqual(position_to_index(1, 0), 1);
			Assert::AreEqual(position_to_index(7, 0), 7);
			Assert::AreEqual(position_to_index(0, 1), 8);
			Assert::AreEqual(position_to_index(4, 2), 20);
			Assert::AreEqual(position_to_index(5, 3), 29);
			Assert::AreEqual(position_to_index(6, 5), 46);
			Assert::AreEqual(position_to_index(7, 7), 63);
			// ビット番号からi座標を取り出すテスト
			Assert::AreEqual(index_to_position_i(0), 0);
			Assert::AreEqual(index_to_position_i(1), 1);
			Assert::AreEqual(index_to_position_i(7), 7);
			Assert::AreEqual(index_to_position_i(8), 0);
			Assert::AreEqual(index_to_position_i(21), 5);
			Assert::AreEqual(index_to_position_i(27), 3);
			Assert::AreEqual(index_to_position_i(44), 4);
			Assert::AreEqual(index_to_position_i(63), 7);
			// ビット番号からj座標を取り出すテスト
			Assert::AreEqual(index_to_position_j(0), 0);
			Assert::AreEqual(index_to_position_j(7), 0);
			Assert::AreEqual(index_to_position_j(8), 1);
			Assert::AreEqual(index_to_position_j(16), 2);
			Assert::AreEqual(index_to_position_j(30), 3);
			Assert::AreEqual(index_to_position_j(39), 4);
			Assert::AreEqual(index_to_position_j(55), 6);
			Assert::AreEqual(index_to_position_j(63), 7);
		}

		// 着手可能な手を調べるテスト
		TEST_METHOD(PossibleMoveTest)
		{
			// 黒が置く
			Assert::AreEqual(possible_moves(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull, const_dark()), 0x0000'0804'2010'0000ull);
			Assert::AreEqual(possible_moves(0x0000'003C'0010'0000ull, 0x0000'0800'3C48'0000ull, const_dark()), 0x001C'0040'0026'8C00ull);
			Assert::AreEqual(possible_moves(0x0000'0038'0412'0000ull, 0x0000'0A04'3848'0000ull, const_dark()), 0x000D'0442'4024'9C00ull);
			Assert::AreEqual(possible_moves(0x0000'101E'1402'0000ull, 0x0000'2A20'2878'0000ull, const_dark()), 0x005F'4440'4004'FC00ull);
			Assert::AreEqual(possible_moves(0x0000'1018'0006'0000ull, 0x0000'2A26'3E78'0000ull, const_dark()), 0x004E'4441'4080'D800ull);
			Assert::AreEqual(possible_moves(0x0042'3408'2020'2800ull, 0x0000'0A76'1E5E'1200ull, const_dark()), 0x000D'8181'C181'851Bull);
			Assert::AreEqual(possible_moves(0x0046'7C78'6000'0000ull, 0x0000'0206'1E7E'7E10ull, const_dark()), 0x0000'0101'0101'81EFull);
			Assert::AreEqual(possible_moves(0x0046'CE0D'2643'F300ull, 0x0090'3172'D83C'0C14ull, const_dark()), 0xB021'0080'0100'000Aull);
			// 白が置く
			Assert::AreEqual(possible_moves(0x0000'0010'1810'0000ull, 0x0000'0008'0000'0000ull, const_light()), 0x0000'0020'0028'0000ull);
			Assert::AreEqual(possible_moves(0x0000'0010'3008'0400ull, 0x0000'0008'0830'0000ull, const_light()), 0x0000'3060'4004'0800ull);
			Assert::AreEqual(possible_moves(0x0000'0012'0418'1C00ull, 0x0000'0008'7822'0000ull, const_light()), 0x0000'3820'0204'201Eull);
			Assert::AreEqual(possible_moves(0x0000'101E'1C06'0000ull, 0x0000'2A20'2078'0000ull, const_light()), 0x0018'0501'0201'0200ull);
			Assert::AreEqual(possible_moves(0x0040'3018'0006'0000ull, 0x0000'0A26'3E78'0000ull, const_light()), 0x8038'4400'0001'0F00ull);
			Assert::AreEqual(possible_moves(0x0046'7E7F'6000'0000ull, 0x0000'0000'1E7E'7E10ull, const_light()), 0xC7B9'8180'8000'0000ull);
			Assert::AreEqual(possible_moves(0x0046'7E7D'2442'FF00ull, 0x0000'0102'DA3C'0010ull, const_light()), 0xC7B9'8080'0181'00EFull);
			Assert::AreEqual(possible_moves(0x80C6'CE0D'2E4B'FD08ull, 0x0010'3172'D034'0215ull, const_light()), 0x4709'0000'0180'00E2ull);
		}

		// 返せる石を調べるテスト
		TEST_METHOD(TurnoverTest)
		{
			// 黒が置く
			Assert::AreEqual(turnovers(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull, const_dark(), position_to_index(5, 3)), 0x0000'0000'1000'0000ull);
			Assert::AreEqual(turnovers(0x0000'003C'0010'0000ull, 0x0000'0800'3C48'0000ull, const_dark(), position_to_index(2, 2)), 0x0000'0000'0C08'0000ull);
			Assert::AreEqual(turnovers(0x0000'0038'0412'0000ull, 0x0000'0A04'3848'0000ull, const_dark(), position_to_index(2, 5)), 0x0000'0004'0000'0000ull);
			Assert::AreEqual(turnovers(0x0000'101E'1402'0000ull, 0x0000'2A20'2878'0000ull, const_dark(), position_to_index(6, 3)), 0x0000'0020'2000'0000ull);
			Assert::AreEqual(turnovers(0x0000'1018'0006'0000ull, 0x0000'2A26'3E78'0000ull, const_dark(), position_to_index(6, 6)), 0x0000'2000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0042'3408'2020'2800ull, 0x0000'0A76'1E5E'1200ull, const_dark(), position_to_index(0, 4)), 0x0000'0006'0204'0000ull);
			Assert::AreEqual(turnovers(0x0046'7C78'6000'0000ull, 0x0000'0206'1E7E'7E10ull, const_dark(), position_to_index(0, 0)), 0x0000'0000'0804'0200ull);
			Assert::AreEqual(turnovers(0x0046'CE0D'2643'F300ull, 0x0090'3172'D83C'0C14ull, const_dark(), position_to_index(7, 4)), 0x0000'0070'4020'0000ull);
			// 白が置く
			Assert::AreEqual(turnovers(0x0000'0010'1810'0000ull, 0x0000'0008'0000'0000ull, const_light(), position_to_index(5, 2)), 0x0000'0000'1000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0010'3008'0400ull, 0x0000'0008'0830'0000ull, const_light(), position_to_index(5, 4)), 0x0000'0010'2000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0012'0418'1C00ull, 0x0000'0008'7822'0000ull, const_light(), position_to_index(2, 2)), 0x0000'0000'0018'0000ull);
			Assert::AreEqual(turnovers(0x0000'101E'1C06'0000ull, 0x0000'2A20'2078'0000ull, const_light(), position_to_index(2, 5)), 0x0000'0008'1000'0000ull);
			Assert::AreEqual(turnovers(0x0040'3018'0006'0000ull, 0x0000'0A26'3E78'0000ull, const_light(), position_to_index(7, 7)), 0x0040'2010'0000'0000ull);
			Assert::AreEqual(turnovers(0x0046'7E7F'6000'0000ull, 0x0000'0000'1E7E'7E10ull, const_light(), position_to_index(1, 7)), 0x0006'0A12'2000'0000ull);
			Assert::AreEqual(turnovers(0x0046'7E7D'2442'FF00ull, 0x0000'0102'DA3C'0010ull, const_light(), position_to_index(7, 5)), 0x0000'7E40'2000'0000ull);
			Assert::AreEqual(turnovers(0x80C6'CE0D'2E4B'FD08ull, 0x0010'3172'D034'0215ull, const_light(), position_to_index(0, 3)), 0x0000'0001'0E01'0100ull);
		}

		// ネガマックス法のテスト
		TEST_METHOD(NegaMaxTest)
		{

		}
	};
}
