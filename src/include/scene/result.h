#pragma once
#include "sceneManager.h"
#include "../reversi/reversi.h"

//���U���g�N���X
class Result : public Scene {
public:
	Result(SceneManager *pManager, int score_[2], bitBoard board1[2], int board2[9][9]);

	~Result() {};
	void update() override;
	void draw() override;

private:
	int player;//���s�v���C���[
	int score[2];//�e�v���C���[�̃X�R�A
	char tmpKey[256];//�L�[���͎擾�̕ϐ�
	int board[9][9][2];//�Ֆʂ̐��l
	//�Ֆʂ̊e�T�C�Y
	int BoardX = 0;//�����x�l
	int BoardY = 0;//�����y�l
	int BoxSize = 40;//�}�X�̑傫��
	int halfBoxSize = 40 >> 1;//�~���������ނ��߂̃}�X�̒��S
	int BoardSize = BoxSize * 9;//�Ֆʂ̑傫��
	int BoardXX = BoardX + BoardSize;//�E����x�l
	int BoardYY = BoardX + BoardSize;//�E����y�l
};