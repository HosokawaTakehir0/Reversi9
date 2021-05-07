#pragma once
#include "../include/reversi/com.h"
#include <filesystem>
#include<iostream>
#include <time.h>
#include<stdio.h>
#include <direct.h>
#include <string>
#include <fstream>
#include <sys/stat.h>



std::random_device rd;
std::mt19937 mt(rd());
std::normal_distribution<> dist(0.0, 1.0);
std::uniform_real_distribution<float> distr(0, 1);
std::normal_distribution<float> normal_distr(0, 0.82);


const int geneNum = 18 * 2;
const unsigned int indSize = 100;
unsigned int geneSize = 100;
const int m_UNDX = 3;
typedef float indv[geneNum];

//盤面をコンソール出力
void boardWrite(bitBoard black, bitBoard white, bitBoard canPut) {
	black >>= 12; white >>= 12; canPut >>= 12;
	int cnt = 0;
	for (int j = 0; j < 9; ++j) {
		for (int i = 0; i < 9; ++i) {
			if (black.test(i)) {
				std::cout << "●";
			}
			else if (white.test(i)) {
				std::cout << "○";
			}
			else if (canPut.test(i)) {
				std::cout << "×";
			}
			else {
				std::cout << "・";
			}
		}
		black >>= 11; white >>= 11; canPut >>= 11;
		std::cout << std::endl;
	}
}

//ゲーム一回分、勝者出力
gameRecord oneGame(Com &com1,Com &com2) {
	Reversi reversi;
	int stone;
	reversi.isOpen = true;

	while (reversi.end == false) {
		if (reversi.turnPlayer == 0) { stone = (com1.Put)(&reversi); }
		else { stone = com2.Put(&reversi); }
		reversi.updateBoard(stone);
		//boardWrite(reversi.board[0],reversi.board[1],reversi.canPutBit);
	}
	std::cout << reversi.score[0] << "vs" << reversi.score[1] << std::endl;
	gameRecord rt{reversi.stonePutList,0,reversi.turnPlayer};
	std::memcpy(rt.scoreBoard, reversi.scoreBoard, sizeof(int[9][9]));
	return rt;
}

//配列シャッフル
void rndShuffle(int* array, size_t size)
{
	int work;
	for (size_t i = size; i > 1; --i) {
		size_t a = i - 1;
		size_t b = rand() % i;
		work = array[a]; array[a] = array[b]; array[b] = work;
	}
}

//ノルム出力
float norm(const indv &x) {
	float nor = 0.0;
	size_t max_ = sizeof(x) / sizeof(x[0]);
	for (size_t i = 0; i < max_; ++i) {
		nor += x[i] * x[i];
	}
	return std::sqrt(nor);
}

//正規化
void normalize(indv &x) {
	float nor = norm(x);
	size_t max_ = sizeof(x) / sizeof(x[0]);
	for (size_t i = 0; i < max_; ++i) {
		x[i] /= nor;
	}
}

//ドット積
float dot(indv &vec1, indv &vec2) {
	float pro = 0.0;
	size_t max_ = sizeof(vec1) / sizeof(vec1[0]);
	for (size_t i = 0; i < max_; ++i) {
		pro += vec1[i] * vec2[i];
	}
	return pro;
}

//正規直交化
void orthonoramlize(indv *vec, int num) {
	size_t max_ = sizeof(vec) / sizeof(vec[0]);
	normalize(vec[0]);
	for (int i = 1; i < num; ++i) {
		indv totalSub = { 0.0 };
		for (int j = 0; j < i; ++j) {
			float dot_ = dot(vec[i], vec[j]);

			for (int k = 0; k < max_; ++k) {
				totalSub[k] += dot_ * vec[j][k];
			}
		}
		for (int j = 0; j < max_; ++j) {
			vec[i][j] -= totalSub[j];
		}
		normalize(vec[i]);
	}
}

//実数値型GAの交叉
void BLX_alpha(indv &ind1,indv &ind2) {
	size_t maxNum = sizeof(ind1) / sizeof(ind1[0]);
	float center,leng;
	for (size_t i = 0; i < maxNum; ++i) {
		center = (ind1[i] + ind2[i])/2.0;
		leng = std::fabsf(center - ind1[i]);
		if (distr(mt) < 0.7) { ind1[i] = center + distr(mt) * leng; }
		if (distr(mt) < 0.7) { ind2[i] = center + distr(mt) * leng; }
	}
}

