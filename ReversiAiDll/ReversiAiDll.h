#pragma once

// �O���ɃG�N�X�|�[�g�����֐����`���܂�
extern "C"
{
	// ���W�ʒu����r�b�g�ԍ���Ԃ�
	__declspec(dllexport) int position_to_index(int i, int j);

	// �r�b�g�ԍ�����i���W��Ԃ�
	__declspec(dllexport) int index_to_position_i(int n);

	// �r�b�g�ԍ�����j���W��Ԃ�
	__declspec(dllexport) int index_to_position_j(int n);

	// �����Ă���r�b�g�̐���Ԃ�
	__declspec(dllexport) int count_bits(unsigned long long n);

	// self�v���C���[�̐΂̐�����opponent�v���C���[�̐΂̐������������̂�Ԃ�
	__declspec(dllexport) int balance(unsigned long long self, unsigned long long opponent);

	// self�v���C���[������\�Ȏ�̃r�b�g�{�[�h�\����Ԃ�
	__declspec(dllexport) unsigned long long possible_moves(unsigned long long self, unsigned long long opponent);

	// self�v���C���[��index�n�_�ɑł����Ƃ��ɕԂ���΂̃r�b�g�{�[�h�\����Ԃ�
	__declspec(dllexport) unsigned long long turnovers(unsigned long long self, unsigned long long opponent, int index);

	// self�v���C���[��index�n�_�ɑł����Ƃ��ɓ�����Ղ��ԐڎQ�Ƃɂ���đ�����A�Ԃ����΂̃r�b�g�{�[�h�\����Ԃ�
	__declspec(dllexport) unsigned long long place(unsigned long long self, unsigned long long opponent, int index, unsigned long long *nself, unsigned long long *nopponent);

	// 
	__declspec(dllexport) int full_search(unsigned long long self, unsigned long long opponent, int wishful);
}
