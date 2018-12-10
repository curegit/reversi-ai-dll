// DLLアプリケーション用にエクスポートされる関数を定義します

// プリコンパイル済みヘッダー
#include "stdafx.h"

// 黒を表す値
#define DARK 0

// 敵を全滅させる手に対する評価の大きさ
#define GOD_MOVE 1000000000

// 敵に全滅させられる手に対する評価の大きさ
#define SHITTY_MOVE -1000000000

// ビットボードによって盤の状態を表す構造体
struct Board
{
	unsigned long long dark;
	unsigned long long light;
};

// 定数黒を返す
int const_dark()
{
	return DARK;
}

// 相手の定数を返す
inline int to_opponent(int player)
{
	return player ^ 0x01;
}

// 定数白を返す
int const_light()
{
	return to_opponent(DARK);
}

// 座標位置からビット番号を返す
int position_to_index(int i, int j)
{
	return (j << 3) | i;
}

// ビット番号からi座標を返す
int index_to_position_i(int n)
{
	return 0b111 & n;
}

// ビット番号からj座標を返す
int index_to_position_j(int n)
{
	return n >> 3;
}

// n番目にだけビットを立たせたビットボード表現を返す
inline unsigned long long index_to_bit(int n)
{
	return 0x01ull << n;
}

// 空いているマスのビットボード表現を返す
inline unsigned long long empty_squares(unsigned long long dark, unsigned long long light)
{
	return ~(dark | light);
}

// 自分の石のビットボード表現を返す
inline unsigned long long self_disks(unsigned long long dark, unsigned long long light, int player)
{
	if (player == DARK) return dark;
	else return light;
}

// 相手の石のビットボード表現を返す
inline unsigned long long opponent_disks(unsigned long long dark, unsigned long long light, int player)
{
	if (player == DARK) return light;
	else return dark;
}

// 着手可能な手のビットボード表現を返す
unsigned long long possible_moves(unsigned long long dark, unsigned long long light, int player)
{
	unsigned long long blank = empty_squares(dark, light);
	unsigned long long self = self_disks(dark, light, player);
	unsigned long long opponent = opponent_disks(dark, light, player);
	unsigned long long opp = opponent & 0x7E7E7E7E7E7E7E7Eull;
	unsigned long long moves;
	unsigned long long flip;
	// 北
	flip = opponent & (self << 8);
	flip |= opponent & (flip << 8);
	flip |= opponent & (flip << 8);
	flip |= opponent & (flip << 8);
	flip |= opponent & (flip << 8);
	flip |= opponent & (flip << 8);
	moves = (flip << 8) & blank;
	// 北東
	flip = opp & (self << 7);
	flip |= opp & (flip << 7);
	flip |= opp & (flip << 7);
	flip |= opp & (flip << 7);
	flip |= opp & (flip << 7);
	flip |= opp & (flip << 7);
	moves |= (flip << 7) & blank;
	// 東
	flip = opp & (self >> 1);
	flip |= opp & (flip >> 1);
	flip |= opp & (flip >> 1);
	flip |= opp & (flip >> 1);
	flip |= opp & (flip >> 1);
	flip |= opp & (flip >> 1);
	moves |= (flip >> 1) & blank;
	// 南東
	flip = opp & (self >> 9);
	flip |= opp & (flip >> 9);
	flip |= opp & (flip >> 9);
	flip |= opp & (flip >> 9);
	flip |= opp & (flip >> 9);
	flip |= opp & (flip >> 9);
	moves |= (flip >> 9) & blank;
	// 南
	flip = opponent & (self >> 8);
	flip |= opponent & (flip >> 8);
	flip |= opponent & (flip >> 8);
	flip |= opponent & (flip >> 8);
	flip |= opponent & (flip >> 8);
	flip |= opponent & (flip >> 8);
	moves |= (flip >> 8) & blank;
	// 南西
	flip = opp & (self >> 7);
	flip |= opp & (flip >> 7);
	flip |= opp & (flip >> 7);
	flip |= opp & (flip >> 7);
	flip |= opp & (flip >> 7);
	flip |= opp & (flip >> 7);
	moves |= (flip >> 7) & blank;
	// 西
	flip = opp & (self << 1);
	flip |= opp & (flip << 1);
	flip |= opp & (flip << 1);
	flip |= opp & (flip << 1);
	flip |= opp & (flip << 1);
	flip |= opp & (flip << 1);
	moves |= (flip << 1) & blank;
	// 北西
	flip = opp & (self << 9);
	flip |= opp & (flip << 9);
	flip |= opp & (flip << 9);
	flip |= opp & (flip << 9);
	flip |= opp & (flip << 9);
	flip |= opp & (flip << 9);
	moves |= (flip << 9) & blank;
	return moves;
}

