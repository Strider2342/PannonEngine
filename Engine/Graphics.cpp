#include "Graphics.h"

Graphics::Graphics()
{

}

void Graphics::Init()
{
	window = GameWindow(options.resolutionX, options.resolutionY, L"PannonEngine", L"PannonClass");
}