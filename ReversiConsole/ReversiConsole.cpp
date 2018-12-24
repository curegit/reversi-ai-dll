#include "pch.h"
#include "ReversiAiDll.h"
#include <iostream>
using namespace std;

// 列文字から列インデックスを返す（不正な文字に対しては -1 を返す）
int char_to_i(char c)
{
	switch (c)
	{
	case 'a':
	case 'A':
		return 7;
	case 'b':
	case 'B':
		return 6;
	case 'c':
	case 'C':
		return 5;
	case 'd':
	case 'D':
		return 4;
	case 'e':
	case 'E':
		return 3;
	case 'f':
	case 'F':
		return 2;
	case 'g':
	case 'G':
		return 1;
	case 'h':
	case 'H':
		return 0;
	default:
		return -1;
	}
}

// 行数文字から行インデックスを返す（不正な文字に対しては -1 を返す）
int char_to_j(char c)
{
	switch (c)
	{
	case '1':
		return 7;
	case '2':
		return 6;
	case '3':
		return 5;
	case '4':
		return 4;
	case '5':
		return 3;
	case '6':
		return 2;
	case '7':
		return 1;
	case '8':
		return 0;
	default:
		return -1;
	}
}

//
int prompt_move()
{
	char buffer[256];
	cin >> buffer;
	
	int i = char_to_i(buffer[0]);
	int j = char_to_j(buffer[1]);

	if (i != -1 && j != -1)
	{
		return position_to_index(i, j);
	}
	else
	{
		return -1;
	}
}



// 
void print_board(unsigned long long player1, unsigned long long player2)
{
	cout << "  | a b c d e f g h\n";
	cout << "-------------------\n";
	for (int i = 1; i <= 8; i++)
	{
		cout << i << " |";
		unsigned long long p1 = player1 >> 8 * (8 - i);
		unsigned long long p2 = player2 >> 8 * (8 - i);
		for (int j = 7; j >= 0; j--)
		{
			char c = ' ';
			if (p1 >> j & 0x01ull) c = 'x';
			if (p2 >> j & 0x01ull) c = 'o';
			cout << " " << c;
		}
		cout << "\n";
	}
}

// 
int is_not_end(unsigned long long player1, unsigned long long player2)
{
	return possible_moves(player1, player2) || possible_moves(player2, player1);
}

int main(const int argc, const char *argv[])
{
	int ai = 0;
	unsigned long long dark = 0x0000'0008'1000'0000ull;
	unsigned long long light = 0x0000'0010'0800'0000ull;
	unsigned long long *self = &dark;
	unsigned long long *opponent = &light;
	while (is_not_end(*self, *opponent))
	{
		print_board(dark, light);

		if (possible_moves(*self, *opponent))
		{
			int pos;
			while (true)
			{
				if (ai)
				{
					pos = choose_move(*self, *opponent);
				}
				else
				{
					pos = prompt_move();
				}
				if (pos == -1)
				{
					cout << "syntax\n";
				}
				else if (!can_place(*self, *opponent, pos))
				{
					cout << "wrong\n";
				}
				else
				{
					break;
				}
			}
			place(*self, *opponent, pos, self, opponent);
		}
		else
		{
			cout << "pass\n";
		}
		unsigned long long* tmp = self;
		self = opponent;
		opponent = tmp;
		ai = !ai;
	}

	cout << "end";

	return 0;
}
