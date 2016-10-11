#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "Application.h"

#include "Scene1.h"
#include "Scene2.h"

int main()
{
	Application application = Application();

	application.AddScene<Scene1>();
	application.AddScene<Scene2>();
	application.Run();

	return 0;
}