// 特定のプレイヤーがある地点に打ったときに返せる石のビットボード表現を返す
unsigned long long turnovers(unsigned long long dark, unsigned long long light, int player, int index)
{
	unsigned long long turns = 0x00ull;
	unsigned long long pos = index_to_bit(index);
	unsigned long long self = self_disks(dark, light, player);
	unsigned long long opponent = opponent_disks(dark, light, player);
	unsigned long long opp = opponent & 0x7E7E7E7E7E7E7E7Eull;
	unsigned long long t;
	// 北
	t = (pos << 8) & opponent;
	t |= (t << 8) & opponent;
	t |= (t << 8) & opponent;
	t |= (t << 8) & opponent;
	t |= (t << 8) & opponent;
	t |= (t << 8) & opponent;
	if ((t << 8) & self) turns |= t;
	// 北東
	t = (pos << 7) & opp;
	t |= (t << 7) & opp;
	t |= (t << 7) & opp;
	t |= (t << 7) & opp;
	t |= (t << 7) & opp;
	t |= (t << 7) & opp;
	if ((t << 7) & self) turns |= t;
	// 東
	t = (pos >> 1) & opp;
	t |= (t >> 1) & opp;
	t |= (t >> 1) & opp;
	t |= (t >> 1) & opp;
	t |= (t >> 1) & opp;
	t |= (t >> 1) & opp;
	if ((t >> 1) & self) turns |= t;
	// 南東
	t = (pos >> 9) & opp;
	t |= (t >> 9) & opp;
	t |= (t >> 9) & opp;
	t |= (t >> 9) & opp;
	t |= (t >> 9) & opp;
	t |= (t >> 9) & opp;
	if ((t >> 9) & self) turns |= t;
	// 南
	t = (pos >> 8) & opponent;
	t |= (t >> 8) & opponent;
	t |= (t >> 8) & opponent;
	t |= (t >> 8) & opponent;
	t |= (t >> 8) & opponent;
	t |= (t >> 8) & opponent;
	if ((t >> 8) & self) turns |= t;
	// 南西
	t = (pos >> 7) & opp;
	t |= (t >> 7) & opp;
	t |= (t >> 7) & opp;
	t |= (t >> 7) & opp;
	t |= (t >> 7) & opp;
	t |= (t >> 7) & opp;
	if ((t >> 7) & self) turns |= t;
	// 西
	t = (pos << 1) & opp;
	t |= (t << 1) & opp;
	t |= (t << 1) & opp;
	t |= (t << 1) & opp;
	t |= (t << 1) & opp;
	t |= (t << 1) & opp;
	if ((t << 1) & self) turns |= t;
	// 北西
	t = (pos << 9) & opp;
	t |= (t << 9) & opp;
	t |= (t << 9) & opp;
	t |= (t << 9) & opp;
	t |= (t << 9) & opp;
	t |= (t << 9) & opp;
	if ((t << 9) & self) turns |= t;
	return turns;
}

// 特定のプレイヤーが現在の盤にある手を打ったときに得られる盤を返す
inline Board place(Board board, int player, int index)
{
	Board b;
	unsigned long long p = index_to_bit(index);
	unsigned long long turns = turnovers(board.dark, board.light, player, index);
	if (player == DARK)
	{
		b.dark = board.dark | turns | p;
		b.light = board.light & ~turns;
	}
	else
	{
		b.dark = board.dark & ~turns;
		b.light = board.light | turns | p;
	}
	return b;
}

// 特定のプレイヤーが現在の盤にある手を打ったときに得られる盤の黒石のビットボード表現を返す（エクスポート用）
unsigned long long place_dark_ex(unsigned long long dark, unsigned long long light, int player, int index)
{
	Board b;
	b.dark = dark;
	b.light = light;
	b = place(b, player, index);
	return b.dark;
}

