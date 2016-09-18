#include "Input.h"

bool Input::GetKeyDown(KeyCode keycode)
{
	return GetAsyncKeyState(keycode);
}
bool Input::GetMouseButtonDown(MouseButton mousebutton)
{
	return GetAsyncKeyState(mousebutton);
}
DirectX::XMFLOAT2 Input::GetMousePosition()
{
	POINT p;
	if (GetCursorPos(&p))
	{
		return DirectX::XMFLOAT2(p.x, p.y);
	}
	else
		return DirectX::XMFLOAT2(0, 0);
}