#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Graphics.h"
#include "GUI.h"
#include "Scene.h"
#include "GameScene.h"
#include "ContentManager.h"
#include "GameObject.h"
#include "Input.h"

#include "DebugHelper.h"

#include "EditorCameraScript.h"

class EditorScene : public GameScene
{
private:
	GUI *gui;
	GameObject cameraMain, camera;
		
	GameObject teapot, bottle;
	GameObject light;

public:
	EditorScene();

	void LoadScene(GameScene *scene);
	
	void Start();
	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	template <class T>
	void SetGUI(T *gui);
};

template<class T>
inline void EditorScene::SetGUI(T *gui)
{
	this->gui = gui;
}
