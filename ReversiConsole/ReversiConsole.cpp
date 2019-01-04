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

// 列数から列数文字を返す（不正な数値に対してはヌル文字を返す）
char i_to_char(int i)
{
	switch (i)
	{
	case 0:
		return 'h';
	case 1:
		return 'g';
	case 2:
		return 'f';
	case 3:
		return 'e';
	case 4:
		return 'd';
	case 5:
		return 'c';
	case 6:
		return 'b';
	case 7:
		return 'a';
	default:
		return NULL;
	}
}

// 行数から行数文字を返す（不正な数値に対してはヌル文字を返す）
char j_to_char(int j)
{
	switch (j)
	{
	case 0:
		return '8';
	case 1:
		return '7';
	case 2:
		return '6';
	case 3:
		return '5';
	case 4:
		return '4';
	case 5:
		return '3';
	case 6:
		return '2';
	case 7:
		return '1';
	default:
		return NULL;
	}
}

// 盤上の位置を表す文字列を返す
char* index_to_str(int index)
{
	char str[3];
	str[0] = i_to_char(index_to_position_i(index));
	str[1] = j_to_char(index_to_position_j(index));
	str[2] = '\0';
	return str;
}

// プレイヤーに入力を促す（置く場所がないときはこの関数を呼ばない）
int prompt_move()
{
	cout << "Your move >> ";
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

// AIに入力を促す（置く場所がないときはこの関数を呼ばない）
int prompt_ai(unsigned long long self, unsigned long long opponent)
{
	cout << "AI move >> ";
	int m = choose_move(self, opponent);
	cout << index_to_str(m) << "\n";
	return m;
}

// 盤の状態を標準出力で表示する
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

// 盤がゲーム終了状態でなければ真を返す
int is_not_end(unsigned long long player1, unsigned long long player2)
{
	return possible_moves(player1, player2) || possible_moves(player2, player1);
}

// プレイヤーの番の入れ替え
void swap(unsigned long long** player1, unsigned long long** player2)
{
	unsigned long long* siding = *player1;
	*player1 = *player2;
	*player2 = siding;
}

// エントリー
int main(const int argc, const char *argv[])
{
	int ai = 0;
	if (argc > 1)
	{
		string arg1 = string(argv[1]);
		if (arg1 == "dark")
		{
			ai = 0;
		}
		else if (arg1 == "light")
		{
			ai = 1;
		}
		else
		{
			cout << "Usage: \n" << argv[0] << " <YOUR SIDE [dark|light] = dark>\n";
			return 1;
		}
	}
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
					pos = prompt_ai(*self, *opponent);
				}
				else
				{
					pos = prompt_move();
				}
				if (pos == -1)
				{
					cout << "Syntax error. Please try again.\n";
				}
				else if (!can_place(*self, *opponent, pos))
				{
					cout << "Invalid move.\n";
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
			if (ai)
			{
				cout << "AI >> Pass\n";
			}
			else
			{
				cout << "You >> Pass\n";
			}
		}
		swap(&self, &opponent);
		ai = !ai;
	}
	cout << "Game end\n";
	print_board(dark, light);
	cout << "x " << count_bits(dark) << " - " << count_bits(light) << " o\n";
	return 0;
}
