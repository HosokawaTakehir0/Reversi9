#pragma once
#include "../include/scene/sceneManager.h"

//������̒������낦
void Scene::drawCenterString(int Height,const char* str, unsigned int color) {
	int strWidth = GetDrawStringWidth(str, -1);
	DrawFormatString((360 - strWidth)/2, Height, color,str);
}


//update�֐�,�N���b�N�̎�t�ƃV�[����update������
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


//draw�֐�,��ʂ̂������������
void SceneManager::draw() {
	ClearDrawScreen();
	mScene->draw();
	ScreenFlip();
};