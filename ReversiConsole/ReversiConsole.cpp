#include "pch.h"
#include "ReversiAiDll.h"
#include <iostream>
using namespace std;

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

int main(const int argc, const char *argv[])
{
	print_board(3255235, 12444141);
}
