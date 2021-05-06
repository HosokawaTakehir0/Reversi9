#pragma once 
#include "reversi.h"


class PlusMinesReversi : public Reversi {
public:
	PlusMinesReversi();

	//盤面生成
	void creatBoard() override;

	//スコア計算
	void cntScore() override;

	//石を置いて盤面更新
	void updateBoard(int &point);
};