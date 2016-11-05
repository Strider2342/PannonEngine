#include "Screen.h"

Screen::Screen()
{
}

Screen::Screen(int width, int height)
{
	this->width = width;
	this->height = height;
}

Ray Screen::ScreenPointToRay(DirectX::XMFLOAT2 position)
{
	Ray ray = Ray();

	DirectX::XMFLOAT2 normalized = NormalizeScreenPoint(position);

	normalized.x *= tan(camera->GetFOV() * 0.5f);
	normalized.y *= tan(camera->GetFOV() * 0.5f);

	DirectX::XMFLOAT3 v_origin = DirectX::XMFLOAT3(normalized.x * camera->GetNearClippingPlane(), normalized.y * camera->GetNearClippingPlane(), camera->GetNearClippingPlane());
	DirectX::XMFLOAT3 v_endpoint = DirectX::XMFLOAT3(normalized.x * camera->GetFarClippingPlane(), normalized.y * camera->GetFarClippingPlane(), camera->GetFarClippingPlane());

	DirectX::XMMATRIX viewMatrix = camera->GetViewMatrix();
	DirectX::XMMATRIX inverseViewMat = DirectX::XMMatrixInverse(nullptr, viewMatrix);

	DirectX::XMFLOAT3 origin;
	DirectX::XMFLOAT3 endpoint;

	DirectX::XMStoreFloat3(&origin, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&v_origin), inverseViewMat));
	DirectX::XMStoreFloat3(&endpoint, DirectX::XMVector3Transform(DirectX::XMLoadFloat3(&v_endpoint), inverseViewMat));

	DirectX::XMFLOAT3 direction;
	DirectX::XMFLOAT3 difference = DirectX::XMFLOAT3(endpoint.x - origin.x, endpoint.y - origin.y, endpoint.z - origin.z);
	DirectX::XMStoreFloat3(&direction, DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&difference)));

	origin = origin + camera->GetTransform()->GetPosition();

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
