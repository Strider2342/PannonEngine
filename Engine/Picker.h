#pragma once
#include <list>
#include "GameObject.h"
#include "Camera.h"
#include "Input.h"

class Picker
{
private:
	Camera *camera;

public:
	Picker();

	void SetCamera(Camera *camera);
	void SetObjects(std::list<GameObject *> gameObjects);
};