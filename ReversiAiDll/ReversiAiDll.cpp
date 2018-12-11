// DLLアプリケーション用にエクスポートされる関数を定義します

// プリコンパイル済みヘッダー
#include "stdafx.h"

// 座標位置からビット番号を返す
int position_to_index(int i, int j)
{
	return (j << 3) | i;
}

// ビット番号からi座標を返す
int index_to_position_i(int n)
{
	return 0x07 & n;
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
inline unsigned long long empty_squares(unsigned long long player1, unsigned long long player2)
{
	return ~(player1 | player2);
}

// selfプレイヤーが着手可能な手のビットボード表現を返す
unsigned long long possible_moves(unsigned long long self, unsigned long long opponent)
{
	unsigned long long blank = empty_squares(self, opponent);
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

// selfプレイヤーがindex地点に打ったときに返せる石のビットボード表現を返す
unsigned long long turnovers(unsigned long long self, unsigned long long opponent, int index)
{
	unsigned long long turns = 0x00ull;
	unsigned long long pos = index_to_bit(index);
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

// selfプレイヤーがindex地点に打ったときに得られる盤を間接参照によって代入し、返した石のビットボード表現を返す
inline unsigned long long place(unsigned long long self, unsigned long long opponent, int index, unsigned long long *nself, unsigned long long *nopponent)
{
	unsigned long long turns = turnovers(self, opponent, index);
	*nself = self | turns | index_to_bit(index);
	*nopponent = opponent & ~turns;
	return turns;
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

// selfプレイヤーの石の数からopponentプレイヤーの石の数を引いたものを返す
inline int balance(unsigned long long self, unsigned long long opponent)
{
	return count_bits(self) - count_bits(opponent);
}

/*
// TODO
inline int evaluation(Board board)
{
	const int w1[256] = {};
	const int w2[256] = {};
	const int w3[256] = {};
	const int w4[256] = {};
}
*/

// 
int full_search_sub(unsigned long long self, unsigned long long opponent, int alpha, int beta)
{
	unsigned long long m = possible_moves(self, opponent);
	if (m)
	{
		int i = 0;
		int chosen;
		int max = MININT;
		unsigned long long s;
		unsigned long long o;
		unsigned long long *sp = &s;
		unsigned long long *op = &o;
		while (m)
		{
			if (m & 0x01ull)
			{
				place(self, opponent, i, sp, op);
				int v = -full_search_sub(o, s, 0, 0);
				if (v > max)
				{
					max = v;
					chosen = i;
				}
			}
			m = m >> 1;
			++i;
		}
		return chosen;
	}
	else
	{
		if (possible_moves(opponent, self))
		{
			return -full_search_sub(opponent, self, 0, 0);
		}
		else
		{
			return balance(self, opponent);
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
int full_search(unsigned long long self, unsigned long long opponent, int wishful)
{
	// 
	//int opp = to_opponent(player);
	unsigned long long moves = possible_moves(self, opponent);
	if (!moves)
	{
		return -1;
	}
	// 
	int alpha = MAXINT;
	int beta = MININT;
	int max = MININT;
	int i = 0;
	int chosen;
	unsigned long long s;
	unsigned long long o;
	unsigned long long *sp = &s;
	unsigned long long *op = &o;
	unsigned long long m = moves;
	while (m)
	{
		if (m & 0x01ull)
		{
			place(self, opponent, i, sp, op);
			int v = -full_search_sub(o, s, alpha, beta);
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
