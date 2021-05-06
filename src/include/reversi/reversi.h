#pragma once
#include "reversiUtil.h"
#include <deque>
#include <unordered_set>

struct gameRecord {//棋譜
	std::deque<int> stonePutList;
	int scoreBoard[9][9];
	int winner;
};

class Reversi
{
public:
	bitBoard board[2];//盤面(-1:石なし、0:黒、1:白)
	int scoreBoard[9][9];//各マスの盤面
	int turnPlayer;//白黒識別(0:黒、1:白)
	int oppPlayer;
	int turn;//ターン
	bitBoard canPutBit;//石がおける箇所
	bool end;//終了したらtrue
	int score[2];//現時点でのスコア
	bool isOpen = true;//置いた石のスコアを開ける(本当は前のターンのスコアを比較したらわかる)
	std::deque<int> stonePutList;//石の置いた場所を順番に記録(棋譜製作用)


	Reversi();

	//盤面生成
	virtual  void creatBoard() {};

	//スコア計算
	virtual void cntScore();

	//石を置いて盤面更新
	virtual void updateBoard(int &point);

	bitBoard openScore;

protected:
	std::random_device rd;
	std::mt19937 mt;

	int tempOpenBoard[9][9] = {
	{0,0,1,0,0,0,1,0,0},
	{0,1,0,0,0,0,0,1,0},
	{1,0,0,0,0,0,0,0,1},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0,1},
	{0,1,0,0,0,0,0,1,0},
	{0,0,1,0,0,0,1,0,0}
	};



};
