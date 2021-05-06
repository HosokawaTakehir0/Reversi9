#pragma once
#include "sceneManager.h"
#include "../reversi/reversi.h"

//リザルトクラス
class Result : public Scene {
public:
	Result(SceneManager *pManager, int score_[2], bitBoard board1[2], int board2[9][9]);

	~Result() {};
	void update() override;
	void draw() override;

private:
	int player;//勝敗プレイヤー
	int score[2];//各プレイヤーのスコア
	char tmpKey[256];//キー入力取得の変数
	int board[9][9][2];//盤面の数値
	//盤面の各サイズ
	int BoardX = 0;//左上のx値
	int BoardY = 0;//左上のy値
	int BoxSize = 40;//マスの大きさ
	int halfBoxSize = 40 >> 1;//円を書き込むためのマスの中心
	int BoardSize = BoxSize * 9;//盤面の大きさ
	int BoardXX = BoardX + BoardSize;//右下のx値
	int BoardYY = BoardX + BoardSize;//右下のy値
};