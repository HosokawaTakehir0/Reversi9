#pragma once
#include "reversi.h"




class Com {

public:
	Com(int turn);
	~Com() {};

private:
	std::mt19937 mt;
	std::random_device rd;



public:
	float weightMap[36];
	float tempMap[18] = { 0 };
	float scoreSampleBoard[9][9];
	int myTurn;
	bool isRnd = false;

	void setPutFunc(float *arr,bool useRnd);
	int rndPut(Reversi *rev);

	float boardEval(bitBoard board[2],int turnPlayer, int depth, float alpha, float beta);
	float oneEval(bitBoard &player, bitBoard &opp);
	int Put1(Reversi *rev);

	int Put(Reversi *rev);
	int Dep = 4;

private:
	typedef int (Com::*p_func)(Reversi *rev);
	p_func p;


	
};
