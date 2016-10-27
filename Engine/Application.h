#pragma once
#include <iostream>
#include <vector>
#include "Graphics.h"
#include "GameScene.h"

class Application
{
private:
	Graphics graphics;

	std::vector<Scene *> scenes;
	int currentScene = 0;

	ApplicationType type;

public:
	Application();
	Application(HWND& hWnd);

	void Run();
	void SetType(ApplicationType type);

	template <class T>
	void AddScene();
	
	template <class T>
	T* GetScene();
};

template<class T>
inline void Application::AddScene()
{
	T *scene = new T();
	scenes.push_back(scene);
}

template<class T>
inline T* Application::GetScene()
{
	for (int i = 0; i < scenes.size(); i++)
	{
		T *temp = dynamic_cast<T*>(scenes[i]);

		if (temp != NULL)
			return temp;
	}
	return NULL;
}
