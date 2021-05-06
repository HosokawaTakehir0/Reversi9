#pragma once
#include "../../include/scene/select.h"
#include "../../include/scene/gameMain.h"

#define PI 3.14159265359

//�N���b�N���ƂɎ��y�[�W�֑J��
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
	//�F�擾
	timer += 1;
	timer %= 100;

	int sin_ = int(127 * std::sin(timer*PI / 50.0));
	int cos_ = int(127 * std::cos(timer*PI / 50.0));

	unsigned int White = GetColor(255, 255, 255);
	unsigned int Black = GetColor(0, 0, 0);
	unsigned int Blink = GetColor(128 + cos_, 128 - cos_, 128 + sin_);

	switch (page) {
	case 0://�ʏ탂�[�h
		DrawFormatString(0, 0, White, "Reversi9");

		DrawFormatString(0, 40, White, "Rule");
		DrawFormatString(0, 80, White, "�E �Ֆʂ�9�~9�̃��o�[�V�ł��D");
		DrawFormatString(0, 100, White, "�������� : �����莩���̐΂������Ƃ�");

		break;
		

	case 1://+NumPlace���[�h
		DrawFormatString(0, 0, White, "+NumberPlace");

		DrawFormatString(0, 40, White, "Rule");
		//DrawFormatString(0, 60, White, "�E �Ֆʂ�9�~9�̃��o�[�V�ł��D");
		DrawFormatString(0, 80, White, "�E �e�}�X�ɃX�R�A���ݒ肳��Ă���");
		DrawFormatString(0, 100, White, "�@ ���v�������̃X�R�A�ɂȂ�܂�");
		DrawFormatString(0, 120, White, "�E �܂��A�X�R�A�̔z�u�̓i���v��");
		DrawFormatString(0, 140, White, "�@ �Ɠ������Ȃ��Ă���");
		DrawFormatString(0, 160, White, "�@ �^�e9�}�X,���R9�}�X,�e3�~3�̃}�X�ڂ�");
		DrawFormatString(0, 180, White, "�@ 1�`9�܂ł̐�������������Ă��܂�");
		DrawFormatString(0, 200, White, "�������� : �X�R�A�������荂���Ȃ�");

		break;

	case 2://+Minesweeper���[�h
		DrawFormatString(0, 0, White, "+MinesSweeper");

		DrawFormatString(0, 40, White, "Rule");
		//DrawFormatString(0, 60, White, "�E �Ֆʂ�9�~9�̃��o�[�V�ł��D");
		DrawFormatString(0, 80, White, "�E �ǂ����̃}�X��18��");
		DrawFormatString(0, 100, White, "�@ ���e�����܂��Ă���A");
		DrawFormatString(0, 120, White, "   ���e�̃}�X��I�Ԃ�");
		DrawFormatString(0, 140, White, "�@ ���̃}�X�ɂ͑���̐΂��u����܂��B");
		DrawFormatString(0, 160, White, "�E �΂�u���Ɛ��������J����A");
		DrawFormatString(0, 180, White, "�@ ���̐����͔��e�łȂ���Ύ��͂̔��e�̐��A");
		DrawFormatString(0, 200, White, "�@ ���e�̂Ƃ���-1���\������܂��B");
		DrawFormatString(0, 220, White, "�������� : �����莩���̐΂������Ƃ�");

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