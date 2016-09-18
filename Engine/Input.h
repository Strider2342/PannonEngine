#pragma once
#include <windows.h>
#include <DirectXMath.h>

enum KeyCode
{
	A = 'A',
	B = 'B',
	C = 'C',
	D = 'D',
	E = 'E',
	F = 'F',
	G = 'G',
	H = 'H',
	I = 'I',
	J = 'J',
	K = 'K',
	L = 'L',
	M = 'M',
	N = 'N',
	O = 'P',
	P = 'P',
	Q = 'Q',
	R = 'R',
	S = 'S',
	T = 'T',
	U = 'U',
	V = 'V',
	W = 'W',
	X = 'X',
	Y = 'Y',
	Z = 'Z',

	F1 = VK_F1,
	F2 = VK_F2,
	F3 = VK_F3,
	F4 = VK_F4,
	F5 = VK_F5,
	F6 = VK_F6,
	F7 = VK_F7,
	F8 = VK_F8,
	F9 = VK_F9,
	F10 = VK_F10,
	F11 = VK_F11,
	F12 = VK_F12,

	LeftArrow = VK_LEFT,
	UpArrow = VK_UP,
	RightArrow = VK_RIGHT,
	DownArrow = VK_DOWN,

	Space = VK_SPACE,
	Esc = VK_ESCAPE,
	Tab = VK_TAB,

	Control = VK_CONTROL,
	LeftControl = VK_LCONTROL,
	RightControl = VK_RCONTROL,
	Shift = VK_SHIFT,
	LeftShift = VK_LSHIFT,
	RightShift = VK_RSHIFT,

	Plus = VK_ADD,
	Minus = VK_SUBTRACT
};
enum MouseButton
{
	LeftButton = VK_LBUTTON,
	MiddleButton = VK_MBUTTON,
	RightButton = VK_RBUTTON
};

class Input
{
public:
	static bool GetKeyDown(KeyCode keycode);

	static bool GetMouseButtonDown(MouseButton mousebutton);
	static DirectX::XMFLOAT2 GetMousePosition();
};