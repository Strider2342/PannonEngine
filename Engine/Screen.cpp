#include "Screen.h"

Screen::Screen()
{
}

Screen::Screen(int width, int height)
{
	this->width = width;
	this->height = height;
}

/*DirectX::XMFLOAT3 Screen::ScreenToWorld(DirectX::XMFLOAT2 position)
{
	//float x = Input::GetMousePosition().x;
	//float y = Input::GetMousePosition().y;

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

	position.x -= width / 2;
	position.y -= height / 2;

	position.x /= width / 2;
	position.y /= height / 2;

	DirectX::XMFLOAT3 viewXnear;
	DirectXExt::XMFloat3Multiply(&viewXnear, camera->GetNearClippingPlane());

	DirectX::XMFLOAT3 hXx = h;
	DirectXExt::XMFloat3Multiply(&hXx, position.x);

	DirectX::XMFLOAT3 vXy = v;
	DirectXExt::XMFloat3Multiply(&vXy, position.y);

	DirectX::XMFLOAT3 pos;
	DirectXExt::XMFloat3Add(&pos, camera->GetTransform()->GetPosition(), viewXnear);
	DirectXExt::XMFloat3Add(&pos, pos, hXx);
	DirectXExt::XMFloat3Add(&pos, pos, vXy);

	DirectX::XMFLOAT3 dir;
	DirectXExt::XMFloat3Subtract(&dir, pos, camera->GetTransform()->GetPosition());

	return pos;
}*/

Ray Screen::ScreenPointToRay(DirectX::XMFLOAT2 position)
{
	Ray ray = Ray();

	DirectX::XMFLOAT2 normalized = NormalizeScreenPoint(position);

	normalized.x *= tan(camera->GetFOV() * 0.5f);
	normalized.y *= tan(camera->GetFOV() * 0.5f);

	DirectX::XMFLOAT3 forward = camera->GetTransform()->GetForward();

	DirectX::XMFLOAT3 v_origin = DirectX::XMFLOAT3(normalized.x * camera->GetNearClippingPlane(), normalized.y * camera->GetNearClippingPlane(), camera->GetNearClippingPlane());
	DirectX::XMFLOAT3 v_endpoint = DirectX::XMFLOAT3(normalized.x * camera->GetFarClippingPlane(), normalized.y * camera->GetFarClippingPlane(), camera->GetFarClippingPlane());

	DirectX::XMMATRIX inverseViewMat = DirectX::XMMatrixInverse(NULL, camera->GetViewMatrix());

	DirectX::XMFLOAT3 origin;
	DirectX::XMFLOAT3 endpoint;

	DirectX::XMStoreFloat3(&origin, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&v_origin), inverseViewMat));
	DirectX::XMStoreFloat3(&endpoint, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&v_endpoint), inverseViewMat));

	DirectX::XMFLOAT3 direction;
	DirectX::XMFLOAT3 difference = DirectX::XMFLOAT3(endpoint.x - origin.x, endpoint.y - origin.y, endpoint.z - origin.z);
	DirectX::XMStoreFloat3(&direction, DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&difference)));

	origin.x += camera->GetTransform()->GetPosition().x;
	origin.y += camera->GetTransform()->GetPosition().y;
	origin.z += camera->GetTransform()->GetPosition().z;

	ray.SetOrigin(origin);
	ray.SetDirection(direction);

	return ray;
}

DirectX::XMFLOAT2 Screen::NormalizeScreenPoint(DirectX::XMFLOAT2 position)
{
	DirectX::XMFLOAT2 normalized = DirectX::XMFLOAT2(0.0f, 0.0f);

	normalized.x = (position.x / (width * 0.5f) - 1.0f) / (width / height);
	normalized.y = 1.0f - (position.y / (height * 0.5f));

	return normalized;
}

Camera* Screen::GetCamera()
{
	return camera;
}

void Screen::SetCamera(Camera *camera)
{
	this->camera = camera;
}
