#pragma once
#include "../../include/scene/select.h"
#include "../../include/scene/gameMain.h"

#define PI 3.14159265359

//クリックごとに次ページへ遷移
void Select::update() {
	if (manager->isClicked) {
		if ((300 <= manager->MouseY) & (manager->MouseY <= 400)) {
			switch (manager->MouseX / 120) {
			case 0:
				if (page != 0)--page;
				break;
			case 1:
				manager->modeSet.mode = page;
				//manager->modeSet.player = -1;
				manager->mScene = new GameMain(manager);
				delete this;
				break;
			case 2:
				if (page != 2)++page;
			}
			
		}
		
	}
}

void Select::draw() {
	//色取得
	timer += 1;
	timer %= 100;

	int sin_ = int(127 * std::sin(timer*PI / 50.0));
	int cos_ = int(127 * std::cos(timer*PI / 50.0));

	unsigned int White = GetColor(255, 255, 255);
	unsigned int Black = GetColor(0, 0, 0);
	unsigned int Blink = GetColor(128 + cos_, 128 - cos_, 128 + sin_);

	switch (page) {
	case 0://通常モード
		DrawFormatString(0, 0, White, "Reversi9");

		DrawFormatString(0, 40, White, "Rule");
		DrawFormatString(0, 80, White, "・ 盤面が9×9のリバーシです．");
		DrawFormatString(0, 100, White, "勝利条件 : 相手より自分の石が多いとき");

		break;
		

	case 1://+NumPlaceモード
		DrawFormatString(0, 0, White, "+NumberPlace");

		DrawFormatString(0, 40, White, "Rule");
		//DrawFormatString(0, 60, White, "・ 盤面が9×9のリバーシです．");
		DrawFormatString(0, 80, White, "・ 各マスにスコアが設定されており");
		DrawFormatString(0, 100, White, "　 合計が自分のスコアになります");
		DrawFormatString(0, 120, White, "・ また、スコアの配置はナンプレ");
		DrawFormatString(0, 140, White, "　 と等しくなっており");
		DrawFormatString(0, 160, White, "　 タテ9マス,ヨコ9マス,各3×3のマス目に");
		DrawFormatString(0, 180, White, "　 1～9までの数字が一つずつ入っています");
		DrawFormatString(0, 200, White, "勝利条件 : スコアが相手より高くなる");

		break;

	case 2://+Minesweeperモード
		DrawFormatString(0, 0, White, "+MinesSweeper");

		DrawFormatString(0, 40, White, "Rule");
		//DrawFormatString(0, 60, White, "・ 盤面が9×9のリバーシです．");
		DrawFormatString(0, 80, White, "・ どこかのマスに18個の");
		DrawFormatString(0, 100, White, "　 爆弾が埋まっており、");
		DrawFormatString(0, 120, White, "   爆弾のマスを選ぶと");
		DrawFormatString(0, 140, White, "　 そのマスには相手の石が置かれます。");
		DrawFormatString(0, 160, White, "・ 石を置くと数字が公開され、");
		DrawFormatString(0, 180, White, "　 その数字は爆弾でなければ周囲の爆弾の数、");
		DrawFormatString(0, 200, White, "　 爆弾のときは-1が表示されます。");
		DrawFormatString(0, 220, White, "勝利条件 : 相手より自分の石が多いとき");

		break;
	}

	DrawBox(0, 300, 360, 400, White, TRUE);
	if ((300 <= manager->MouseY) & (manager->MouseY <= 400)) {
		int sel = manager->MouseX / 120;
		DrawBox(sel * 120, 300, (sel + 1)* 120, 400, Blink, TRUE);
	}
	DrawLine(120, 300, 120, 400, Black);
	DrawLine(240, 300, 240, 400, Black);
	DrawFormatString(0, 340, Black, "     prev         start         next ");
}