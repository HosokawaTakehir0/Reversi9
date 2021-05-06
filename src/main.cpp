#include <iostream>
#include <cmath>
#include "DxLib.h"
//#include "include.h"

#include "include/scene/sceneManager.h"
#include "include/scene/title.h"

//�E�B���h�E�T�C�Y�w��
int WindowHeight = 420;
int WindowWidth = 360;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	//�E�C���h�E�ݒ�
	SetMainWindowText("Reversi9EX");
	ChangeWindowMode(TRUE);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetWindowSizeChangeEnableFlag(FALSE); 
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//�V�[���Ǘ��N���X�̎��̉�
	SceneManager *manager;
	manager = new SceneManager();
	manager->mScene = new Title(manager);

	//�Q�[���̃��[�v��
	while (!ProcessMessage()) {
		manager->update();
		manager->draw();
		if (manager->isEnd)break;
	}

	//�Ǘ��N���X�̉��
	delete manager;
	
	//DxLib�̏I��
	DxLib_End();

	return 0;
}

