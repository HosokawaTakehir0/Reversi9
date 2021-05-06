#pragma once
#include "../include/reversi/reversi.h"

Reversi::Reversi() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			scoreBoard[i][j] = 1;
		}
	}

	mt.seed(rd());

	/*初期石配置
	(左上は盤面上(4,4)の位置)
		●〇●
		〇●〇
		●〇●
	*/
	board[0].set(48).set(50).set(60).set(70).set(72);
	board[1].set(49).set(59).set(61).set(71);

	turnPlayer = 0;
	oppPlayer = 1;
	turn = 1;
	end = false;
	score[0] =0,score[1] = 0; 
	cntScore();

	canPutBit = isPut(board[turnPlayer], board[oppPlayer]);

	int indexFlag = 12;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (tempOpenBoard[i][j] == 1)openScore.set(indexFlag);
			++indexFlag;
		}
		indexFlag += 2;
	}
}

//現時点のスコアを計算
void Reversi::cntScore() {
	score[0] = board[0].count();
	score[1] = board[1].count();
}


//石を置いて盤面の更新
void Reversi::updateBoard(int &point) {

	//石を置いて次のプレイヤーにターンを渡す
	doPut(point, board[turnPlayer], board[oppPlayer]);
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
	if (canPutBit == 0){
		end = true;
		cntScore();
		turnPlayer = -1;
		if (score[0] > score[1]) turnPlayer = 0;
		if (score[0] < score[1]) turnPlayer = 1;

	}
	if (isOpen) { openScore.set(point); }
	stonePutList.push_back(point);

	//スコア計算
	cntScore();
	turn += 1;

}


