// DLLアプリケーション用にエクスポートされる関数を定義します

// プリコンパイル済みヘッダー
#include "stdafx.h"

// 黒を表す値
#define DARK 0

// 白を表す値
#define LIGHT 1

// 敵を全滅させる手に対する評価
#define GOD_MOVE 1000000000

// 敵に全滅させられる手に対する評価
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

// 定数白を返す
int const_light()
{
	return LIGHT;
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
	unsigned long long pos = 0x01ull << index;
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
	unsigned long long p = 0x01ull << index;
	unsigned long long turns = turnovers(board.dark, board.light, player, index);
	if (player == DARK)
	{
		b.dark = board.dark | turns | p;
		b.light ^= turns;
	}
	else
	{
		b.dark ^= turns;
		b.light = board.light | turns | p;
	}
	return b;
}

/*
int evaluation(unsigned long dark, unsigned long light, int player)
{

}
*/

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