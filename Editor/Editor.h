#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "EditorGraphics.h"

class Editor
{
private:
	EditorGraphics *graphics;

public:
	Editor();
	
	void Init(EditorGraphics *graphics);

	void Load();
	void Update();
	void Draw();
};