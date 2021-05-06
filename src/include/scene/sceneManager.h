#pragma once
#include "DxLib.h"
#include <cmath>


#define PI 3.14159265359

class SceneManager;

//�Q�[�����[�h
struct gameMode {
	int player = -1;//(��:0,�@��:1,�@��l�ΐ�:-1)
	int mode = 0;//(�ʏ�:0, +NumPl:1, +Mines:2)
};


//�V�[���N���X
class Scene{
protected:
	SceneManager *manager;

public:
	Scene(SceneManager *pManager) { manager = pManager; };
	virtual ~Scene() {};
	virtual void update() {};
	virtual void draw() {};
	int timer = 0;
	//�����̒������낦
	void drawCenterString(int Height,const char* str, unsigned int color);
};


//�V�[���Ǘ��N���X
class SceneManager {
public:
	SceneManager() {};
	~SceneManager() { delete mScene; };

	Scene *mScene;
	int MouseX, MouseY;//�}�E�X��x,y�l
	bool isPush = false;//�}�E�X���������܂�Ă��邩�ۂ�
	bool isClicked = false;//�}�E�X���������܂ꂽ��Ԃ��痣�ꂽ��ԂɂȂ����Ƃ�
	bool isEnd = false;//�Q�[�����I���������ۂ�
	gameMode modeSet;//�Q�[���̐ݒ��`����

	void update() ; 
	void draw();


};

