#pragma once
#include "../include/reversi/plusNumPl.h"

//二次配列の転置
void transpose(int board[][9]) {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < i; ++j) {
			int temp = board[i][j];
			board[i][j] = board[j][i];
			board[j][i] = temp;
		}
	}
}

/*ナンプレのルール下で二次配列の入れ替え
3行をまとめてブロックとすると
ブロックごとの入れ替え(3コ)
ブロック内での行の入れ替え(3*3コ)
列でも同様のため転置をはさむ
*/
void swap2(int board[][9],int target) {
	if (target % 2 == 0) transpose(board);
	int i, j;
	switch (target % 3) {
	case 0:
		i = 1; j = 2;
		break;
	case 1:
		i = 0; j = 2;
		break;
	case 2:
		i = 0; j = 1;
		break;
	}
	if (target < 6) {
		i *= 3; j *= 3;
		std::swap(board[i],board[j]);
		std::swap(board[i + 1], board[j + 1]);
		std::swap(board[i + 2], board[j + 2]);
	}
	else {
		int target_ = target % 3 * 3;
		std::swap(board[target_ + i], board[target_ + j]);
	}
	if (target % 2 == 0) transpose(board);
}

void PlusNumPlReversi::creatBoard() {
	int numBoard[9][9] = \
	{
		{ 1,4,5,3,2,7,6,9,8 },
		{ 8,3,9,6,5,4,1,2,7 },
		{ 6,7,2,9,1,8,5,4,3 },
		{ 4,9,6,1,8,5,3,7,2 },
		{ 2,1,8,4,7,3,9,5,6 },
		{ 7,5,3,2,9,6,4,8,1 },
		{ 3,6,7,5,4,2,8,1,9 },
		{ 9,8,4,7,6,1,2,3,5 },
		{ 5,2,1,8,3,9,7,6,4 },
	};


	int x;
	for (int i = 0; i < 50; ++i) {
		x = mt() % 24;
		swap2(numBoard, x);
	}

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			scoreBoard[i][j] = numBoard[i][j];
		}
	}
}