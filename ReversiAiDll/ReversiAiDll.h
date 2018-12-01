#pragma once

// 外部にエクスポートされる関数を定義します
extern "C"
{
	// 定数黒を返す
	__declspec(dllexport) int const_dark();

	// 定数白を返す
	__declspec(dllexport) int const_light();

	// 座標位置からビット番号を返す
	__declspec(dllexport) int position_to_index(int i, int j);

	// ビット番号からi座標を返す
	__declspec(dllexport) int index_to_position_i(int n);

	// ビット番号からj座標を返す
	__declspec(dllexport) int index_to_position_j(int n);

	// 着手可能な手のビットボード表現を返す
	__declspec(dllexport) unsigned long long possible_moves(unsigned long long dark, unsigned long long light, int player);

	// 特定のプレイヤーがある地点に打ったときに返せる石のビットボード表現を返す
	__declspec(dllexport) unsigned long long turnovers(unsigned long long dark, unsigned long long light, int player, int index);
}
