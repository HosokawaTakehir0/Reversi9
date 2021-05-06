#pragma once
#include "DxLib.h"
#include <cmath>


#define PI 3.14159265359

class SceneManager;

//ゲームモード
struct gameMode {
	int player = -1;//(黒:0,　白:1,　二人対戦:-1)
	int mode = 0;//(通常:0, +NumPl:1, +Mines:2)
};


//シーンクラス
class Scene{
protected:
	SceneManager *manager;

public:
	Scene(SceneManager *pManager) { manager = pManager; };
	virtual ~Scene() {};
	virtual void update() {};
	virtual void draw() {};
	int timer = 0;
	//文字の中央ぞろえ
	void drawCenterString(int Height,const char* str, unsigned int color);
};


//シーン管理クラス
class SceneManager {
public:
	SceneManager() {};
	~SceneManager() { delete mScene; };

	Scene *mScene;
	int MouseX, MouseY;//マウスのx,y値
	bool isPush = false;//マウスが押し込まれているか否か
	bool isClicked = false;//マウスが押し込まれた状態から離れた状態になったとき
	bool isEnd = false;//ゲームが終了したか否か
	gameMode modeSet;//ゲームの設定を伝える

	void update() ; 
	void draw();


};

