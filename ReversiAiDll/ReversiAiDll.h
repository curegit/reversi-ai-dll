#pragma once

// 外部にエクスポートされる関数を定義します
extern "C"
{
	// ビット番号からi座標を返す
	__declspec(dllexport) int index_to_position_i(int n);

	// ビット番号からj座標を返す
	__declspec(dllexport) int index_to_position_j(int n);

	// 座標位置からビット番号を返す
	__declspec(dllexport) int position_to_index(int i, int j);

	// n番目にだけビットを立たせたビットボード表現を返す
	__declspec(dllexport) unsigned long long index_to_bit(int n);

	// 特定の座標位置に対応する場所にだけビットを立たせたビットボード表現を返す
	__declspec(dllexport) unsigned long long position_to_bit(int i, int j);

	// 立っているビットの数を返す
	__declspec(dllexport) int count_bits(unsigned long long n);

	// selfプレイヤーの石の数からopponentプレイヤーの石の数を引いたものを返す
	__declspec(dllexport) int balance(unsigned long long self, unsigned long long opponent);

	// selfプレイヤーが着手可能な手のビットボード表現を返す
	__declspec(dllexport) unsigned long long possible_moves(unsigned long long self, unsigned long long opponent);

	// selfプレイヤーがindex地点に打てるかどうかを返す
	__declspec(dllexport) int can_place(unsigned long long self, unsigned long long opponent, int index);

	// selfプレイヤーがindex地点に打ったときに返せる石のビットボード表現を返す
	__declspec(dllexport) unsigned long long turnovers(unsigned long long self, unsigned long long opponent, int index);

	// selfプレイヤーがindex地点に打ったときに得られる盤を間接参照によって代入し、返した石のビットボード表現を返す
	__declspec(dllexport) unsigned long long place(unsigned long long self, unsigned long long opponent, int index, unsigned long long* nself, unsigned long long* nopponent);

	// 有利なほど大きいように盤上の位置ごとにつけられた重みを用いて、石のある位置の重みの和を返す
	__declspec(dllexport) int sum_of_weights(unsigned long long disks);

	// selfプレイヤーに有利なほど大きな数が返る静的評価関数
	__declspec(dllexport) int evaluation(unsigned long long self, unsigned long long opponent);

	// turns周りの開放度を返す
	__declspec(dllexport) int openness(unsigned long long self, unsigned long long opponent, unsigned long long turns);

	// 係数を掛けた開放度の負値を返す
	__declspec(dllexport) int openness_evaluation(unsigned long long self, unsigned long long opponent, unsigned long long turns);

	// ミニマックス戦略に基づいてゲーム木の完全探索をし、最良の手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// wishful を真にしておくと、互いに完璧に打てば負けてしまう場合は相手のミスに賭けるような選択をするようになる
	__declspec(dllexport) int full_search(unsigned long long self, unsigned long long opponent);

	// ミニマックス戦略に基づいてゲーム木の完全探索をし、最良の手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// この関数はCPUスレッド数のスレッドによって並列処理される
	__declspec(dllexport) int full_search_parallel(unsigned long long self, unsigned long long opponent);

	// ミニマックス戦略に基づいてゲーム木の完全探索をし、最良の手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// この関数は複数スレッドによって並列処理される
	__declspec(dllexport) int full_search_parallel_with(unsigned long long self, unsigned long long opponent, int concurrency);

	// ミニマックス戦略に基づいてゲーム木の部分探索をし、最良と思われる手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// depth は先読みの深さで、1以上である必要があり奇数が望ましい
	__declspec(dllexport) int heuristic_search(unsigned long long self, unsigned long long opponent, int depth);

	// ミニマックス戦略に基づいてゲーム木の部分探索をし、最良と思われる手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// depth は先読みの深さで、1以上である必要があり奇数が望ましい
	// この関数はCPUスレッド数のスレッドによって並列処理される
	__declspec(dllexport) int heuristic_search_parallel(unsigned long long self, unsigned long long opponent, int depth);

	// ミニマックス戦略に基づいてゲーム木の部分探索をし、最良と思われる手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// depth は先読みの深さで、1以上である必要があり奇数が望ましい
	// この関数は複数スレッドによって並列処理される
	__declspec(dllexport) int heuristic_search_parallel_with(unsigned long long self, unsigned long long opponent, int depth, int concurrency);

	// ミニマックス戦略に基づいてゲーム木の探索をし、最良と思われる手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// ゲームの進行度によって部分探索と完全探索を自動で選択する
	// 切り替えのタイミングと、先読みの深さは数秒で結果が返るような値に調整されている
	__declspec(dllexport) int choose_move(unsigned long long self, unsigned long long opponent);

	// ミニマックス戦略に基づいてゲーム木の探索をし、最良と思われる手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// ゲームの進行度によって部分探索と完全探索を自動で選択する
	// 切り替えのタイミングと、先読みの深さは数秒で結果が返るような値にだいたい調整されている
	// この関数はCPUスレッド数のスレッドによって並列処理される
	// 並列処理によって探索にかかる時間が短くなるので非並列版よりも深く読むようにしている
	__declspec(dllexport) int choose_move_parallel(unsigned long long self, unsigned long long opponent);

	// ミニマックス戦略に基づいてゲーム木の探索をし、最良と思われる手のビット番号を返す
	// 打つ手がない場合は -1 を返す
	// ゲームの進行度によって部分探索と完全探索を自動で選択する
	// 切り替えのタイミングと、先読みの深さは数秒で結果が返るような値にだいたい調整されている
	// この関数は複数スレッドによって並列処理される
	// 並列処理によって探索にかかる時間が短くなるので非並列版よりも深く読むようにしている
	__declspec(dllexport) int choose_move_parallel_with(unsigned long long self, unsigned long long opponent, int concurrency);
}
