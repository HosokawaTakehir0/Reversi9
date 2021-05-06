#pragma once
#include "../include/reversi/plusMines.h"


PlusMinesReversi::PlusMinesReversi() {
	creatBoard();

	openScore.set(48).set(50).set(60).set(70).set(72);
	openScore.set(49).set(59).set(61).set(71);
}

//盤面生成
void PlusMinesReversi::creatBoard() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			scoreBoard[i][j] = 0;
		}
	}
	int numMines = 18;
	std::vector<int> allList;
	allList.reserve(72);
	for (int i = 0; i < 30; ++i)allList.push_back(i);
	for (int i = 51; i < 81; ++i)allList.push_back(i);
	for (int i = 33; i < 39; ++i)allList.push_back(i);
	for (int i = 42; i < 48; ++i)allList.push_back(i);

	int id, num, x, y;
	for (int i = 0; i < numMines; ++i) {
		id = mt() % allList.size();
		num = allList[id];
		x = num % 9;
		y = num / 9;
		allList.erase(allList.begin() + id);
		scoreBoard[y][x] = -1;
		for (int dy = y - 1; dy <= y + 1; ++dy) {
			for (int dx = x - 1; dx <= x + 1; ++dx) {

				if ((dx >= 0)&(dx < 9)&(dy >= 0)&(dy < 9) \
					& !((dx == x)&(dy == y))){

					if (scoreBoard[dy][dx] != -1) ++scoreBoard[dy][dx];
				}
			}
		}
	}
}

//スコア計算
void PlusMinesReversi::cntScore() {
	Reversi::cntScore();
}

//石を置いて盤面の更新
void PlusMinesReversi::updateBoard(int &point) {

	//石を置いて次のプレイヤーにターンを渡す
	if (scoreBoard[point / 11 - 1][point % 11 - 1] == -1) {//爆弾を踏んだら相手の石として置く
		doPut(point, board[oppPlayer], board[turnPlayer]);
	}
	else {
		doPut(point, board[turnPlayer], board[oppPlayer]);
	}

	oppPlayer = turnPlayer;
	turnPlayer ^= 1;

	//石が置けるところがないと再度同じプレイヤーのターンへ
	canPutBit = isPut(board[turnPlayer], board[oppPlayer]);
	if (canPutBit == 0) {
		oppPlayer = turnPlayer;
		turnPlayer ^= 1;
		canPutBit = isPut(board[turnPlayer], board[oppPlayer]);
	}

	//それでも置けないならゲーム終了,ターンを勝利プレイヤーのものに変更して終了判定
	if (canPutBit == 0) {
		end = true;
		cntScore();
		turnPlayer = -1;
		if (score[0] > score[1]) turnPlayer = 0;
		if (score[0] < score[1]) turnPlayer = 1;

	}
	if (isOpen) { openScore.set(point); }
	//stonePutList.push_back(point);
	//nonPutList.erase(point);
	//スコア計算
	cntScore();
	turn += 1;
}