int ga_main() {
	mt.seed(rd());
	Com com1(0);
	Com com2(1);
	Com com3(0);
	Com com4(1);
	
	float tmp[36] = { 0 };
	com3.setPutFunc(tmp, true);
	com4.setPutFunc(tmp, true);


	std::string main_dir =".\\GA";//GA統括用
	std::string now_dir;//各世代保存用
	_mkdir(main_dir.c_str());
	std::string rc_file = ".\\rc.bin";//棋譜保存ファイル
	std::ofstream ofs;
	std::ifstream ifs;
	

	const unsigned int halfSize = indSize >> 1;
	const unsigned int numTrial = 2;
	const int m = 4;
	indv pop[indSize];
	int fitness[indSize] = { 1 };
	int matchList[indSize];
	for (size_t i = 0; i < indSize; ++i)matchList[i] = i;
	int target[2];

	int totalFit;
	int c;
	int ball;
	int addi;
	int fGene;
	indv tmpPop[indSize];

	gameRecord rc;

	for (int i = 0; i < indSize; ++i) {
		for (int j = 0; j < geneNum; ++j) {
			pop[i][j] = distr(mt) * 400 - 200;
		}
	}

	//now_dir = main_dir + "\\" + std::to_string(0);
	//_mkdir(now_dir.c_str());

	//ofs.open((now_dir + "\\ind").c_str(), std::ios::binary);
	//ofs.write(reinterpret_cast<char *>(pop), sizeof(pop));
	//ofs.close();


	fGene = 0;

	now_dir = main_dir + "\\" + std::to_string(fGene);
	ifs.open((now_dir + "\\ind").c_str(), std::ios::binary);
	//ifs.read(reinterpret_cast<char *>(pop), sizeof(pop));
	ifs.close();



	for (size_t g = fGene; g < geneSize; ++g) {

		for (size_t i = 0; i < indSize; ++i)fitness[i] = 0;


		ofs.open((rc_file).c_str(), std::ios::binary | std::ios::app);
		for (size_t i = 0; i < numTrial; ++i) {

			rndShuffle(matchList, indSize);
			target[0] = 0, target[1] = 1;

			for (size_t j = 0; j < halfSize; ++j) {
				com1.setPutFunc(pop[target[0]],false);
				com2.setPutFunc(pop[target[1]],false);
				std::cout << g << "G," << j + i* 50 << ",trial::";
				//rc = oneGame(com1, com2);
				//fitness[matchList[target[rc.winner]]] += 1;
				rc = oneGame(com3, com4);
				ofs.write(reinterpret_cast<char *>(&rc), sizeof(gameRecord));
				ofs.flush();


				target[0] += 2; target[1] += 2;
			}
		}
		ofs.close();

		ofs.open((now_dir + "\\fitness").c_str(), std::ios::binary);
		ofs.write(reinterpret_cast<char *>(fitness), sizeof(fitness));
		ofs.close();
	
		totalFit = 1;
		//totalFit = 0;
		for (size_t i = 0; i < indSize; ++i)if (fitness[i] <= 1)fitness[i] = 0;

		int max_ = 0;
		std::vector<int> max_idx;

		for (size_t i = 0; i < indSize; ++i) { 
			totalFit += fitness[i];
			if (max_ < fitness[i]) {max_ = fitness[i];}
		}

		for (size_t i = 0; i < indSize; ++i) {
			if (max_ == fitness[i]) { max_idx.push_back(i); }
		}

		for (size_t i = 0; i < indSize; ++i) {
			ball = mt() % totalFit;
			addi = 0;
			for (c= 0; c < indSize; ++c) {
				addi += fitness[c];
				if (addi > ball)break;
			}
			std::memcpy(tmpPop[i],pop[c],sizeof(indv));
			//mutate(&tmpPop[i], 0.05);
			//std::cout << c << ",";
		}
		//std::cout << std::endl;
		for (size_t i = 0; i < max_idx.size(); ++i) {std::memcpy(pop[i], pop[max_idx[i]], sizeof(indv));}

		for (size_t i = max_idx.size(); i < indSize; ++i) { std::memcpy(pop[i], tmpPop[i], sizeof(indv)); }

		for (size_t i = 3; i < indSize; i += 2) { BLX_alpha(pop[i], pop[i + 1]); }

		for (int i = 5; i < 15; ++i) {
			for (int j = 0; j < 36; ++j) {
				std::cout << pop[i][j] << ",";
			}
			std::cout << std::endl << std::endl;
		}

		now_dir = main_dir + "\\" + std::to_string(g + 1);
		_mkdir(now_dir.c_str());

		ofs.open((now_dir + "\\ind").c_str(), std::ios::binary);
		ofs.write(reinterpret_cast<char *>(pop), sizeof(pop));
		ofs.close();
	}

	return 0;
}