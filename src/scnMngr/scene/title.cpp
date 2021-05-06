#pragma once
#include "../../include/scene/Title.h"
#include "../../include/scene/select.h"

#define PI 3.14159265359

//�N���b�N���ƂɎ��y�[�W�֑J��
void Title::update() {
	if (manager->isClicked){
		manager->mScene = new Select(manager);
		delete this;
	}
}

void Title::draw() {
	//�F�擾
	timer += 1;
	timer %= 100;

	int sin_ = int(127 * std::sin(timer*PI / 50.0));
	int cos_ = int(127 * std::cos(timer*PI / 50.0));

	unsigned int White = GetColor(255, 255, 255);
	unsigned int Blink = GetColor(128 + cos_, 128 - cos_, 128 + sin_);



	drawCenterString(160, "Reversi9EX", White);

	drawCenterString(320, "Click to start!", Blink);

}