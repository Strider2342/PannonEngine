#include "Graphics.h"

Graphics::Graphics()
{

}

void Graphics::Init()
{
	this->window = GameWindow(options.resolutionX, options.resolutionY, L"Pannon Engine", L"PannonClass");
}