// DLLアプリケーション用にエクスポートされる関数を定義します

// プリコンパイル済みヘッダー
#include "stdafx.h"

// 黒を表す値
#define DARK 0

//
#define LIGHT 1

//
#define GOD_MOVE 1000000000

//
#define SHITTY_MOVE -1000000000

//
#define MIN_I 0

#define MAX_I 7

#define MIN_J 0

#define MAX_J 7

// 位置座標を上位ビットと下位ビットに連結させて返す
int encode_position(int i, int j)
{
	return (i << 16) | j;
}

// 連結された位置座標を
int decode_position_i(int position)
{
	return (position >> 16) & 0xFFFF;
}

// 
int decode_position_j(int position)
{
	return position & 0xFFFF;
}

//
inline long empty_squares(long dark, long light)
{
	return ~(dark | light);
}

inline int can_place(long dark, long light, int player, int i, int j)
{
	for (
}

inline long turnovers(long dark, long light, int player, int i, int j)
{
	return
}

inline long possible_moves(long dark, long light, int player)
{
	long empty = empty_squares(dark, light);


		for (int i = 0; empty = empty >> i; i++)
		{
			if (empty & 1)
			{

			}
		}

	return
}

inline long


//
int choose_move(long dark, long light, int player, int options)
{

}
