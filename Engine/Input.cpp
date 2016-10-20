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
	else
		return DirectX::XMFLOAT2(0, 0);
}