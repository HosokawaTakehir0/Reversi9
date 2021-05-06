#pragma once
#include "sceneManager.h"
#include "../reversi/reversi.h"
#include "../reversi/plusMines.h"
#include "../reversi/plusNumPl.h"
#include "../reversi/com.h"



class GameMain :public Scene {
public:
	GameMain(SceneManager *pManager);

	~GameMain() {};

	void update() override;
	void draw() override;

	void flagUpdate();

private:
	Reversi *reversi;

	//盤面の各サイズ
	int BoardX = 0;//左上のx値
	int BoardY = 0;//左上のy値
	int BoxSize = 40;//マスの大きさ
	int halfBoxSize = 40 >> 1;//円を書き込むためのマスの中心
	int BoardSize = BoxSize * 9;//盤面の大きさ
	int BoardXX = BoardX + BoardSize;//右下のx値
	int BoardYY = BoardX + BoardSize;//右下のy値
	std::vector<int> tmpNextPoints;//置ける場所(flagのindex)
	std::vector<spot> nextPoints;//置ける場所(x,y表示)
	int indexFlag;//flagの読み取りindex
	int comTurn;//コンピュータ用(0:黒,1:白,-1:2p対戦のため参加なし)
	bool isWriteScore = true;

	Com com;
};