#pragma once
#include "../../include/scene/select.h"
#include "../../include/scene/result.h"


Result::Result(SceneManager *pManager, int score_[2], bitBoard board1[2], int board2[9][9]): Scene(pManager) {
	score[0] = score_[0], score[1] = score_[1];
	int temp = score[0] - score[1];
	player = 0;
	if (temp > 0) player = 1;
	if (temp < 0) player = 2;
	int indexFlag = 12;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			board[i][j][1] = board2[i][j];
			if (board1[0].test(indexFlag)) {
				board[i][j][0] = 0;
			}
			else if (board1[1].test(indexFlag)) {
				board[i][j][0] = 1;
			}
			else {
				board[i][j][0] = -1;
			}
			++indexFlag;
		}
		indexFlag += 2;
	}
};

//update　yが押されたら再度ゲーム開始，nが押されたらゲーム終了
void Result::update() {
	GetHitKeyStateAll(tmpKey);
	if (tmpKey[KEY_INPUT_Y] != 0) {
		manager->mScene = new Select(manager);
		delete this;
	}
	else if (tmpKey[KEY_INPUT_N] != 0) {
		manager->isEnd = true;
	}
}



void Result::draw() {
	//色取得
	timer += 1;
	timer %= 100;
	int cos_ = int(127 * std::cos(timer*PI / 50.0));

	unsigned int Blink = GetColor(128 + cos_, 0, 128 - cos_);

	unsigned int BackColor = GetColor(0, 255, 0);
	unsigned int Black = GetColor(0, 0, 0);
	unsigned int White = GetColor(255, 255, 255);
	unsigned int Blue = GetColor(0, 0, 255);
	unsigned int Red = GetColor(255, 0, 0);

	//勝敗書き込み
	if (player != 0) {
		DrawFormatString(0, 360, Blink, \
			"player%d is win(%d::%d)", player, score[0], score[1]);
	}
	else {
		DrawFormatString(0, 360, Blink, \
			"Draw(%d::%d)", player, score[0], score[1]);
	}
	DrawFormatString(0, 380, White, \
		"You want do it again? ");
	DrawFormatString(0, 400, White, \
		"(Please push key , Y / N)");

	//盤面書き込み
	DrawBox(BoardX, BoardY, BoardXX, BoardYY, BackColor, TRUE);

	int x, y;
	int r = 15;
	x = BoardX + halfBoxSize; y = BoardY + halfBoxSize;

	//各マスのスコアの表示
	for (int i = 0; i < 9; ++i) {
		x = BoardX + BoxSize / 2;
		for (int j = 0; j < 9; ++j) {
			switch (board[i][j][0]) {
			case -1:
				DrawFormatString(x - 3, y - 5, Black, "%d", board[i][j][1]);
				break;
			case 0:
				DrawCircle(x, y, r, Black);
				DrawFormatString(x - 3, y - 5, White, "%d", board[i][j][1]);
				break;
			case 1:
				DrawCircle(x, y, r, White);
				DrawFormatString(x - 3, y - 5, Black, "%d", board[i][j][1]);
				break;
			}
			x += BoxSize;
		}
		y += BoxSize;
	}

	//マスの線の書き込み
	for (int i = 0; i < 10; ++i) {
		x = BoardX + i * BoxSize;
		y = BoardY + i * BoxSize;
		DrawLine(BoardX, y, BoardXX, y, Black);
		DrawLine(x, BoardY, x, BoardYY, Black);
	}
	for (int i = 0; i < 10; i += 3) {
		x = BoardX + i * BoxSize;
		y = BoardY + i * BoxSize;
		DrawLine(BoardX, y, BoardXX, y, Red);
		DrawLine(x, BoardY, x, BoardYY, Red);
	}

}