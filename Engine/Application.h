#pragma once
#include <iostream>
#include <vector>
#include "Graphics.h"
#include "GameBuilder.h"
#include "GameScene.h"

class Application
{
private:
	Graphics graphics;
	GameBuilder builder;

	std::string projectPath = "";

	std::vector<Scene *> scenes;
	int currentScene = 0;

	ApplicationType type;

public:
	Application();
	Application(HWND& hWnd);

	void Run();

	std::string GetProjectPath();
	void SetProjectPath(std::string projectPath);

	template <class T>
	void AddScene();

	template <class T>
	void AddScene(T *scene);
	
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
inline void Application::AddScene(T * scene)
{
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