// 特定のプレイヤーが現在の盤にある手を打ったときに得られる盤の白石のビットボード表現を返す（エクスポート用）
unsigned long long place_light_ex(unsigned long long dark, unsigned long long light, int player, int index)
{
	Board b;
	b.dark = dark;
	b.light = light;
	b = place(b, player, index);
	return b.light;
}

// 立っているビットの数を返す
inline int count_bits(unsigned long long n)
{
	n = ((n & 0xAAAA'AAAA'AAAA'AAAAull) >> 1) + (n & 0x5555'5555'5555'5555ull);
	n = ((n & 0xCCCC'CCCC'CCCC'CCCCull) >> 2) + (n & 0x3333'3333'3333'3333ull);
	n = ((n & 0xF0F0'F0F0'F0F0'F0F0ull) >> 4) + (n & 0x0F0F'0F0F'0F0F'0F0Full);
	n = ((n & 0xFF00'FF00'FF00'FF00ull) >> 8) + (n & 0x00FF'00FF'00FF'00FFull);
	n = ((n & 0xFFFF'0000'FFFF'0000ull) >> 16) + (n & 0x0000'FFFF'0000'FFFFull);
	n = ((n & 0xFFFF'FFFF'0000'0000ull) >> 32) + (n & 0x0000'0000'FFFF'FFFFull);
	return (int)n;
}

// 立っているビットの数を返す（エクスポート用）
int count_bits_ex(unsigned long long n)
{
	return count_bits(n);
}

// TODO
inline int balance(Board board)
{
	return count_bits(board.dark) - count_bits(board.light);
}

// TODO
inline int evaluation(Board board)
{
	const int w1[256] = {};
	const int w2[256] = {};
	const int w3[256] = {};
	const int w4[256] = {};
}

// 
int full_search_sub(Board board, int player, int alpha, int beta)
{
	int opp = to_opponent(player);
	unsigned long long moves = possible_moves(board.dark, board.light, player);
	if (moves)
	{
		int i = 0;
		int chosen;
		int max = MININT;
		while (moves)
		{
			if (moves & 0x01ull)
			{
				int v = -full_search_sub(place(board, player, i), opp, 0, 0);
				if (v > max)
				{
					max = v;
					chosen = i;
				}
			}
			moves = moves >> 1;
			++i;
		}
		return chosen;
	}
	else
	{
		if (possible_moves(board.dark, board.light, opp))
		{
			return -full_search_sub(board, opp, 0, 0);
		}
		else
		{
			return (player == DARK ? -1 : 1) * balance(board);
		}
	}
}

//
/*
int full_search_wishful_sub(Board board, int player, )
{

}
*/

// ミニマックスアルゴリズムに基づいてゲーム木の完全探索をする
int full_search(unsigned long long dark, unsigned long long light, int player, int wishful)
{
	// 
	int opp = to_opponent(player);
	unsigned long long moves = possible_moves(dark, light, player);
	if (!moves)
	{
		return -1;
	}
	// 
	Board b;
	b.dark = dark;
	b.light = light;
	int alpha = MAXINT;
	int beta = MININT;
	int max = MININT;
	int i = 0;
	int chosen;
	unsigned long long m = moves;
	while (m)
	{
		if (m & 0x01ull)
		{
			int v = -full_search_sub(place(b, player, i), opp, alpha, beta);
			if (v > max)
			{
				max = v;
				chosen = i;
			}
		}
		m = m >> 1;
		++i;
	}
	// TODO: 負けてしまうときに相手のミスにかけることを実装をする
	/*
	if (max < 0 && wishful)
	{
		i = 0;
		max = MININT;
	}
	*/
	return chosen;
}



/*
//
int choose_move(unsigned long dark, unsigned long light, int player, int options)
{
	//
	unsigned long moves = possible_moves();
	//


	for (int k = 0; k < 64; k++)
	{
		if (moves >> k & 0x01 ? ? ? ? ? ? ? )
		{
			int i = number_to_position_i(i);
			int j = number_to_position_j(i);
			unsigned long board = place(i, j);
		}
	}
}
*/
