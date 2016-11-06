#pragma once

class GameScene;
class GUI
{
protected:
	GameScene *scene;

public:
	GUI();

	void SetScene(GameScene *scene);
	
	virtual void Init();
	virtual void AssembleGUI();
	virtual void Render();
};