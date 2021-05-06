#pragma once
#include "../../include/scene/gameMain.h"
#include "../../include/scene/result.h"


GameMain::GameMain(SceneManager *pManager) :Scene(pManager), com(0) {
	switch (manager->modeSet.mode) {
	case 0:
		reversi = new Reversi();
		isWriteScore = false;
		break;
	case 1:
		reversi = new PlusNumPlReversi();
		break;
	case 2:
		reversi = new PlusMinesReversi();
		break;
	default:
		break;
	}

	switch (manager->modeSet.player) {
	case 0:
		com.myTurn = 1;
		comTurn = 1;
		break;
	case 1:
		com.myTurn = 0;
		comTurn = 0;
		break;
	default:
		comTurn = -1;
		break;
	}
	float tmpArr[36] = {
					-45.2085, -1080.63, 115.772, -2405.46, -211.173, 145.573,
					-46.5731, -2267.96, 111.737, -194.737, -82.0433, 103.865,
					125.274, 113.183, 143.497, 97.9999, 125.512, 97.6482,
					143.441, 160.75, 73.2191, 100.313, 125.71, 148.574,
					114.703, 118.774, 72.8827, 153.257, 106.789, 111.182,
					108.391, 149.678, 119.906, 117.302, 103.561, 115.533 };
	com.setPutFunc(tmpArr , false);

	tmpNextPoints = getFlag(reversi->canPutBit);
	for (size_t i = 0; i < tmpNextPoints.size(); ++i) {
		nextPoints.push_back(spot{ (tmpNextPoints[i] - 12) % 11,(tmpNextPoints[i] - 12) / 11 });
	}
}

void GameMain::flagUpdate() {
	tmpNextPoints = getFlag(reversi->canPutBit);
	nextPoints.clear();
	for (size_t i = 0; i < tmpNextPoints.size(); ++i) {
		nextPoints.push_back(spot{ (tmpNextPoints[i] - 12) % 11,(tmpNextPoints[i] - 12) / 11 });
	}
	if (reversi->end) {
		manager->mScene = new Result(manager, reversi->score, reversi->board, reversi->scoreBoard);
		delete this;
	}
}

void GameMain::update() {
	if (comTurn == reversi->turnPlayer) {
		int stone = com.Put(reversi);
		reversi->updateBoard(stone);
		flagUpdate();
	}
	if (manager->isClicked) {
		//クリックされたとき,石が置けるか判定
		bool isUpdate = false;
		int x = manager->MouseX / BoxSize; int y = manager->MouseY / BoxSize;
		int len = nextPoints.size();
		for (int i = 0; i < len; ++i) {
			if (x == nextPoints[i].x && y == nextPoints[i].y) isUpdate = true;
		}

		//石が置けたら盤面更新
		if (isUpdate) {
			int point = y * 11 + x + 12;
			reversi->updateBoard(point);
			flagUpdate();
		}
	}
}


void GameMain::draw() {
	//色取得
	timer += 1;
	timer %= 50;

	int cos_ = int(127 * std::cos(timer*PI / 25.0));

	unsigned int BackColor = GetColor(0, 255, 0);
	unsigned int Black = GetColor(0, 0, 0);
	unsigned int White = GetColor(255, 255, 255);
	unsigned int BlinkBlue = GetColor(0, 128 + cos_, 128 - cos_);
	unsigned int Red = GetColor(255, 0, 0);

	DrawBox(BoardX, BoardY, BoardXX, BoardYY, BackColor, TRUE);
	int mouseX = manager->MouseX; int mouseY = manager->MouseY;
	if (BoardX < mouseX && mouseX < BoardXX && BoardY < mouseY && mouseY < BoardYY) {
		int pointX = mouseX - mouseX % BoxSize; int pointY = mouseY - mouseY % BoxSize;
		DrawBox(pointX, pointY, pointX + BoxSize, pointY + BoxSize, BlinkBlue, TRUE);
	}

	int x, y;
	int r = 17;

	//次置ける場所にマーク配置
	int size = nextPoints.size();
	for (int i = 0; i < size; ++i) {
		x = nextPoints[i].x * BoxSize + halfBoxSize + BoardX;
		y = nextPoints[i].y * BoxSize + halfBoxSize + BoardY;
		DrawCircle(x, y, 8, Red);
	}

	//石配置
	x = BoardX + halfBoxSize; y = BoardY + halfBoxSize;
	indexFlag = 12;
	for (int i = 0; i < 9; ++i) {
		x = BoardX + BoxSize / 2;
		for (int j = 0; j < 9; ++j) {
			if (reversi->board[0].test(indexFlag)) {
				DrawCircle(x, y, r, Black);
			}
			else if (reversi->board[1].test(indexFlag)) {
				DrawCircle(x, y, r, White);
			}
			++indexFlag;
			x += BoxSize;
		}
		indexFlag += 2;
		y += BoxSize;
	}

	//マスの線書き込み
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

	//スコアの書き込み
	indexFlag = 12;
	if (isWriteScore) {
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				if (reversi->openScore.test(indexFlag)) {
					x = BoardX + halfBoxSize + BoxSize * j; y = BoardY + halfBoxSize + BoxSize * i;
					if (reversi->board[0].test(indexFlag)) {
						DrawFormatString(x - 3, y - 5, White, "%d", reversi->scoreBoard[i][j]);
					}
					else DrawFormatString(x - 3, y - 5, Black, "%d", reversi->scoreBoard[i][j]);
				}
				++indexFlag;
			}
			indexFlag += 2;
		}
	}

	//点数の書き込み
	DrawFormatString(0, 360, White, "%d::%d", reversi->score[0], reversi->score[1]);
	DrawFormatString(0, 380, White, "player%d turn", reversi->turnPlayer + 1);

}
