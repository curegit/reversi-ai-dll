#pragma once

// �O���ɃG�N�X�|�[�g�����֐����`���܂�
extern "C"
{
	// �萔����Ԃ�
	__declspec(dllexport) int const_dark();

	// �萔����Ԃ�
	__declspec(dllexport) int const_light();

	// ���W�ʒu����r�b�g�ԍ���Ԃ�
	__declspec(dllexport) int position_to_index(int i, int j);

	// �r�b�g�ԍ�����i���W��Ԃ�
	__declspec(dllexport) int index_to_position_i(int n);

	// �r�b�g�ԍ�����j���W��Ԃ�
	__declspec(dllexport) int index_to_position_j(int n);

	// ����\�Ȏ�̃r�b�g�{�[�h�\����Ԃ�
	__declspec(dllexport) unsigned long long possible_moves(unsigned long long dark, unsigned long long light, int player);

	// ����̃v���C���[������n�_�ɑł����Ƃ��ɕԂ���΂̃r�b�g�{�[�h�\����Ԃ�
	__declspec(dllexport) unsigned long long turnovers(unsigned long long dark, unsigned long long light, int player, int index);
}
