#include "sceneManager.h"

//�Z���N�g��ʃN���X
class Select : public Scene {
public:
	Select(SceneManager *pManager) :Scene(pManager) {};
	~Select() {};

	void update() override;
	void draw() override;

private:
	int page = 0;//�y�[�W�ԍ�
	gameMode modeSet;
};