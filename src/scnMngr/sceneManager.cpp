#pragma once
#include "../include/scene/sceneManager.h"

//文字列の中央ぞろえ
void Scene::drawCenterString(int Height,const char* str, unsigned int color) {
	int strWidth = GetDrawStringWidth(str, -1);
	DrawFormatString((360 - strWidth)/2, Height, color,str);
}


//update関数,クリックの受付とシーンのupdateをする
void SceneManager::update() {
	GetMousePoint(&MouseX, &MouseY);
	if (isPush) {
		if (!GetMouseInput() & MOUSE_INPUT_LEFT) { isClicked = true; isPush = false; }
	}
	else {
		if (GetMouseInput() & MOUSE_INPUT_LEFT)isPush = true;
	}
	mScene->update();
	isClicked = false;
}


//draw関数,画面のちらつきも無くす
void SceneManager::draw() {
	ClearDrawScreen();
	mScene->draw();
	ScreenFlip();
};