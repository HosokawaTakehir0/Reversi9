#pragma once
#include "reversiUtil.h"
#include <deque>
#include <unordered_set>

struct gameRecord {//����
	std::deque<int> stonePutList;
	int scoreBoard[9][9];
	int winner;
};

class Reversi
{
public:
	bitBoard board[2];//�Ֆ�(-1:�΂Ȃ��A0:���A1:��)
	int scoreBoard[9][9];//�e�}�X�̔Ֆ�
	int turnPlayer;//��������(0:���A1:��)
	int oppPlayer;
	int turn;//�^�[��
	bitBoard canPutBit;//�΂�������ӏ�
	bool end;//�I��������true
	int score[2];//�����_�ł̃X�R�A
	bool isOpen = true;//�u�����΂̃X�R�A���J����(�{���͑O�̃^�[���̃X�R�A���r������킩��)
	std::deque<int> stonePutList;//�΂̒u�����ꏊ�����ԂɋL�^(��������p)


	Reversi();

	//�Ֆʐ���
	virtual  void creatBoard() {};

	//�X�R�A�v�Z
	virtual void cntScore();

	//�΂�u���ĔՖʍX�V
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
