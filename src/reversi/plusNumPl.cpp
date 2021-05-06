#pragma once
#include "../include/reversi/plusNumPl.h"

PlusNumPlReversi::PlusNumPlReversi() {
	creatBoard();
	cntScore();
}

//�����_�̃X�R�A���v�Z
void PlusNumPlReversi::cntScore() {
	score[0] = 0, score[1] = 0;
	int cnt = 12;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (board[0].test(cnt))score[0] += scoreBoard[i][j];
			++cnt;
		}
		cnt += 2;
	}
	cnt = 12;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (board[1].test(cnt))score[1] += scoreBoard[i][j];
			++cnt;
		}
		cnt += 2;
	}
}


//�΂�u���ĔՖʂ̍X�V
void PlusNumPlReversi::updateBoard(int &point) {
	Reversi::updateBoard(point);
}
