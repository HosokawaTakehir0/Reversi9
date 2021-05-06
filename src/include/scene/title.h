#include "sceneManager.h"

//タイトルクラス
class Title : public Scene {
public:
	Title(SceneManager *pManager) :Scene(pManager) {};
	~Title() {};

	void update() override;
	void draw() override;

};