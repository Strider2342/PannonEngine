#pragma once
#include <list>
#include <DirectXMath.h>
#include "DirectXMathExtension.h"
#include "GraphicsOptions.h"
#include "GameObject.h"
#include "Camera.h"
#include "Input.h"

class Picker
{
private:
	GraphicsOptions options;
	Camera *camera;

public:
	Picker();

	void SetCamera(Camera *camera);
	void SetObjects(std::list<GameObject *> gameObjects);

	void PickObject();
};