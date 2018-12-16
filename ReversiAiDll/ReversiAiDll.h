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

	// �L���ȂقǑ傫���悤�ɔՏ�̈ʒu���Ƃɂ���ꂽ�d�݂�p���āA�΂̂���ʒu�̏d�݂̘a��Ԃ�
	__declspec(dllexport) int sum_of_weights(unsigned long long disks);

	// turns����̊J���x��Ԃ�
	__declspec(dllexport) int openness(unsigned long long self, unsigned long long opponent, unsigned long long turns);

	// �~�j�}�b�N�X�헪�Ɋ�Â��ăQ�[���؂̊��S�T�������A�ŗǂ̎�̃r�b�g�ԍ���Ԃ�
	// �ł肪�Ȃ��ꍇ�� -1 ��Ԃ�
	// wishful ��^�ɂ��Ă����ƁA�݂��Ɋ����ɑłĂΕ����Ă��܂��ꍇ�͑���̃~�X�ɓq����悤�ȑI��������悤�ɂȂ�
	__declspec(dllexport) int full_search(unsigned long long self, unsigned long long opponent, int wishful);

	// �~�j�}�b�N�X�헪�Ɋ�Â��ăQ�[���؂̕����T�������A�ŗǂƎv�����̃r�b�g�ԍ���Ԃ�
	// �ł肪�Ȃ��ꍇ�� -1 ��Ԃ�
	// depth �͐�ǂ݂̐[���ŁA1�ȏ�ł���K�v���������]�܂���
	__declspec(dllexport) int heuristic_search(unsigned long long self, unsigned long long opponent, int depth);
}
