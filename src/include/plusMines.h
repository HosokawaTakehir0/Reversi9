#pragma once 
#include "reversi.h"


class PlusMinesReversi : public Reversi {
public:
	PlusMinesReversi();

	//�Ֆʐ���
	void creatBoard() override;

	//�X�R�A�v�Z
	void cntScore() override;

	//�΂�u���ĔՖʍX�V
	void updateBoard(int &point);
};