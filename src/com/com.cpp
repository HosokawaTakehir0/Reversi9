#pragma once
#include "../include/reversi/com.h"

Com::Com(int turn) {
	mt.seed(rd());
	myTurn = turn;
}

void Com::setPutFunc(float *arr,bool useRnd) {
	if (useRnd) {
		p = &Com::rndPut;
		return;
	}

	for (int i = 0; i < 36; ++i) {
		weightMap[i] = arr[i];
	}
	p = &Com::Put1;
	
}

int Com::rndPut(Reversi *rev) {
	bitBoard hands = isPut(rev->board[myTurn], rev->board[myTurn ^ 1]);
	std::vector<int> handsList = getFlag(hands);
	return handsList[mt()%handsList.size()];
}


float Com::oneEval(bitBoard &player, bitBoard &opp) {
	float eval = 0;
	for (int i = 0; i < 4; ++i) {
		//1s–Ú6—ñ‚Ü‚Å•]‰¿‰ÁŽZ
		eval += tempMap[0] * player[12]; eval += tempMap[1] * player[13]; eval += tempMap[2] * player[14];
		eval += tempMap[3] * player[15]; eval += tempMap[4] * player[16]; eval += tempMap[5] * player[17];
		//2s–Ú6—ñ‚Ü‚Å•]‰¿‰ÁŽZ
		eval += tempMap[6] * player[23]; eval += tempMap[7] * player[24]; eval += tempMap[8] * player[25];
		eval += tempMap[9] * player[26]; eval += tempMap[10] * player[27]; eval += tempMap[11] * player[28];
		//3s–Ú6—ñ‚Ü‚Å•]‰¿‰ÁŽZ
		eval += tempMap[12] * player[34]; eval += tempMap[3] * player[35]; eval += tempMap[14] * player[36];
		eval += tempMap[15] * player[37]; eval += tempMap[38] * player[39]; eval += tempMap[17] * player[40];

		//1s–Ú6—ñ‚Ü‚Å•]‰¿Œ¸ŽZ
		eval -= tempMap[0] * opp[12]; eval -= tempMap[1] * opp[13]; eval -= tempMap[2] * opp[14];
		eval -= tempMap[3] * opp[15]; eval -= tempMap[4] * opp[16]; eval -= tempMap[5] * opp[17];
		//2s–Ú6—ñ‚Ü‚Å•]‰¿Œ¸ŽZ
		eval -= tempMap[6] * opp[23]; eval -= tempMap[7] * opp[24]; eval -= tempMap[8] * opp[25];
		eval -= tempMap[9] * opp[26]; eval -= tempMap[10] * opp[27]; eval -= tempMap[11] * opp[28];
		//3s–Ú6—ñ‚Ü‚Å•]‰¿Œ¸ŽZ
		eval -= tempMap[12] * opp[34]; eval -= tempMap[3] * opp[35]; eval -= tempMap[14] * opp[36];
		eval -= tempMap[15] * opp[37]; eval -= tempMap[38] * opp[39]; eval -= tempMap[17] * opp[40];

		//”Õ–Ê‚Ì‘ÎÌ«‚©‚ç90“x‰ñ‚µ‚Ä4‰ñs‚¤(’†S9ƒ}ƒX‚Í–³Ž‹)
		rotate90degClock(player);
		rotate90degClock(opp);
	}

	int indexFlag = 12;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			eval += scoreSampleBoard[i][j] * player[indexFlag];
			eval -= scoreSampleBoard[i][j] * opp[indexFlag];
			++indexFlag;
		}
		indexFlag += 2;
	}
	return eval;
}


float Com::boardEval(bitBoard board[2],int turnPlayer,int depth,float alpha,float beta) {
	if (depth == 0) {
		return oneEval(board[myTurn], board[myTurn ^ 1]);
	}

	int oppPlayer = turnPlayer ^ 1;

	bitBoard hands = isPut(board[turnPlayer], board[oppPlayer]);
	if (hands.size() == 1) {
		if (depth == Dep) {
			return hands[0];
		}
	}

	if (hands == 0) {
		turnPlayer = oppPlayer;
		oppPlayer ^= 1;
		hands = isPut(board[turnPlayer], board[oppPlayer]);
		if (hands == 0) {
			return oneEval(board[myTurn], board[myTurn ^ 1]);
		}
	}
	std::vector<int> hansList = getFlag(hands);
	bitBoard temp[2];
	int selectHand;
	for (auto hand : hansList) {
		temp[0] = board[0]; temp[1] = board[0];
		doPut(hand, temp[turnPlayer], temp[oppPlayer]);
		float val = boardEval(temp, turnPlayer ^ 1  ,depth - 1, alpha, beta);
		if (turnPlayer == myTurn) {
			if (val > alpha) {
				alpha = val;
				selectHand = hand;
			}
			if (val > beta) return beta;
		}
		else {

			if (val < beta) {
				beta = val;
				selectHand = hand;
			}
			if (val < alpha)return alpha;
		}

	}

	if (depth == Dep)return selectHand;
	if (turnPlayer == myTurn) return alpha;
	return beta;
}

int Com::Put1(Reversi *rev) {
	int turn = rev->turn;
	float sumOpenScore;
	int indexFlag = 12;
	int nonSqCnt;
	float sampleScore;
	for (int i = 0; i < 9; ++i) {
		sumOpenScore = 0.0;
		nonSqCnt = 9;
		for (int j = 0; j < 9; ++j) {
			if (rev->openScore.test(indexFlag)) {
				sumOpenScore += rev->scoreBoard[i][j];
				--nonSqCnt;
			}
			++indexFlag;
		}
		indexFlag -= 9;
		sampleScore = (float)(45.0 - sumOpenScore) / nonSqCnt;
		for (int j = 0; j < 9; ++j) {
			if (rev->openScore.test(indexFlag)) {
				scoreSampleBoard[i][j] = rev->scoreBoard[i][j];
			}
			else {
				scoreSampleBoard[i][j] = sampleScore;
			}
			++indexFlag;
		}
		indexFlag += 2;
	}

	if (turn != 0) {//turn <66;
		float t = 1.0 / (1.0 + exp(-0.3 * (turn - 33)));
		for (int i = 0; i < 18; ++i) {
			tempMap[i] = (1.0 - t) * weightMap[i >> 1] + t * weightMap[(i >> 1) + 1];
		}
		return (int)(boardEval(rev->board, myTurn, Dep, -FLT_MAX, FLT_MAX));

	}
}

int Com::Put(Reversi *rev) {
	return (this->*p)(rev);
}