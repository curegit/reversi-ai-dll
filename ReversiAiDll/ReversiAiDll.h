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

	// 立っているビットの数を返す
	__declspec(dllexport) int count_bits_ex(unsigned long long n);

	// 着手可能な手のビットボード表現を返す
	__declspec(dllexport) unsigned long long possible_moves(unsigned long long dark, unsigned long long light, int player);

	// 特定のプレイヤーがある地点に打ったときに返せる石のビットボード表現を返す
	__declspec(dllexport) unsigned long long turnovers(unsigned long long dark, unsigned long long light, int player, int index);

	// 特定のプレイヤーが現在の盤にある手を打ったときに得られる盤の黒石のビットボード表現を返す（エクスポート用）
	__declspec(dllexport) unsigned long long place_dark_ex(unsigned long long dark, unsigned long long light, int player, int index);

	// 特定のプレイヤーが現在の盤にある手を打ったときに得られる盤の白石のビットボード表現を返す（エクスポート用）
	__declspec(dllexport) unsigned long long place_light_ex(unsigned long long dark, unsigned long long light, int player, int index);

	// 
	__declspec(dllexport) int full_search(unsigned long long dark, unsigned long long light, int player, int wishful);
}
