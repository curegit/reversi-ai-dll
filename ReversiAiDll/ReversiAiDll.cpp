// DLLアプリケーション用にエクスポートされる関数を定義します

// プリコンパイル済みヘッダー
#include "stdafx.h"

// 正負反転可能なINTの最大・最小値
#define INTMAX 2147483647
#define INTMIN -2147483647

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

// 座標位置からビット番号を返す
inline int position_to_index(int i, int j)
{
	return (j << 3) | i;
}

// n番目にだけビットを立たせたビットボード表現を返す
inline unsigned long long index_to_bit(int n)
{
	return 0x01ull << n;
}

// 特定の座標位置に対応する場所にだけビットを立たせたビットボード表現を返す
inline unsigned long long position_to_bit(int i, int j)
{
	return index_to_bit(position_to_index(i, j));
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
	moves = flip << 8;
	// 北東
	flip = opp & (self << 7);
	flip |= opp & (flip << 7);
	flip |= opp & (flip << 7);
	flip |= opp & (flip << 7);
	flip |= opp & (flip << 7);
	flip |= opp & (flip << 7);
	moves |= flip << 7;
	// 東
	flip = opp & (self >> 1);
	flip |= opp & (flip >> 1);
	flip |= opp & (flip >> 1);
	flip |= opp & (flip >> 1);
	flip |= opp & (flip >> 1);
	flip |= opp & (flip >> 1);
	moves |= flip >> 1;
	// 南東
	flip = opp & (self >> 9);
	flip |= opp & (flip >> 9);
	flip |= opp & (flip >> 9);
	flip |= opp & (flip >> 9);
	flip |= opp & (flip >> 9);
	flip |= opp & (flip >> 9);
	moves |= flip >> 9;
	// 南
	flip = opponent & (self >> 8);
	flip |= opponent & (flip >> 8);
	flip |= opponent & (flip >> 8);
	flip |= opponent & (flip >> 8);
	flip |= opponent & (flip >> 8);
	flip |= opponent & (flip >> 8);
	moves |= flip >> 8;
	// 南西
	flip = opp & (self >> 7);
	flip |= opp & (flip >> 7);
	flip |= opp & (flip >> 7);
	flip |= opp & (flip >> 7);
	flip |= opp & (flip >> 7);
	flip |= opp & (flip >> 7);
	moves |= flip >> 7;
	// 西
	flip = opp & (self << 1);
	flip |= opp & (flip << 1);
	flip |= opp & (flip << 1);
	flip |= opp & (flip << 1);
	flip |= opp & (flip << 1);
	flip |= opp & (flip << 1);
	moves |= flip << 1;
	// 北西
	flip = opp & (self << 9);
	flip |= opp & (flip << 9);
	flip |= opp & (flip << 9);
	flip |= opp & (flip << 9);
	flip |= opp & (flip << 9);
	flip |= opp & (flip << 9);
	moves |= flip << 9;
	return moves & blank;
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

// selfプレイヤーがindex地点に打てるかどうかを返す
int can_place(unsigned long long self, unsigned long long opponent, int index)
{
	return 1 && (possible_moves(self, opponent) & index_to_bit(index));
}

// selfプレイヤーがindex地点に打ったときに得られる盤を間接参照によって代入し、返した石のビットボード表現を返す
inline unsigned long long place(unsigned long long self, unsigned long long opponent, int index, unsigned long long* nself, unsigned long long* nopponent)
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

// 有利なほど大きいように盤上の位置ごとにつけられた重みを用いて、石のある位置の重みの和を返す
inline int sum_of_weights(unsigned long long disks)
{
	const int w1[256] = { 0, 10000, -3000, 7000, 1000, 11000, -2000, 8000, 800, 10800, -2200, 7800, 1800, 11800, -1200, 8800, 800, 10800, -2200, 7800, 1800, 11800, -1200, 8800, 1600, 11600, -1400, 8600, 2600, 12600, -400, 9600, 1000, 11000, -2000, 8000, 2000, 12000, -1000, 9000, 1800, 11800, -1200, 8800, 2800, 12800, -200, 9800, 1800, 11800, -1200, 8800, 2800, 12800, -200, 9800, 2600, 12600, -400, 9600, 3600, 13600, 600, 10600, -3000, 7000, -6000, 4000, -2000, 8000, -5000, 5000, -2200, 7800, -5200, 4800, -1200, 8800, -4200, 5800, -2200, 7800, -5200, 4800, -1200, 8800, -4200, 5800, -1400, 8600, -4400, 5600, -400, 9600, -3400, 6600, -2000, 8000, -5000, 5000, -1000, 9000, -4000, 6000, -1200, 8800, -4200, 5800, -200, 9800, -3200, 6800, -1200, 8800, -4200, 5800, -200, 9800, -3200, 6800, -400, 9600, -3400, 6600, 600, 10600, -2400, 7600, 10000, 20000, 7000, 17000, 11000, 21000, 8000, 18000, 10800, 20800, 7800, 17800, 11800, 21800, 8800, 18800, 10800, 20800, 7800, 17800, 11800, 21800, 8800, 18800, 11600, 21600, 8600, 18600, 12600, 22600, 9600, 19600, 11000, 21000, 8000, 18000, 12000, 22000, 9000, 19000, 11800, 21800, 8800, 18800, 12800, 22800, 9800, 19800, 11800, 21800, 8800, 18800, 12800, 22800, 9800, 19800, 12600, 22600, 9600, 19600, 13600, 23600, 10600, 20600, 7000, 17000, 4000, 14000, 8000, 18000, 5000, 15000, 7800, 17800, 4800, 14800, 8800, 18800, 5800, 15800, 7800, 17800, 4800, 14800, 8800, 18800, 5800, 15800, 8600, 18600, 5600, 15600, 9600, 19600, 6600, 16600, 8000, 18000, 5000, 15000, 9000, 19000, 6000, 16000, 8800, 18800, 5800, 15800, 9800, 19800, 6800, 16800, 8800, 18800, 5800, 15800, 9800, 19800, 6800, 16800, 9600, 19600, 6600, 16600, 10600, 20600, 7600, 17600 };
	const int w2[256] = { 0, -3000, -5000, -8000, -450, -3450, -5450, -8450, -500, -3500, -5500, -8500, -950, -3950, -5950, -8950, -500, -3500, -5500, -8500, -950, -3950, -5950, -8950, -1000, -4000, -6000, -9000, -1450, -4450, -6450, -9450, -450, -3450, -5450, -8450, -900, -3900, -5900, -8900, -950, -3950, -5950, -8950, -1400, -4400, -6400, -9400, -950, -3950, -5950, -8950, -1400, -4400, -6400, -9400, -1450, -4450, -6450, -9450, -1900, -4900, -6900, -9900, -5000, -8000, -10000, -13000, -5450, -8450, -10450, -13450, -5500, -8500, -10500, -13500, -5950, -8950, -10950, -13950, -5500, -8500, -10500, -13500, -5950, -8950, -10950, -13950, -6000, -9000, -11000, -14000, -6450, -9450, -11450, -14450, -5450, -8450, -10450, -13450, -5900, -8900, -10900, -13900, -5950, -8950, -10950, -13950, -6400, -9400, -11400, -14400, -5950, -8950, -10950, -13950, -6400, -9400, -11400, -14400, -6450, -9450, -11450, -14450, -6900, -9900, -11900, -14900, -3000, -6000, -8000, -11000, -3450, -6450, -8450, -11450, -3500, -6500, -8500, -11500, -3950, -6950, -8950, -11950, -3500, -6500, -8500, -11500, -3950, -6950, -8950, -11950, -4000, -7000, -9000, -12000, -4450, -7450, -9450, -12450, -3450, -6450, -8450, -11450, -3900, -6900, -8900, -11900, -3950, -6950, -8950, -11950, -4400, -7400, -9400, -12400, -3950, -6950, -8950, -11950, -4400, -7400, -9400, -12400, -4450, -7450, -9450, -12450, -4900, -7900, -9900, -12900, -8000, -11000, -13000, -16000, -8450, -11450, -13450, -16450, -8500, -11500, -13500, -16500, -8950, -11950, -13950, -16950, -8500, -11500, -13500, -16500, -8950, -11950, -13950, -16950, -9000, -12000, -14000, -17000, -9450, -12450, -14450, -17450, -8450, -11450, -13450, -16450, -8900, -11900, -13900, -16900, -8950, -11950, -13950, -16950, -9400, -12400, -14400, -17400, -8950, -11950, -13950, -16950, -9400, -12400, -14400, -17400, -9450, -12450, -14450, -17450, -9900, -12900, -14900, -17900 };
	const int w3[256] = { 0, 1000, -450, 550, 30, 1030, -420, 580, 10, 1010, -440, 560, 40, 1040, -410, 590, 10, 1010, -440, 560, 40, 1040, -410, 590, 20, 1020, -430, 570, 50, 1050, -400, 600, 30, 1030, -420, 580, 60, 1060, -390, 610, 40, 1040, -410, 590, 70, 1070, -380, 620, 40, 1040, -410, 590, 70, 1070, -380, 620, 50, 1050, -400, 600, 80, 1080, -370, 630, -450, 550, -900, 100, -420, 580, -870, 130, -440, 560, -890, 110, -410, 590, -860, 140, -440, 560, -890, 110, -410, 590, -860, 140, -430, 570, -880, 120, -400, 600, -850, 150, -420, 580, -870, 130, -390, 610, -840, 160, -410, 590, -860, 140, -380, 620, -830, 170, -410, 590, -860, 140, -380, 620, -830, 170, -400, 600, -850, 150, -370, 630, -820, 180, 1000, 2000, 550, 1550, 1030, 2030, 580, 1580, 1010, 2010, 560, 1560, 1040, 2040, 590, 1590, 1010, 2010, 560, 1560, 1040, 2040, 590, 1590, 1020, 2020, 570, 1570, 1050, 2050, 600, 1600, 1030, 2030, 580, 1580, 1060, 2060, 610, 1610, 1040, 2040, 590, 1590, 1070, 2070, 620, 1620, 1040, 2040, 590, 1590, 1070, 2070, 620, 1620, 1050, 2050, 600, 1600, 1080, 2080, 630, 1630, 550, 1550, 100, 1100, 580, 1580, 130, 1130, 560, 1560, 110, 1110, 590, 1590, 140, 1140, 560, 1560, 110, 1110, 590, 1590, 140, 1140, 570, 1570, 120, 1120, 600, 1600, 150, 1150, 580, 1580, 130, 1130, 610, 1610, 160, 1160, 590, 1590, 140, 1140, 620, 1620, 170, 1170, 590, 1590, 140, 1140, 620, 1620, 170, 1170, 600, 1600, 150, 1150, 630, 1630, 180, 1180 };
	const int w4[256] = { 0, 800, -500, 300, 10, 810, -490, 310, 50, 850, -450, 350, 60, 860, -440, 360, 50, 850, -450, 350, 60, 860, -440, 360, 100, 900, -400, 400, 110, 910, -390, 410, 10, 810, -490, 310, 20, 820, -480, 320, 60, 860, -440, 360, 70, 870, -430, 370, 60, 860, -440, 360, 70, 870, -430, 370, 110, 910, -390, 410, 120, 920, -380, 420, -500, 300, -1000, -200, -490, 310, -990, -190, -450, 350, -950, -150, -440, 360, -940, -140, -450, 350, -950, -150, -440, 360, -940, -140, -400, 400, -900, -100, -390, 410, -890, -90, -490, 310, -990, -190, -480, 320, -980, -180, -440, 360, -940, -140, -430, 370, -930, -130, -440, 360, -940, -140, -430, 370, -930, -130, -390, 410, -890, -90, -380, 420, -880, -80, 800, 1600, 300, 1100, 810, 1610, 310, 1110, 850, 1650, 350, 1150, 860, 1660, 360, 1160, 850, 1650, 350, 1150, 860, 1660, 360, 1160, 900, 1700, 400, 1200, 910, 1710, 410, 1210, 810, 1610, 310, 1110, 820, 1620, 320, 1120, 860, 1660, 360, 1160, 870, 1670, 370, 1170, 860, 1660, 360, 1160, 870, 1670, 370, 1170, 910, 1710, 410, 1210, 920, 1720, 420, 1220, 300, 1100, -200, 600, 310, 1110, -190, 610, 350, 1150, -150, 650, 360, 1160, -140, 660, 350, 1150, -150, 650, 360, 1160, -140, 660, 400, 1200, -100, 700, 410, 1210, -90, 710, 310, 1110, -190, 610, 320, 1120, -180, 620, 360, 1160, -140, 660, 370, 1170, -130, 670, 360, 1160, -140, 660, 370, 1170, -130, 670, 410, 1210, -90, 710, 420, 1220, -80, 720 };
	int w = w1[disks & 0xFFull];
	w += w2[(disks >> 8) & 0xFFull];
	w += w3[(disks >> 16) & 0xFFull];
	w += w4[(disks >> 24) & 0xFFull];
	w += w4[(disks >> 32) & 0xFFull];
	w += w3[(disks >> 40) & 0xFFull];
	w += w2[(disks >> 48) & 0xFFull];
	w += w1[(disks >> 56)];
	return w;
}

// selfプレイヤーに有利なほど大きな数が返る静的評価関数
inline int evaluation(unsigned long long self, unsigned long long opponent)
{
	// 適当な係数を求める
	int b = count_bits(self | opponent);
	int k = 50 * b;
	// (自分の重み和 - 相手の重み和) + 係数 x (自分の着手可能手数 - 相手の着手可能手数)
	return (sum_of_weights(self) - sum_of_weights(opponent)) + k * (count_bits(possible_moves(self, opponent)) - count_bits(possible_moves(opponent, self)));
}

// turns周りの開放度を返す
inline int openness(unsigned long long self, unsigned long long opponent, unsigned long long turns)
{
	int o = 0;
	unsigned long long blank = empty_squares(self, opponent);
	unsigned long long blae = blank & 0x7F7F7F7F7F7F7F7Full;
	unsigned long long blaw = blank & 0xFEFEFEFEFEFEFEFEull;
	o += count_bits((turns << 8) & blank);
	o += count_bits((turns << 7) & blae);
	o += count_bits((turns >> 1) & blae);
	o += count_bits((turns >> 9) & blae);
	o += count_bits((turns >> 8) & blank);
	o += count_bits((turns >> 7) & blaw);
	o += count_bits((turns << 1) & blaw);
	o += count_bits((turns << 9) & blaw);
	return o;
}

// 係数を掛けた開放度の負値を返す
inline int openness_evaluation(unsigned long long self, unsigned long long opponent, unsigned long long turns)
{
	// 開放度に掛ける適当な係数
	const int k = 10;
	return -k * openness(self, opponent, turns);
}

// ゲーム木の完全探索のサブルーチン
int full_search_sub(unsigned long long self, unsigned long long opponent, int alpha, int beta)
{
	unsigned long long m = possible_moves(self, opponent);
	if (m)
	{
		int i = 0;
		unsigned long long s;
		unsigned long long o;
		unsigned long long* sp = &s;
		unsigned long long* op = &o;
		do
		{
			if (m & 0x01ull)
			{
				place(self, opponent, i, sp, op);
				int v = -full_search_sub(o, s, -beta, -alpha);
				if (v > alpha)
				{
					alpha = v;
					if (alpha >= beta)
					{
						break;
					}
				}
			}
			m = m >> 1;
			++i;
		} while (m);
		return alpha;
	}
	else
	{
		if (possible_moves(opponent, self))
		{
			return -full_search_sub(opponent, self, -beta, -alpha);
		}
		else
		{
			return balance(self, opponent);
		}
	}
}

// ミニマックス戦略に基づいてゲーム木の完全探索をし、最良の手のビット番号を返す
// 打つ手がない場合は -1 を返す
int full_search(unsigned long long self, unsigned long long opponent)
{
	// 打てる手がなければ終了
	unsigned long long moves = possible_moves(self, opponent);
	if (!moves)
	{
		return -1;
	}
	// 探索をする
	int alpha = INTMIN;
	int beta = INTMAX;
	int i = 0;
	int chosen;
	unsigned long long s;
	unsigned long long o;
	unsigned long long* sp = &s;
	unsigned long long* op = &o;
	unsigned long long m = moves;
	do
	{
		if (m & 0x01ull)
		{
			place(self, opponent, i, sp, op);
			int v = -full_search_sub(o, s, -beta, -alpha);
			if (v > alpha)
			{
				alpha = v;
				chosen = i;
			}
		}
		m = m >> 1;
		++i;
	} while (m);
	return chosen;
}

// 完全探索のスレッド関数
unsigned long WINAPI full_search_thread(void* args)
{
	int alpha = INTMIN;
	int beta = INTMAX;
	int* ret = (int*)args;
	unsigned long long s = ((unsigned long long*)args)[0];
	unsigned long long o = ((unsigned long long*)args)[1];
	*ret = -full_search_sub(o, s, -beta, -alpha);
	return 0;
}

// ミニマックス戦略に基づいてゲーム木の完全探索をし、最良の手のビット番号を返す
// 打つ手がない場合は -1 を返す
// この関数は複数スレッドによって並列処理される
int full_search_parallel_with(unsigned long long self, unsigned long long opponent, int concurrency)
{
	// 打てる手がなければ終了
	unsigned long long moves = possible_moves(self, opponent);
	if (!moves)
	{
		return -1;
	}
	// 探索をする
	int alpha = INTMIN;
	int i = 0;
	int chosen;
	unsigned long long s;
	unsigned long long o;
	unsigned long long* sp = &s;
	unsigned long long* op = &o;
	unsigned long long m = moves;
	unsigned long th[64];
	HANDLE handles[64] = { };
	unsigned long long shared[128];
	int free_thread = 0;
	unsigned int running = 0;
	HANDLE* running_handles = new HANDLE[concurrency];
	do
	{
		if (m & 0x01ull)
		{
			place(self, opponent, i, &s, &o);
			shared[i * 2] = s;
			shared[i * 2 + 1] = o;
			if (running == concurrency) {
				free_thread = WaitForMultipleObjects(concurrency, running_handles, false, INFINITE);
				--running;
			}
			handles[i] = CreateThread(NULL, 0, full_search_thread, shared + i * 2, 0, th + i);
			running_handles[free_thread] = handles[i];
			++free_thread;
			++running;
		}
		m = m >> 1;
		++i;
	} while (m);
	delete[] running_handles;
	// スレッドから結果を回収する
	for (i = 0; i < 64; i++)
	{
		if (handles[i])
		{
			WaitForSingleObject(handles[i], INFINITE);
			int v = *(int*)(shared + i * 2);
			if (v > alpha)
			{
				alpha = v;
				chosen = i;
			}
			CloseHandle(handles[i]);
		}
	}
	return chosen;
}

// ミニマックス戦略に基づいてゲーム木の完全探索をし、最良の手のビット番号を返す
// 打つ手がない場合は -1 を返す
// この関数はCPUスレッド数のスレッドによって並列処理される
int full_search_parallel(unsigned long long self, unsigned long long opponent)
{
	unsigned int cpu_count = std::thread::hardware_concurrency();
	return full_search_parallel_with(self, opponent, cpu_count);
}

// ゲーム木の部分探索のサブルーチン
int heuristic_search_sub(unsigned long long self, unsigned long long opponent, int depth, int alpha, int beta)
{
	const int confident_victory = 100000000;
	unsigned long long m = possible_moves(self, opponent);
	if (m)
	{
		if (depth)
		{
			int i = 0;
			int d = depth - 1;
			unsigned long long s;
			unsigned long long o;
			unsigned long long* sp = &s;
			unsigned long long* op = &o;
			do
			{
				if (m & 0x01ull)
				{
					place(self, opponent, i, sp, op);
					int v = -heuristic_search_sub(o, s, d, -beta, -alpha);
					if (v > alpha)
					{
						alpha = v;
						if (alpha >= beta)
						{
							break;
						}
					}
				}
				m = m >> 1;
				++i;
			} while (m);
			return alpha;
		}
		else
		{
			return evaluation(self, opponent);
		}
	}
	else
	{
		if (possible_moves(opponent, self))
		{
			if (depth)
			{
				return -heuristic_search_sub(opponent, self, depth - 1, -beta, -alpha);
			}
			else
			{
				return evaluation(self, opponent);
			}
		}
		else
		{
			if (balance(self, opponent) > 0)
			{
				return confident_victory;
			}
			else
			{
				return -confident_victory;
			}
		}
	}
}

// ミニマックス戦略に基づいてゲーム木の部分探索をし、最良と思われる手のビット番号を返す
// 打つ手がない場合は -1 を返す
// depth は先読みの深さで、1以上である必要があり奇数が望ましい
int heuristic_search(unsigned long long self, unsigned long long opponent, int depth)
{
	// 打てる手がなければ終了
	unsigned long long moves = possible_moves(self, opponent);
	if (!moves)
	{
		return -1;
	}
	// 探索をする
	int alpha = INTMIN;
	int beta = INTMAX;
	int i = 0;
	int chosen;
	unsigned long long s;
	unsigned long long o;
	unsigned long long* sp = &s;
	unsigned long long* op = &o;
	unsigned long long m = moves;
	int d = depth - 1;
	do
	{
		if (m & 0x01ull)
		{
			unsigned long long turns = place(self, opponent, i, sp, op);
			int v = -heuristic_search_sub(o, s, d, -beta, -alpha) + openness_evaluation(self, opponent, turns);
			if (v > alpha)
			{
				alpha = v;
				chosen = i;
			}
		}
		m = m >> 1;
		++i;
	} while (m);
	return chosen;
}

// 部分探索のスレッド関数
unsigned long WINAPI heuristic_search_thread(void* args)
{
	int alpha = INTMIN;
	int beta = INTMAX;
	int* ret = (int*)args;
	unsigned long long s = ((unsigned long long*)args)[0];
	unsigned long long o = ((unsigned long long*)args)[1];
	int d = ((int*)((unsigned long long*)args + 2))[0];
	int opns = ((int*)((unsigned long long*)args + 2))[1];
	*ret = -heuristic_search_sub(o, s, d, -beta, -alpha) + opns;
	return 0;
}

// ミニマックス戦略に基づいてゲーム木の部分探索をし、最良と思われる手のビット番号を返す
// 打つ手がない場合は -1 を返す
// depth は先読みの深さで、1以上である必要があり奇数が望ましい
// この関数は複数スレッドによって並列処理される
int heuristic_search_parallel_with(unsigned long long self, unsigned long long opponent, int depth, int concurrency)
{
	// 打てる手がなければ終了
	unsigned long long moves = possible_moves(self, opponent);
	if (!moves)
	{
		return -1;
	}
	// 探索をする
	int alpha = INTMIN;
	int i = 0;
	int chosen;
	unsigned long long s;
	unsigned long long o;
	unsigned long long* sp = &s;
	unsigned long long* op = &o;
	unsigned long long m = moves;
	unsigned long th[64];
	HANDLE handles[64] = { };
	unsigned long long shared[192];
	int free_thread = 0;
	unsigned int running = 0;
	HANDLE* running_handles = new HANDLE[concurrency];
	do
	{
		if (m & 0x01ull)
		{
			unsigned long long turns = place(self, opponent, i, &s, &o);
			shared[i * 3] = s;
			shared[i * 3 + 1] = o;
			((int*)(shared + i * 3 + 2))[0] = depth - 1;
			((int*)(shared + i * 3 + 2))[1] = openness_evaluation(self, opponent, turns);
			if (running == concurrency) {
				free_thread = WaitForMultipleObjects(concurrency, running_handles, false, INFINITE);
				--running;
			}
			handles[i] = CreateThread(NULL, 0, heuristic_search_thread, shared + i * 3, 0, th + i);
			running_handles[free_thread] = handles[i];
			++free_thread;
			++running;
		}
		m = m >> 1;
		++i;
	} while (m);
	delete[] running_handles;
	// スレッドから結果を回収する
	for (i = 0; i < 64; i++)
	{
		if (handles[i])
		{
			WaitForSingleObject(handles[i], INFINITE);
			int v = *(int*)(shared + i * 3);
			if (v > alpha)
			{
				alpha = v;
				chosen = i;
			}
			CloseHandle(handles[i]);
		}
	}
	return chosen;
}

// ミニマックス戦略に基づいてゲーム木の部分探索をし、最良と思われる手のビット番号を返す
// 打つ手がない場合は -1 を返す
// depth は先読みの深さで、1以上である必要があり奇数が望ましい
// この関数はCPUスレッド数のスレッドによって並列処理される
int heuristic_search_parallel(unsigned long long self, unsigned long long opponent, int depth)
{
	unsigned int cpu_count = std::thread::hardware_concurrency();
	return heuristic_search_parallel_with(self, opponent, depth, cpu_count);
}

// ミニマックス戦略に基づいてゲーム木の探索をし、最良と思われる手のビット番号を返す
// 打つ手がない場合は -1 を返す
// ゲームの進行度によって部分探索と完全探索を自動で選択する
// 切り替えのタイミングと、先読みの深さは数秒で結果が返るような値に調整されている
int choose_move(unsigned long long self, unsigned long long opponent)
{
	int occu = count_bits(self | opponent);
	if (occu > 50)
	{
		return full_search(self, opponent);
	}
	else
	{
		int move = max(count_bits(possible_moves(self, opponent)), count_bits(possible_moves(opponent, self)));
		return heuristic_search(self, opponent, move > 8 ? 5 : 7);
	}
}

// ミニマックス戦略に基づいてゲーム木の探索をし、最良と思われる手のビット番号を返す
// 打つ手がない場合は -1 を返す
// ゲームの進行度によって部分探索と完全探索を自動で選択する
// 切り替えのタイミングと、先読みの深さは数秒で結果が返るような値にだいたい調整されている
// この関数は複数スレッドによって並列処理される
// 並列処理によって探索にかかる時間が短くなるので非並列版よりも深く読むようにしている
int choose_move_parallel_with(unsigned long long self, unsigned long long opponent, int concurrency)
{
	int occu = count_bits(self | opponent);
	if (occu > 48)
	{
		return full_search_parallel_with(self, opponent, concurrency);
	}
	else
	{
		int move = max(count_bits(possible_moves(self, opponent)), count_bits(possible_moves(opponent, self)));
		return heuristic_search_parallel_with(self, opponent, move > 8 ? 7 : 9, concurrency);
	}
}

// ミニマックス戦略に基づいてゲーム木の探索をし、最良と思われる手のビット番号を返す
// 打つ手がない場合は -1 を返す
// ゲームの進行度によって部分探索と完全探索を自動で選択する
// 切り替えのタイミングと、先読みの深さは数秒で結果が返るような値にだいたい調整されている
// この関数はCPUスレッド数のスレッドによって並列処理される
// 並列処理によって探索にかかる時間が短くなるので非並列版よりも深く読むようにしている
int choose_move_parallel(unsigned long long self, unsigned long long opponent)
{
	unsigned int cpu_count = std::thread::hardware_concurrency();
	return choose_move_parallel_with(self, opponent, cpu_count);
}
