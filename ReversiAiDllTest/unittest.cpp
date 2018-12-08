// DLL�A�v���P�[�V�����̒P�̃e�X�g���L�q���܂�

// �v���R���p�C���ς݃w�b�_�[
#include "stdafx.h"

// �P�̃e�X�g���W���[��
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReversiAiDllTest
{
	// �e�X�g���\�b�h���`����N���X
	TEST_CLASS(UnitTest)
	{
	public:
		// �ʒu���W�ƃr�b�g�ԍ��̑��ݕϊ��e�X�g
		TEST_METHOD(PositionConversionTest)
		{
			// �ʒu���W����r�b�g�ԍ��ւ̕ϊ��e�X�g
			Assert::AreEqual(position_to_index(0, 0), 0);
			Assert::AreEqual(position_to_index(1, 0), 1);
			Assert::AreEqual(position_to_index(7, 0), 7);
			Assert::AreEqual(position_to_index(0, 1), 8);
			Assert::AreEqual(position_to_index(4, 2), 20);
			Assert::AreEqual(position_to_index(5, 3), 29);
			Assert::AreEqual(position_to_index(6, 5), 46);
			Assert::AreEqual(position_to_index(7, 7), 63);
			// �r�b�g�ԍ�����i���W�����o���e�X�g
			Assert::AreEqual(index_to_position_i(0), 0);
			Assert::AreEqual(index_to_position_i(1), 1);
			Assert::AreEqual(index_to_position_i(7), 7);
			Assert::AreEqual(index_to_position_i(8), 0);
			Assert::AreEqual(index_to_position_i(21), 5);
			Assert::AreEqual(index_to_position_i(27), 3);
			Assert::AreEqual(index_to_position_i(44), 4);
			Assert::AreEqual(index_to_position_i(63), 7);
			// �r�b�g�ԍ�����j���W�����o���e�X�g
			Assert::AreEqual(index_to_position_j(0), 0);
			Assert::AreEqual(index_to_position_j(7), 0);
			Assert::AreEqual(index_to_position_j(8), 1);
			Assert::AreEqual(index_to_position_j(16), 2);
			Assert::AreEqual(index_to_position_j(30), 3);
			Assert::AreEqual(index_to_position_j(39), 4);
			Assert::AreEqual(index_to_position_j(55), 6);
			Assert::AreEqual(index_to_position_j(63), 7);
		}

		// ����\�Ȏ�𒲂ׂ�e�X�g
		TEST_METHOD(PossibleMoveTest)
		{
			// �����u��
			Assert::AreEqual(possible_moves(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull, const_dark()), 0x0000'0804'2010'0000ull);
			Assert::AreEqual(possible_moves(0x0000'003C'0010'0000ull, 0x0000'0800'3C48'0000ull, const_dark()), 0x001C'0040'0026'8C00ull);
			Assert::AreEqual(possible_moves(0x0000'0038'0412'0000ull, 0x0000'0A04'3848'0000ull, const_dark()), 0x000D'0442'4024'9C00ull);
			Assert::AreEqual(possible_moves(0x0000'101E'1402'0000ull, 0x0000'2A20'2878'0000ull, const_dark()), 0x005F'4440'4004'FC00ull);
			Assert::AreEqual(possible_moves(0x0000'1018'0006'0000ull, 0x0000'2A26'3E78'0000ull, const_dark()), 0x004E'4441'4080'D800ull);
			Assert::AreEqual(possible_moves(0x0042'3408'2020'2800ull, 0x0000'0A76'1E5E'1200ull, const_dark()), 0x000D'8181'C181'851Bull);
			Assert::AreEqual(possible_moves(0x0046'7C78'6000'0000ull, 0x0000'0206'1E7E'7E10ull, const_dark()), 0x0000'0101'0101'81EFull);
			Assert::AreEqual(possible_moves(0x0046'CE0D'2643'F300ull, 0x0090'3172'D83C'0C14ull, const_dark()), 0xB021'0080'0100'000Aull);
			// ���̔Ԃ����ǂ��ɂ��u���Ȃ��Ƃ�
			Assert::AreEqual(possible_moves(0x487E'4260'4854'7040ull, 0x8781'BD9F'B7AB'8FBFull, const_dark()), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x767E'5B1F'4F17'3300ull, 0x8180'A4E0'B0E8'CCFFull, const_dark()), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x0066'5317'4717'3300ull, 0xFF98'ACE8'B8E8'CCFFull, const_dark()), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x0014'7E00'5E6E'7C00ull, 0x8181'81FF'A191'0004ull, const_dark()), 0x0000'0000'0000'0000ull);
			// �Ղ����܂��Ă��邪���̔ԂƂ��Ē��ׂ��Ƃ�
			Assert::AreEqual(possible_moves(0x80FE'CEA2'D2FA'C2BFull, 0x7F01'315D'2D05'3D40ull, const_dark()), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x009F'0264'5010'7800ull, 0xFF60'FD9B'AFEF'87FFull, const_dark()), 0x0000'0000'0000'0000ull);
			// �����u��
			Assert::AreEqual(possible_moves(0x0000'0010'1810'0000ull, 0x0000'0008'0000'0000ull, const_light()), 0x0000'0020'0028'0000ull);
			Assert::AreEqual(possible_moves(0x0000'0010'3008'0400ull, 0x0000'0008'0830'0000ull, const_light()), 0x0000'3060'4004'0800ull);
			Assert::AreEqual(possible_moves(0x0000'0012'0418'1C00ull, 0x0000'0008'7822'0000ull, const_light()), 0x0000'3820'0204'201Eull);
			Assert::AreEqual(possible_moves(0x0000'101E'1C06'0000ull, 0x0000'2A20'2078'0000ull, const_light()), 0x0018'0501'0201'0200ull);
			Assert::AreEqual(possible_moves(0x0040'3018'0006'0000ull, 0x0000'0A26'3E78'0000ull, const_light()), 0x8038'4400'0001'0F00ull);
			Assert::AreEqual(possible_moves(0x0046'7E7F'6000'0000ull, 0x0000'0000'1E7E'7E10ull, const_light()), 0xC7B9'8180'8000'0000ull);
			Assert::AreEqual(possible_moves(0x0046'7E7D'2442'FF00ull, 0x0000'0102'DA3C'0010ull, const_light()), 0xC7B9'8080'0181'00EFull);
			Assert::AreEqual(possible_moves(0x80C6'CE0D'2E4B'FD08ull, 0x0010'3172'D034'0215ull, const_light()), 0x4709'0000'0180'00E2ull);
			// ���̔Ԃ����ǂ��ɂ��u���Ȃ��Ƃ�
			Assert::AreEqual(possible_moves(0x0000'01B9'3D3D'21FDull, 0x0000'7E46'4242'DE02ull, const_light()), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x0D09'0D0D'0301'0101ull, 0x1236'3232'FC3E'0000ull, const_light()), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0xFF19'0D0D'0101'0101ull, 0x0026'3232'FE3E'0202ull, const_light()), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0xFFB9'B98B'B3B3'8F8Full, 0x0046'4674'4C4C'7050ull, const_light()), 0x0000'0000'0000'0000ull);
			// �Ղ����܂��Ă��邪���̔ԂƂ��Ē��ׂ��Ƃ�
			Assert::AreEqual(possible_moves(0x80FE'CEA2'D2FA'C2BFull, 0x7F01'315D'2D05'3D40ull, const_light()), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(possible_moves(0x009F'0264'5010'7800ull, 0xFF60'FD9B'AFEF'87FFull, const_light()), 0x0000'0000'0000'0000ull);
		}

		// �Ԃ���΂𒲂ׂ�e�X�g
		TEST_METHOD(TurnoverTest)
		{
			// �����u��
			Assert::AreEqual(turnovers(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull, const_dark(), position_to_index(5, 3)), 0x0000'0000'1000'0000ull);
			Assert::AreEqual(turnovers(0x0000'003C'0010'0000ull, 0x0000'0800'3C48'0000ull, const_dark(), position_to_index(2, 2)), 0x0000'0000'0C08'0000ull);
			Assert::AreEqual(turnovers(0x0000'0038'0412'0000ull, 0x0000'0A04'3848'0000ull, const_dark(), position_to_index(2, 5)), 0x0000'0004'0000'0000ull);
			Assert::AreEqual(turnovers(0x0000'101E'1402'0000ull, 0x0000'2A20'2878'0000ull, const_dark(), position_to_index(6, 3)), 0x0000'0020'2000'0000ull);
			Assert::AreEqual(turnovers(0x0000'1018'0006'0000ull, 0x0000'2A26'3E78'0000ull, const_dark(), position_to_index(6, 6)), 0x0000'2000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0042'3408'2020'2800ull, 0x0000'0A76'1E5E'1200ull, const_dark(), position_to_index(0, 4)), 0x0000'0006'0204'0000ull);
			Assert::AreEqual(turnovers(0x0046'7C78'6000'0000ull, 0x0000'0206'1E7E'7E10ull, const_dark(), position_to_index(0, 0)), 0x0000'0000'0804'0200ull);
			Assert::AreEqual(turnovers(0x0046'CE0D'2643'F300ull, 0x0090'3172'D83C'0C14ull, const_dark(), position_to_index(7, 4)), 0x0000'0070'4020'0000ull);
			// ����1���Ԃ��Ȃ��ʒu�ɒu��
			Assert::AreEqual(turnovers(0x487E'4260'4854'7040ull, 0x8781'BD9F'B7AB'8FBFull, const_dark(), position_to_index(5, 7)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x767E'5B1F'4F17'3300ull, 0x8180'A4E0'B0E8'CCFFull, const_dark(), position_to_index(3, 7)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0066'5317'4717'3300ull, 0xFF98'ACE8'B8E8'CCFFull, const_dark(), position_to_index(0, 6)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0014'7E00'5E6E'7C00ull, 0x8181'81FF'A191'0004ull, const_dark(), position_to_index(3, 6)), 0x0000'0000'0000'0000ull);
			// �������łɐ΂Ŗ��܂��Ă���ʒu�ɒu��
			Assert::AreEqual(turnovers(0x487E'4260'4854'7040ull, 0x8781'BD9F'B7AB'8FBFull, const_dark(), position_to_index(0, 0)), 0x0000'0000'0000'023Eull);
			Assert::AreEqual(turnovers(0x0066'5317'4717'3300ull, 0xFF98'ACE8'B8E8'CCFFull, const_dark(), position_to_index(4, 3)), 0x0000'0428'2800'0000ull);
			// ����1���Ԃ��Ȃ������łɐ΂Ŗ��܂��Ă���ʒu�ɒu��
			Assert::AreEqual(turnovers(0x767E'5B1F'4F17'3300ull, 0x8180'A4E0'B0E8'CCFFull, const_dark(), position_to_index(2, 5)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0014'7E00'5E6E'7C00ull, 0x8181'81FF'A191'0004ull, const_dark(), position_to_index(6, 1)), 0x0000'0000'0000'0000ull);
			// �����u��
			Assert::AreEqual(turnovers(0x0000'0010'1810'0000ull, 0x0000'0008'0000'0000ull, const_light(), position_to_index(5, 2)), 0x0000'0000'1000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0010'3008'0400ull, 0x0000'0008'0830'0000ull, const_light(), position_to_index(5, 4)), 0x0000'0010'2000'0000ull);
			Assert::AreEqual(turnovers(0x0000'0012'0418'1C00ull, 0x0000'0008'7822'0000ull, const_light(), position_to_index(2, 2)), 0x0000'0000'0018'0000ull);
			Assert::AreEqual(turnovers(0x0000'101E'1C06'0000ull, 0x0000'2A20'2078'0000ull, const_light(), position_to_index(2, 5)), 0x0000'0008'1000'0000ull);
			Assert::AreEqual(turnovers(0x0040'3018'0006'0000ull, 0x0000'0A26'3E78'0000ull, const_light(), position_to_index(7, 7)), 0x0040'2010'0000'0000ull);
			Assert::AreEqual(turnovers(0x0046'7E7F'6000'0000ull, 0x0000'0000'1E7E'7E10ull, const_light(), position_to_index(1, 7)), 0x0006'0A12'2000'0000ull);
			Assert::AreEqual(turnovers(0x0046'7E7D'2442'FF00ull, 0x0000'0102'DA3C'0010ull, const_light(), position_to_index(7, 5)), 0x0000'7E40'2000'0000ull);
			Assert::AreEqual(turnovers(0x80C6'CE0D'2E4B'FD08ull, 0x0010'3172'D034'0215ull, const_light(), position_to_index(0, 3)), 0x0000'0001'0E01'0100ull);
			// ����1���Ԃ��Ȃ��ʒu�ɒu��
			Assert::AreEqual(turnovers(0x0000'01B9'3D3D'21FDull, 0x0000'7E46'4242'DE02ull, const_light(), position_to_index(0, 7)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0x0D09'0D0D'0301'0101ull, 0x1236'3232'FC3E'0000ull, const_light(), position_to_index(6, 1)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0xFF19'0D0D'0101'0101ull, 0x0026'3232'FE3E'0202ull, const_light(), position_to_index(2, 0)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0xFFB9'B98B'B3B3'8F8Full, 0x0046'4674'4C4C'7050ull, const_light(), position_to_index(5, 0)), 0x0000'0000'0000'0000ull);
			// �������łɐ΂Ŗ��܂��Ă���ʒu�ɒu��
			Assert::AreEqual(turnovers(0x0000'01B9'3D3D'21FDull, 0x0000'7E46'4242'DE02ull, const_light(), position_to_index(4, 3)), 0x0000'0038'2C38'0000ull);
			Assert::AreEqual(turnovers(0xFF19'0D0D'0101'0101ull, 0x0026'3232'FE3E'0202ull, const_light(), position_to_index(3, 7)), 0x0018'0808'0000'0000ull);
			// ����1���Ԃ��Ȃ������łɐ΂Ŗ��܂��Ă���ʒu�ɒu��
			Assert::AreEqual(turnovers(0x0D09'0D0D'0301'0101ull, 0x1236'3232'FC3E'0000ull, const_light(), position_to_index(5, 2)), 0x0000'0000'0000'0000ull);
			Assert::AreEqual(turnovers(0xFFB9'B98B'B3B3'8F8Full, 0x0046'4674'4C4C'7050ull, const_light(), position_to_index(7, 0)), 0x0000'0000'0000'0000ull);
		}

		// �l�K�}�b�N�X�@�̃e�X�g
		TEST_METHOD(NegaMaxTest)
		{

		}
	};
}
