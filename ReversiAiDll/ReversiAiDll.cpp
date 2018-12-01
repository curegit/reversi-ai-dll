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

// 着手可能な手のビットボード表現を返す
unsigned long long possible_moves(unsigned long long dark, unsigned long long light, int player)
{
	unsigned long long blank = ~(dark | light);
	unsigned long long self;
	unsigned long long opponent;
	if (player == DARK)
	{
		self = dark;
		opponent = light;
	}
	else
	{
		self = light;
		opponent = dark;
	}
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
/*
unsigned long turnovers(unsigned long dark, unsigned long light, int player, int index)
{
	unsigned long turns = 0x00ul;

	unsigned long pos = 0x01ul << index;

	t = (pos << 1) & opp
		t |= (t << 1) & opp


		turns |= t;

	return turns;
}

Board place(Board board, int player, int number)
{

}

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