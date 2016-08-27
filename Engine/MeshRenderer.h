#pragma once

class MeshRenderer
{
private:

public:
	MeshRenderer();

	void InitPipeline();
	void LoadShader();

	void Render();
};