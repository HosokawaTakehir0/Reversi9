#pragma once 
#include "reversi.h"


class PlusNumPlReversi : public Reversi {
public:
	PlusNumPlReversi();

	//�Ֆʐ���
	void creatBoard() override;

	//�X�R�A�v�Z
	void cntScore() override;

	//�΂�u���ĔՖʍX�V
	void updateBoard(int &point);
};