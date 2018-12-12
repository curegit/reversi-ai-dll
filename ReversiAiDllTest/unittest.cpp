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

		// 立っているビットの数を数えるテスト
		TEST_METHOD(BitCountTest)
		{
			Assert::AreEqual(count_bits(0x0000'0000'0000'0000ull), 0);
			Assert::AreEqual(count_bits(0x0000'0000'0000'0001ull), 1);
			Assert::AreEqual(count_bits(0x1000'0000'0000'0000ull), 1);
			Assert::AreEqual(count_bits(0x0A00'C0D0'1E00'0430ull), 14);
			Assert::AreEqual(count_bits(0x3004'0500'00BD'7008ull), 15);
			Assert::AreEqual(count_bits(0x0123'4567'89AB'CDEFull), 32);
		}

		// 着手可能な手を調べるテスト
		TEST_METHOD(PossibleMoveTest)
		{
			// 黒が置く
			Assert::AreEqual(possible_moves(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull), 0x0000'0804'2010'0000ull);
			Assert::AreEqual(possible_moves(0x0000'003C'0010'0000ull, 0x0000'0800'3C48'0000ull), 0x001C'0040'0026'8C00ull);
			Assert::AreEqual(possible_moves(0x0000'0038'0412'0000ull, 0x0000'0A04'3848'0000ull), 0x000D'0442'4024'9C00ull);
			Assert::AreEqual(possible_moves(0x0000'101E'1402'0000ull, 0x0000'2A20'2878'0000ull), 0x005F'4440'4004'FC00ull);
			Assert::AreEqual(possible_moves(0x0000'1018'0006'0000ull, 0x0000'2A26'3E78'0000ull), 0x004E'4441'4080'D800ull);
			Assert::AreEqual(possible_moves(0x0042'3408'2020'2800ull, 0x0000'0A76'1E5E'1200ull), 0x000D'8181'C181'851Bull);
			Assert::AreEqual(possible_moves(0x0046'7C78'6000'0000ull, 0x0000'0206'1E7E'7E10ull), 0x0000'0101'0101'81EFull);
			Assert::AreEqual(possible_moves(0x0046'CE0D'2643'F300ull, 0x0090'3172'D83C'0C14ull), 0xB021'0080'0100'000Aull);
			// 黒の番だがどこにも置けないとき
			Assert::AreEqual(possible_moves(0x487E'4260'4854'7040ull, 0x8781'BD9F'B7AB'8FBFull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x767E'5B1F'4F17'3300ull, 0x8180'A4E0'B0E8'CCFFull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x0066'5317'4717'3300ull, 0xFF98'ACE8'B8E8'CCFFull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x0014'7E00'5E6E'7C00ull, 0x8181'81FF'A191'0004ull), 0x0000'0000'0000'0000ull);
			// 盤が埋まっているが黒の番として調べたとき
			Assert::AreEqual(possible_moves(0x80FE'CEA2'D2FA'C2BFull, 0x7F01'315D'2D05'3D40ull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x009F'0264'5010'7800ull, 0xFF60'FD9B'AFEF'87FFull), 0x0000'0000'0000'0000ull);
			/*
			// 白が置く
			Assert::AreEqual(possible_moves(0x0000'0010'1810'0000ull, 0x0000'0008'0000'0000ull), 0x0000'0020'0028'0000ull);
			Assert::AreEqual(possible_moves(0x0000'0010'3008'0400ull, 0x0000'0008'0830'0000ull), 0x0000'3060'4004'0800ull);
			Assert::AreEqual(possible_moves(0x0000'0012'0418'1C00ull, 0x0000'0008'7822'0000ull), 0x0000'3820'0204'201Eull);
			Assert::AreEqual(possible_moves(0x0000'101E'1C06'0000ull, 0x0000'2A20'2078'0000ull), 0x0018'0501'0201'0200ull);
			Assert::AreEqual(possible_moves(0x0040'3018'0006'0000ull, 0x0000'0A26'3E78'0000ull), 0x8038'4400'0001'0F00ull);
			Assert::AreEqual(possible_moves(0x0046'7E7F'6000'0000ull, 0x0000'0000'1E7E'7E10ull), 0xC7B9'8180'8000'0000ull);
			Assert::AreEqual(possible_moves(0x0046'7E7D'2442'FF00ull, 0x0000'0102'DA3C'0010ull), 0xC7B9'8080'0181'00EFull);
			Assert::AreEqual(possible_moves(0x80C6'CE0D'2E4B'FD08ull, 0x0010'3172'D034'0215ull), 0x4709'0000'0180'00E2ull);
			// 白の番だがどこにも置けないとき
			Assert::AreEqual(possible_moves(0x0000'01B9'3D3D'21FDull, 0x0000'7E46'4242'DE02ull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x0D09'0D0D'0301'0101ull, 0x1236'3232'FC3E'0000ull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0xFF19'0D0D'0101'0101ull, 0x0026'3232'FE3E'0202ull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0xFFB9'B98B'B3B3'8F8Full, 0x0046'4674'4C4C'7050ull), 0x0000'0000'0000'0000ull);
			// 盤が埋まっているが白の番として調べたとき
			Assert::AreEqual(possible_moves(0x80FE'CEA2'D2FA'C2BFull, 0x7F01'315D'2D05'3D40ull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x009F'0264'5010'7800ull, 0xFF60'FD9B'AFEF'87FFull), 0x0000'0000'0000'0000ull);
			*/
			// 白が置く
			Assert::AreEqual(possible_moves(0x0000'0008'0000'0000ull, 0x0000'0010'1810'0000ull), 0x0000'0020'0028'0000ull);
			Assert::AreEqual(possible_moves(0x0000'0008'0830'0000ull, 0x0000'0010'3008'0400ull), 0x0000'3060'4004'0800ull);
			Assert::AreEqual(possible_moves(0x0000'0008'7822'0000ull, 0x0000'0012'0418'1C00ull), 0x0000'3820'0204'201Eull);
			Assert::AreEqual(possible_moves(0x0000'2A20'2078'0000ull, 0x0000'101E'1C06'0000ull), 0x0018'0501'0201'0200ull);
			Assert::AreEqual(possible_moves(0x0000'0A26'3E78'0000ull, 0x0040'3018'0006'0000ull), 0x8038'4400'0001'0F00ull);
			Assert::AreEqual(possible_moves(0x0000'0000'1E7E'7E10ull, 0x0046'7E7F'6000'0000ull), 0xC7B9'8180'8000'0000ull);
			Assert::AreEqual(possible_moves(0x0000'0102'DA3C'0010ull, 0x0046'7E7D'2442'FF00ull), 0xC7B9'8080'0181'00EFull);
			Assert::AreEqual(possible_moves(0x0010'3172'D034'0215ull, 0x80C6'CE0D'2E4B'FD08ull), 0x4709'0000'0180'00E2ull);
			// 白の番だがどこにも置けないとき
			Assert::AreEqual(possible_moves(0x0000'7E46'4242'DE02ull, 0x0000'01B9'3D3D'21FDull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x1236'3232'FC3E'0000ull, 0x0D09'0D0D'0301'0101ull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x0026'3232'FE3E'0202ull, 0xFF19'0D0D'0101'0101ull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x0046'4674'4C4C'7050ull, 0xFFB9'B98B'B3B3'8F8Full), 0x0000'0000'0000'0000ull);
			// 盤が埋まっているが白の番として調べたとき
			Assert::AreEqual(possible_moves(0x7F01'315D'2D05'3D40ull, 0x80FE'CEA2'D2FA'C2BFull), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0xFF60'FD9B'AFEF'87FFull, 0x009F'0264'5010'7800ull), 0x0000'0000'0000'0000ull);
		}

		// 返せる石を調べるテスト
		TEST_METHOD(TurnoverTest)
		{
			// 黒が置く
			Assert::AreEqual(turnovers(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull, position_to_index(5, 3)), 0x0000'0000'1000'0000ull);
			Assert::AreEqual(turnovers(0x0000'003C'0010'0000ull, 0x0000'0800'3C48'0000ull, position_to_index(2, 2)), 0x0000'0000'0C08'0000ull);
			Assert::AreEqual(turnovers(0x0000'0038'0412'0000ull, 0x0000'0A04'3848'0000ull, position_to_index(2, 5)), 0x0000'0004'0000'0000ull);
			Assert::AreEqual(turnovers(0x0000'101E'1402'0000ull, 0x0000'2A20'2878'0000ull, position_to_index(6, 3)), 0x0000'0020'2000'0000ull);
			Assert::AreEqual(turnovers(0x0000'1018'0006'0000ull, 0x0000'2A26'3E78'0000ull, position_to_index(6, 6)), 0x0000'2000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0042'3408'2020'2800ull, 0x0000'0A76'1E5E'1200ull, position_to_index(0, 4)), 0x0000'0006'0204'0000ull);
			Assert::AreEqual(turnovers(0x0046'7C78'6000'0000ull, 0x0000'0206'1E7E'7E10ull, position_to_index(0, 0)), 0x0000'0000'0804'0200ull);
			Assert::AreEqual(turnovers(0x0046'CE0D'2643'F300ull, 0x0090'3172'D83C'0C14ull, position_to_index(7, 4)), 0x0000'0070'4020'0000ull);
			// 黒が1つも返せない位置に置く
			Assert::AreEqual(turnovers(0x487E'4260'4854'7040ull, 0x8781'BD9F'B7AB'8FBFull, position_to_index(5, 7)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x767E'5B1F'4F17'3300ull, 0x8180'A4E0'B0E8'CCFFull, position_to_index(3, 7)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0066'5317'4717'3300ull, 0xFF98'ACE8'B8E8'CCFFull, position_to_index(0, 6)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0014'7E00'5E6E'7C00ull, 0x8181'81FF'A191'0004ull, position_to_index(3, 6)), 0x0000'0000'0000'0000ull);
			// 黒がすでに石で埋まっている位置に置く
			Assert::AreEqual(turnovers(0x487E'4260'4854'7040ull, 0x8781'BD9F'B7AB'8FBFull, position_to_index(0, 0)), 0x0000'0000'0000'023Eull);
			Assert::AreEqual(turnovers(0x0066'5317'4717'3300ull, 0xFF98'ACE8'B8E8'CCFFull, position_to_index(4, 3)), 0x0000'0428'2800'0000ull);
			// 黒が1つも返せない且つすでに石で埋まっている位置に置く
			Assert::AreEqual(turnovers(0x767E'5B1F'4F17'3300ull, 0x8180'A4E0'B0E8'CCFFull, position_to_index(2, 5)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0014'7E00'5E6E'7C00ull, 0x8181'81FF'A191'0004ull, position_to_index(6, 1)), 0x0000'0000'0000'0000ull);

			/*
			// 白が置く
			Assert::AreEqual(turnovers(0x0000'0010'1810'0000ull, 0x0000'0008'0000'0000ull, const_light(), position_to_index(5, 2)), 0x0000'0000'1000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0010'3008'0400ull, 0x0000'0008'0830'0000ull, const_light(), position_to_index(5, 4)), 0x0000'0010'2000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0012'0418'1C00ull, 0x0000'0008'7822'0000ull, const_light(), position_to_index(2, 2)), 0x0000'0000'0018'0000ull);
			Assert::AreEqual(turnovers(0x0000'101E'1C06'0000ull, 0x0000'2A20'2078'0000ull, const_light(), position_to_index(2, 5)), 0x0000'0008'1000'0000ull);
			Assert::AreEqual(turnovers(0x0040'3018'0006'0000ull, 0x0000'0A26'3E78'0000ull, const_light(), position_to_index(7, 7)), 0x0040'2010'0000'0000ull);
			Assert::AreEqual(turnovers(0x0046'7E7F'6000'0000ull, 0x0000'0000'1E7E'7E10ull, const_light(), position_to_index(1, 7)), 0x0006'0A12'2000'0000ull);
			Assert::AreEqual(turnovers(0x0046'7E7D'2442'FF00ull, 0x0000'0102'DA3C'0010ull, const_light(), position_to_index(7, 5)), 0x0000'7E40'2000'0000ull);
			Assert::AreEqual(turnovers(0x80C6'CE0D'2E4B'FD08ull, 0x0010'3172'D034'0215ull, const_light(), position_to_index(0, 3)), 0x0000'0001'0E01'0100ull);
			// 白が1つも返せない位置に置く
			Assert::AreEqual(turnovers(0x0000'01B9'3D3D'21FDull, 0x0000'7E46'4242'DE02ull, const_light(), position_to_index(0, 7)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0D09'0D0D'0301'0101ull, 0x1236'3232'FC3E'0000ull, const_light(), position_to_index(6, 1)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0xFF19'0D0D'0101'0101ull, 0x0026'3232'FE3E'0202ull, const_light(), position_to_index(2, 0)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0xFFB9'B98B'B3B3'8F8Full, 0x0046'4674'4C4C'7050ull, const_light(), position_to_index(5, 0)), 0x0000'0000'0000'0000ull);
			// 白がすでに石で埋まっている位置に置く
			Assert::AreEqual(turnovers(0x0000'01B9'3D3D'21FDull, 0x0000'7E46'4242'DE02ull, const_light(), position_to_index(4, 3)), 0x0000'0038'2C38'0000ull);
			Assert::AreEqual(turnovers(0xFF19'0D0D'0101'0101ull, 0x0026'3232'FE3E'0202ull, const_light(), position_to_index(3, 7)), 0x0018'0808'0000'0000ull);
			// 白が1つも返せない且つすでに石で埋まっている位置に置く
			Assert::AreEqual(turnovers(0x0D09'0D0D'0301'0101ull, 0x1236'3232'FC3E'0000ull, const_light(), position_to_index(5, 2)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0xFFB9'B98B'B3B3'8F8Full, 0x0046'4674'4C4C'7050ull, const_light(), position_to_index(7, 0)), 0x0000'0000'0000'0000ull);
			*/

			// 白が置く
			Assert::AreEqual(turnovers(0x0000'0008'0000'0000ull, 0x0000'0010'1810'0000ull, position_to_index(5, 2)), 0x0000'0000'1000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0008'0830'0000ull, 0x0000'0010'3008'0400ull, position_to_index(5, 4)), 0x0000'0010'2000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0008'7822'0000ull, 0x0000'0012'0418'1C00ull, position_to_index(2, 2)), 0x0000'0000'0018'0000ull);
			Assert::AreEqual(turnovers(0x0000'2A20'2078'0000ull, 0x0000'101E'1C06'0000ull, position_to_index(2, 5)), 0x0000'0008'1000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0A26'3E78'0000ull, 0x0040'3018'0006'0000ull, position_to_index(7, 7)), 0x0040'2010'0000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0000'1E7E'7E10ull, 0x0046'7E7F'6000'0000ull, position_to_index(1, 7)), 0x0006'0A12'2000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0102'DA3C'0010ull, 0x0046'7E7D'2442'FF00ull, position_to_index(7, 5)), 0x0000'7E40'2000'0000ull);
			Assert::AreEqual(turnovers(0x0010'3172'D034'0215ull, 0x80C6'CE0D'2E4B'FD08ull, position_to_index(0, 3)), 0x0000'0001'0E01'0100ull);
			// 白が1つも返せない位置に置く
			Assert::AreEqual(turnovers(0x0000'7E46'4242'DE02ull, 0x0000'01B9'3D3D'21FDull, position_to_index(0, 7)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x1236'3232'FC3E'0000ull, 0x0D09'0D0D'0301'0101ull, position_to_index(6, 1)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0026'3232'FE3E'0202ull, 0xFF19'0D0D'0101'0101ull, position_to_index(2, 0)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0046'4674'4C4C'7050ull, 0xFFB9'B98B'B3B3'8F8Full, position_to_index(5, 0)), 0x0000'0000'0000'0000ull);
			// 白がすでに石で埋まっている位置に置く
			Assert::AreEqual(turnovers(0x0000'7E46'4242'DE02ull, 0x0000'01B9'3D3D'21FDull, position_to_index(4, 3)), 0x0000'0038'2C38'0000ull);
			Assert::AreEqual(turnovers(0x0026'3232'FE3E'0202ull, 0xFF19'0D0D'0101'0101ull, position_to_index(3, 7)), 0x0018'0808'0000'0000ull);
			// 白が1つも返せない且つすでに石で埋まっている位置に置く
			Assert::AreEqual(turnovers(0x1236'3232'FC3E'0000ull, 0x0D09'0D0D'0301'0101ull, position_to_index(5, 2)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0046'4674'4C4C'7050ull, 0xFFB9'B98B'B3B3'8F8Full, position_to_index(7, 0)), 0x0000'0000'0000'0000ull);

		}

		
		// 盤更新のテスト
		TEST_METHOD(BoardUpdateTest)
		{
			unsigned long long self;
			unsigned long long opponent;
			unsigned long long turns;
			// 
			turns = place(0x00F8'C687'E7AB'C0E4ull, 0xFE04'3878'1854'3A18ull, position_to_index(0, 0), &self, &opponent);
			Assert::AreEqual(self, 0x00F8'E697'EFAF'C2E5ull);
			Assert::AreEqual(opponent, 0xFE04'1868'1050'3818ull);
			Assert::AreEqual(turns, 0x0000'2010'0804'0200ull);
			// 
			turns = place(0x4000'0810'2C44'6073ull, 0xBCFD'F7EF'D3BB'9F8Cull, position_to_index(0, 7), &self, &opponent);
			Assert::AreEqual(self, 0x4101'0911'2D45'6173ull);
			Assert::AreEqual(opponent, 0xBCFC'F6EE'D2BA'9E8Cull);
			Assert::AreEqual(turns, 0x0001'0101'0101'0100ull);
		}
		
		// 完全探索のテスト
		TEST_METHOD(FullSearchTest)
		{
			Assert::AreEqual(full_search(0x4000'0810'2C44'6073ull, 0xBCFD'F7EF'D3BB'9F8Cull, 0), position_to_index(0, 7));

			Assert::AreEqual(full_search(0xFE04'3878'1850'3818ull, 0x00F8'C687'E7AF'C0E4ull, 0), position_to_index(1, 1));

			Assert::AreEqual(full_search(0x8080'908F'B388'9C80ull, 0x7E7C'6F70'4C77'637Full, 0), position_to_index(0, 7));
		}
		
	};
}
