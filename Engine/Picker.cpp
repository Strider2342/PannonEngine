#include "Picker.h"

Picker::Picker()
{ }

void Picker::SetCamera(Camera * camera)
{
	this->camera = camera;
}

void Picker::SetObjects(std::list<GameObject*> gameObjects)
{
}

void Picker::PickObject()
{
	/*float x = Input::GetMousePosition().x;
	float y = Input::GetMousePosition().y;

	DirectX::XMFLOAT3 view;
	DirectXExt::XMFloat3Subtract(&view, camera->GetTransform()->GetForward(), camera->GetTransform()->GetPosition());
	DirectXExt::XMFloat3Normalize(&view);

	DirectX::XMFLOAT3 h;
	DirectXExt::XMFloat3CrossProduct(&h, view, camera->GetTransform()->GetUp());
	DirectXExt::XMFloat3Normalize(&h);

	DirectX::XMFLOAT3 v;
	DirectXExt::XMFloat3CrossProduct(&v, h, view);
	DirectXExt::XMFloat3Normalize(&v);

	float rad = camera->GetFOV() * DirectX::XM_PI / 180.0f;
	float vLength = tan(rad / 2) * camera->GetNearClippingPlane();
	float hLength = vLength * camera->GetAspectRatio();

	DirectXExt::XMFloat3Multiply(&v, vLength);
	DirectXExt::XMFloat3Multiply(&h, hLength);

	x -= options.resolutionX / 2;
	y -= options.resolutionY / 2;

	x /= options.resolutionX / 2;
	y /= options.resolutionY / 2;

	DirectX::XMFLOAT3 viewXnear;
	DirectXExt::XMFloat3Multiply(&viewXnear, camera->GetNearClippingPlane());

	DirectX::XMFLOAT3 hXx = h;
	DirectXExt::XMFloat3Multiply(&hXx, x);

	DirectX::XMFLOAT3 vXy = v;
	DirectXExt::XMFloat3Multiply(&vXy, y);

	DirectX::XMFLOAT3 pos;
	DirectXExt::XMFloat3Add(&pos, camera->GetTransform()->GetPosition(), viewXnear);
	DirectXExt::XMFloat3Add(&pos, pos, hXx);
	DirectXExt::XMFloat3Add(&pos, pos, vXy);

	DirectX::XMFLOAT3 dir;
	DirectXExt::XMFloat3Subtract(&dir, pos, camera->GetTransform()->GetPosition());*/
}
