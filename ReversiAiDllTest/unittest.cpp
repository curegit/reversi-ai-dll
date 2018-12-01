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
		TEST_METHOD(PossibleMoveTestMethod)
		{
			// �����u��
			Assert::AreEqual(possible_moves(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull, const_dark()), 0x0000'0804'2010'0000ull);
			// �����u��
			Assert::AreEqual(possible_moves(0x0000'0010'1810'0000ull, 0x0000'0008'0000'0000ull, const_light()), 0x0000'0020'0028'0000ull);
		}

		// �Ԃ���΂𒲂ׂ�e�X�g
		TEST_METHOD(TurnoverTest)
		{
			// �����u��
			Assert::AreEqual(turnovers(0x0000'0010'0800'0000ull, 0x0000'0008'1000'0000ull, const_dark(), position_to_index(5, 3)), 0x0000'0000'1000'0000ull);
			// �����u��
			Assert::AreEqual(turnovers(0x0000'0010'1810'0000ull, 0x0000'0008'0000'0000ull, const_light(), position_to_index(5, 2)), 0x0000'0000'1000'0000ull);
		}

		// �l�K�}�b�N�X�@�̃e�X�g
		TEST_METHOD(NegaMaxTestMethod)
		{

		}
	};
}
