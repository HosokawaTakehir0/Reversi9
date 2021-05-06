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

	//�Ֆʂ̊e�T�C�Y
	int BoardX = 0;//�����x�l
	int BoardY = 0;//�����y�l
	int BoxSize = 40;//�}�X�̑傫��
	int halfBoxSize = 40 >> 1;//�~���������ނ��߂̃}�X�̒��S
	int BoardSize = BoxSize * 9;//�Ֆʂ̑傫��
	int BoardXX = BoardX + BoardSize;//�E����x�l
	int BoardYY = BoardX + BoardSize;//�E����y�l
	std::vector<int> tmpNextPoints;//�u����ꏊ(flag��index)
	std::vector<spot> nextPoints;//�u����ꏊ(x,y�\��)
	int indexFlag;//flag�̓ǂݎ��index
	int comTurn;//�R���s���[�^�p(0:��,1:��,-1:2p�ΐ�̂��ߎQ���Ȃ�)
	bool isWriteScore = true;

	Com com;
};