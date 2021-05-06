#include "sceneManager.h"

//セレクト画面クラス
class Select : public Scene {
public:
	Select(SceneManager *pManager) :Scene(pManager) {};
	~Select() {};

	void update() override;
	void draw() override;

private:
	int page = 0;//ページ番号
	gameMode modeSet;
};