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
