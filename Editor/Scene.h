#pragma once
#include "Graphics.h"

class Scene
{
private:
	Graphics graphics;

public:
	Scene();

	void Init(Graphics &graphics);
	void Load();
	void Update();
	void Draw();
};