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
			Assert::AreEqual(0, position_to_index(0, 0));
			Assert::AreEqual(1, position_to_index(1, 0));
			Assert::AreEqual(7, position_to_index(7, 0));
			Assert::AreEqual(8, position_to_index(0, 1));
			Assert::AreEqual(20, position_to_index(4, 2));
			Assert::AreEqual(29, position_to_index(5, 3));
			Assert::AreEqual(46, position_to_index(6, 5));
			Assert::AreEqual(63, position_to_index(7, 7));
			// ビット番号からi座標を取り出すテスト
			Assert::AreEqual(0, index_to_position_i(0));
			Assert::AreEqual(1, index_to_position_i(1));
			Assert::AreEqual(7, index_to_position_i(7));
			Assert::AreEqual(0, index_to_position_i(8));
			Assert::AreEqual(5, index_to_position_i(21));
			Assert::AreEqual(3, index_to_position_i(27));
			Assert::AreEqual(4, index_to_position_i(44));
			Assert::AreEqual(7, index_to_position_i(63));
			// ビット番号からj座標を取り出すテスト
			Assert::AreEqual(0, index_to_position_j(0));
			Assert::AreEqual(0, index_to_position_j(7));
			Assert::AreEqual(1, index_to_position_j(8));
			Assert::AreEqual(2, index_to_position_j(16));
			Assert::AreEqual(3, index_to_position_j(30));
			Assert::AreEqual(4, index_to_position_j(39));
			Assert::AreEqual(6, index_to_position_j(55));
			Assert::AreEqual(7, index_to_position_j(63));
		}

		// 立っているビットの数を数えるテスト
		TEST_METHOD(BitCountTest)
		{
			Assert::AreEqual(0, count_bits(0x0000'0000'0000'0000ull));
			Assert::AreEqual(1, count_bits(0x0000'0000'0000'0001ull));
			Assert::AreEqual(1, count_bits(0x1000'0000'0000'0000ull));
			Assert::AreEqual(14, count_bits(0x0A00'C0D0'1E00'0430ull));
			Assert::AreEqual(15, count_bits(0x3004'0500'00BD'7008ull));
			Assert::AreEqual(32, count_bits(0x0123'4567'89AB'CDEFull));
		}

		// 着手可能な手を調べるテスト
		TEST_METHOD(PossibleMoveTest)
		{
			// 普通に置けるとき
			Assert::AreEqual(0x0000'0804'2010'0000ull, possible_moves(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull));
			Assert::AreEqual(0x001C'0040'0026'8C00ull, possible_moves(0x0000'003C'0010'0000ull, 0x0000'0800'3C48'0000ull));
			Assert::AreEqual(0x000D'0442'4024'9C00ull, possible_moves(0x0000'0038'0412'0000ull, 0x0000'0A04'3848'0000ull));
			Assert::AreEqual(0x005F'4440'4004'FC00ull, possible_moves(0x0000'101E'1402'0000ull, 0x0000'2A20'2878'0000ull));
			Assert::AreEqual(0x004E'4441'4080'D800ull, possible_moves(0x0000'1018'0006'0000ull, 0x0000'2A26'3E78'0000ull));
			Assert::AreEqual(0x000D'8181'C181'851Bull, possible_moves(0x0042'3408'2020'2800ull, 0x0000'0A76'1E5E'1200ull));
			Assert::AreEqual(0x0000'0101'0101'81EFull, possible_moves(0x0046'7C78'6000'0000ull, 0x0000'0206'1E7E'7E10ull));
			Assert::AreEqual(0xB021'0080'0100'000Aull, possible_moves(0x0046'CE0D'2643'F300ull, 0x0090'3172'D83C'0C14ull));    
			Assert::AreEqual(0x0000'0020'0028'0000ull, possible_moves(0x0000'0008'0000'0000ull, 0x0000'0010'1810'0000ull));
			Assert::AreEqual(0x0000'3060'4004'0800ull, possible_moves(0x0000'0008'0830'0000ull, 0x0000'0010'3008'0400ull));
			Assert::AreEqual(0x0000'3820'0204'201Eull, possible_moves(0x0000'0008'7822'0000ull, 0x0000'0012'0418'1C00ull));
			Assert::AreEqual(0x0018'0501'0201'0200ull, possible_moves(0x0000'2A20'2078'0000ull, 0x0000'101E'1C06'0000ull));
			Assert::AreEqual(0x8038'4400'0001'0F00ull, possible_moves(0x0000'0A26'3E78'0000ull, 0x0040'3018'0006'0000ull));
			Assert::AreEqual(0xC7B9'8180'8000'0000ull, possible_moves(0x0000'0000'1E7E'7E10ull, 0x0046'7E7F'6000'0000ull));
			Assert::AreEqual(0xC7B9'8080'0181'00EFull, possible_moves(0x0000'0102'DA3C'0010ull, 0x0046'7E7D'2442'FF00ull));
			Assert::AreEqual(0x4709'0000'0180'00E2ull, possible_moves(0x0010'3172'D034'0215ull, 0x80C6'CE0D'2E4B'FD08ull));
			// パスが発生するとき（どこにも置けないとき）
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x0000'7E46'4242'DE02ull, 0x0000'01B9'3D3D'21FDull));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x1236'3232'FC3E'0000ull, 0x0D09'0D0D'0301'0101ull));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x0026'3232'FE3E'0202ull, 0xFF19'0D0D'0101'0101ull));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x0046'4674'4C4C'7050ull, 0xFFB9'B98B'B3B3'8F8Full));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x487E'4260'4854'7040ull, 0x8781'BD9F'B7AB'8FBFull));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x767E'5B1F'4F17'3300ull, 0x8180'A4E0'B0E8'CCFFull));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x0066'5317'4717'3300ull, 0xFF98'ACE8'B8E8'CCFFull));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x0014'7E00'5E6E'7C00ull, 0x8181'81FF'A191'0004ull));
			// 盤が埋まっているとき
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x80FE'CEA2'D2FA'C2BFull, 0x7F01'315D'2D05'3D40ull));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x009F'0264'5010'7800ull, 0xFF60'FD9B'AFEF'87FFull));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0x7F01'315D'2D05'3D40ull, 0x80FE'CEA2'D2FA'C2BFull));
			Assert::AreEqual(0x0000'0000'0000'0000ull, possible_moves(0xFF60'FD9B'AFEF'87FFull, 0x009F'0264'5010'7800ull));
		}

		// 返せる石を調べるテスト
		TEST_METHOD(TurnoverTest)
		{
			// 普通に置くとき
			Assert::AreEqual(0x0000'0000'1000'0000ull, turnovers(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull, position_to_index(5, 3)));
			Assert::AreEqual(0x0000'0000'0C08'0000ull, turnovers(0x0000'003C'0010'0000ull, 0x0000'0800'3C48'0000ull, position_to_index(2, 2)));
			Assert::AreEqual(0x0000'0004'0000'0000ull, turnovers(0x0000'0038'0412'0000ull, 0x0000'0A04'3848'0000ull, position_to_index(2, 5)));
			Assert::AreEqual(0x0000'0020'2000'0000ull, turnovers(0x0000'101E'1402'0000ull, 0x0000'2A20'2878'0000ull, position_to_index(6, 3)));
			Assert::AreEqual(0x0000'2000'0000'0000ull, turnovers(0x0000'1018'0006'0000ull, 0x0000'2A26'3E78'0000ull, position_to_index(6, 6)));
			Assert::AreEqual(0x0000'0006'0204'0000ull, turnovers(0x0042'3408'2020'2800ull, 0x0000'0A76'1E5E'1200ull, position_to_index(0, 4)));
			Assert::AreEqual(0x0000'0000'0804'0200ull, turnovers(0x0046'7C78'6000'0000ull, 0x0000'0206'1E7E'7E10ull, position_to_index(0, 0)));
			Assert::AreEqual(0x0000'0070'4020'0000ull, turnovers(0x0046'CE0D'2643'F300ull, 0x0090'3172'D83C'0C14ull, position_to_index(7, 4)));
			Assert::AreEqual(0x0000'0000'1000'0000ull, turnovers(0x0000'0008'0000'0000ull, 0x0000'0010'1810'0000ull, position_to_index(5, 2)));
			Assert::AreEqual(0x0000'0010'2000'0000ull, turnovers(0x0000'0008'0830'0000ull, 0x0000'0010'3008'0400ull, position_to_index(5, 4)));
			Assert::AreEqual(0x0000'0000'0018'0000ull, turnovers(0x0000'0008'7822'0000ull, 0x0000'0012'0418'1C00ull, position_to_index(2, 2)));
			Assert::AreEqual(0x0000'0008'1000'0000ull, turnovers(0x0000'2A20'2078'0000ull, 0x0000'101E'1C06'0000ull, position_to_index(2, 5)));
			Assert::AreEqual(0x0040'2010'0000'0000ull, turnovers(0x0000'0A26'3E78'0000ull, 0x0040'3018'0006'0000ull, position_to_index(7, 7)));
			Assert::AreEqual(0x0006'0A12'2000'0000ull, turnovers(0x0000'0000'1E7E'7E10ull, 0x0046'7E7F'6000'0000ull, position_to_index(1, 7)));
			Assert::AreEqual(0x0000'7E40'2000'0000ull, turnovers(0x0000'0102'DA3C'0010ull, 0x0046'7E7D'2442'FF00ull, position_to_index(7, 5)));
			Assert::AreEqual(0x0000'0001'0E01'0100ull, turnovers(0x0010'3172'D034'0215ull, 0x80C6'CE0D'2E4B'FD08ull, position_to_index(0, 3)));
			// 1つも返せない位置に置くとき（本来は置けない位置に置く）
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x487E'4260'4854'7040ull, 0x8781'BD9F'B7AB'8FBFull, position_to_index(5, 7)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x767E'5B1F'4F17'3300ull, 0x8180'A4E0'B0E8'CCFFull, position_to_index(3, 7)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x0066'5317'4717'3300ull, 0xFF98'ACE8'B8E8'CCFFull, position_to_index(0, 6)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x0014'7E00'5E6E'7C00ull, 0x8181'81FF'A191'0004ull, position_to_index(3, 6)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x0000'7E46'4242'DE02ull, 0x0000'01B9'3D3D'21FDull, position_to_index(0, 7)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x1236'3232'FC3E'0000ull, 0x0D09'0D0D'0301'0101ull, position_to_index(6, 1)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x0026'3232'FE3E'0202ull, 0xFF19'0D0D'0101'0101ull, position_to_index(2, 0)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x0046'4674'4C4C'7050ull, 0xFFB9'B98B'B3B3'8F8Full, position_to_index(5, 0)));
			// すでに石で埋まっている位置に置くとき（本来は置けない位置に置く）
			Assert::AreEqual(0x0000'0000'0000'023Eull, turnovers(0x487E'4260'4854'7040ull, 0x8781'BD9F'B7AB'8FBFull, position_to_index(0, 0)));
			Assert::AreEqual(0x0000'0428'2800'0000ull, turnovers(0x0066'5317'4717'3300ull, 0xFF98'ACE8'B8E8'CCFFull, position_to_index(4, 3)));
			Assert::AreEqual(0x0000'0038'2C38'0000ull, turnovers(0x0000'7E46'4242'DE02ull, 0x0000'01B9'3D3D'21FDull, position_to_index(4, 3)));
			Assert::AreEqual(0x0018'0808'0000'0000ull, turnovers(0x0026'3232'FE3E'0202ull, 0xFF19'0D0D'0101'0101ull, position_to_index(3, 7)));
			// 1つも返せない且つすでに石で埋まっている位置に置く（本来は置けない位置に置く）
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x767E'5B1F'4F17'3300ull, 0x8180'A4E0'B0E8'CCFFull, position_to_index(2, 5)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x0014'7E00'5E6E'7C00ull, 0x8181'81FF'A191'0004ull, position_to_index(6, 1)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x1236'3232'FC3E'0000ull, 0x0D09'0D0D'0301'0101ull, position_to_index(5, 2)));
			Assert::AreEqual(0x0000'0000'0000'0000ull, turnovers(0x0046'4674'4C4C'7050ull, 0xFFB9'B98B'B3B3'8F8Full, position_to_index(7, 0)));
		}

		// 盤更新のテスト
		TEST_METHOD(BoardUpdateTest)
		{
			unsigned long long self;
			unsigned long long opponent;
			unsigned long long turns;
			turns = place(0x00F8'C687'E7AB'C0E4ull, 0xFE04'3878'1854'3A18ull, position_to_index(0, 0), &self, &opponent);
			Assert::AreEqual(0x00F8'E697'EFAF'C2E5ull, self);
			Assert::AreEqual(0xFE04'1868'1050'3818ull, opponent);
			Assert::AreEqual(0x0000'2010'0804'0200ull, turns);
			turns = place(0x4000'0810'2C44'6073ull, 0xBCFD'F7EF'D3BB'9F8Cull, position_to_index(0, 7), &self, &opponent);
			Assert::AreEqual(0x4101'0911'2D45'6173ull, self);
			Assert::AreEqual(0xBCFC'F6EE'D2BA'9E8Cull, opponent);
			Assert::AreEqual(0x0001'0101'0101'0100ull, turns);
		}

		// 静的評価用の重みのテスト
		TEST_METHOD(WeightTest)
		{
			Assert::AreEqual(0, sum_of_weights(0x0000'0000'0000'0000ull));
			Assert::AreEqual(20000, sum_of_weights(0x8000'0000'0000'0001ull));
			Assert::AreEqual(100, sum_of_weights(0x0000'0010'0800'0000ull));
		}

		// 開放度計算のテスト
		TEST_METHOD(OpennessTest)
		{
			Assert::AreEqual(2, openness(0x0000'0008'0828'0000ull, 0x0000'0010'3010'1000ull, 0x0000'0000'0010'0000ull));
			Assert::AreEqual(5, openness(0x0000'0008'0828'0000ull, 0x0000'0010'3010'1000ull, 0x0000'0000'3000'0000ull));
		}

		// 完全探索のテスト
		TEST_METHOD(FullSearchTest)
		{
			Assert::AreEqual(position_to_index(0, 7), full_search(0x4000'0810'2C44'6073ull, 0xBCFD'F7EF'D3BB'9F8Cull));
			Assert::AreEqual(position_to_index(1, 1), full_search(0xFE04'3878'1850'3818ull, 0x00F8'C687'E7AF'C0E4ull));
			Assert::AreEqual(position_to_index(0, 7), full_search(0x8080'908F'B388'9C80ull, 0x7E7C'6F70'4C77'637Full));
			Assert::AreEqual(position_to_index(1, 6), full_search(0x0010'6341'6D29'0721ull, 0xBCAC'9CBE'92D6'381Eull));
		}

		// 部分探索のテスト
		TEST_METHOD(HeuristicSearchTest)
		{
			Assert::AreEqual(position_to_index(4, 0), heuristic_search(0x0000'0000'0010'0804ull, 0x0000'1038'7E6C'3020ull, 9));
		}
	};
}
