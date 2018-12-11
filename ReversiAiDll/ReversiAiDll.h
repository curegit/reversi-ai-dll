#pragma once

// 外部にエクスポートされる関数を定義します
extern "C"
{
	// 座標位置からビット番号を返す
	__declspec(dllexport) int position_to_index(int i, int j);

	// ビット番号からi座標を返す
	__declspec(dllexport) int index_to_position_i(int n);

	// ビット番号からj座標を返す
	__declspec(dllexport) int index_to_position_j(int n);

	// 立っているビットの数を返す
	__declspec(dllexport) int count_bits(unsigned long long n);

	// selfプレイヤーの石の数からopponentプレイヤーの石の数を引いたものを返す
	__declspec(dllexport) int balance(unsigned long long self, unsigned long long opponent);

	// selfプレイヤーが着手可能な手のビットボード表現を返す
	__declspec(dllexport) unsigned long long possible_moves(unsigned long long self, unsigned long long opponent);

	// selfプレイヤーがindex地点に打ったときに返せる石のビットボード表現を返す
	__declspec(dllexport) unsigned long long turnovers(unsigned long long self, unsigned long long opponent, int index);

	// selfプレイヤーがindex地点に打ったときに得られる盤を間接参照によって代入し、返した石のビットボード表現を返す
	__declspec(dllexport) unsigned long long place(unsigned long long self, unsigned long long opponent, int index, unsigned long long *nself, unsigned long long *nopponent);

	// 
	__declspec(dllexport) int full_search(unsigned long long self, unsigned long long opponent, int wishful);
}
