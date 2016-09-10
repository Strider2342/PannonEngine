#include "DebugHelper.h"

std::string DebugHelper::XMFLOAT3ToString(DirectX::XMFLOAT3 vector)
{
	return "{" + std::to_string(vector.x) + "; " + std::to_string(vector.y) + "; " + std::to_string(vector.z) + "}";
}