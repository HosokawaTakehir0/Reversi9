#include "sceneManager.h"

//�^�C�g���N���X
class Title : public Scene {
public:
	Title(SceneManager *pManager) :Scene(pManager) {};
	~Title() {};

	void update() override;
	void draw() override;

};