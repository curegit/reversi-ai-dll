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

	// 有利なほど大きいように盤上の位置ごとにつけられた重みを用いて、石のある位置の重みの和を返す
	__declspec(dllexport) int sum_of_weights(unsigned long long disks);

	// turns周りの開放度を返す
	__declspec(dllexport) int openness(unsigned long long self, unsigned long long opponent, unsigned long long turns);

	// ミニマックス戦略に基づいてゲーム木の完全探索をし、最良の手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// wishful を真にしておくと、互いに完璧に打てば負けてしまう場合は相手のミスに賭けるような選択をするようになる
	__declspec(dllexport) int full_search(unsigned long long self, unsigned long long opponent, int wishful);

	// ミニマックス戦略に基づいてゲーム木の部分探索をし、最良と思われる手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// depth は先読みの深さで、1以上である必要があり奇数が望ましい
	__declspec(dllexport) int heuristic_search(unsigned long long self, unsigned long long opponent, int depth);
}
