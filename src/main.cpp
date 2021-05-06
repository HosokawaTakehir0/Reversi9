#include <iostream>
#include <cmath>
#include "DxLib.h"
//#include "include.h"

#include "include/scene/sceneManager.h"
#include "include/scene/title.h"

//ウィンドウサイズ指定
int WindowHeight = 420;
int WindowWidth = 360;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{	
	//ウインドウ設定
	SetMainWindowText("Reversi9EX");
	ChangeWindowMode(TRUE);
	SetGraphMode(WindowWidth, WindowHeight, 32);
	SetWindowSizeChangeEnableFlag(FALSE); 
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);

	//シーン管理クラスの実体化
	SceneManager *manager;
	manager = new SceneManager();
	manager->mScene = new Title(manager);

	//ゲームのループ文
	while (!ProcessMessage()) {
		manager->update();
		manager->draw();
		if (manager->isEnd)break;
	}

	//管理クラスの解放
	delete manager;
	
	//DxLibの終了
	DxLib_End();

	return 0;
}

