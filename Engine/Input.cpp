#include "Input.h"

Input::Input()
{
	SetPreviousPosition();
}

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
	HWND hWnd = GetActiveWindow();
	RECT rect;
	GetClientRect(hWnd, &rect);
	DirectX::XMFLOAT2 windowPosition = DirectX::XMFLOAT2(rect.left, rect.top);

	POINT p;
	if (GetCursorPos(&p))
	{
		ScreenToClient(hWnd, &p);
		return DirectX::XMFLOAT2(p.x, p.y);
	}

	return DirectX::XMFLOAT2(0.0f, 0.0f);
}

DirectX::XMFLOAT2 Input::GetDeltaPosition()
{
	DirectX::XMFLOAT2 delta;

	delta = GetMousePosition();
	delta.x -= prevPos.x;
	delta.y -= prevPos.y;

	return delta;
}

void Input::SetPreviousPosition()
{
	prevPos = GetMousePosition();
}
