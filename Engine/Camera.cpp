#include "Camera.h"

Camera::Camera()
{ }

void Camera::Init()
{
	fov = 75.0f;
	aspectRatio = 1280.0f / 720.0f;
	nearClippingPlane = 0.1f;
	farClippingPlane = 100.0f;
}

DirectX::XMMATRIX& Camera::GetViewMatrix()
{
	DirectX::XMFLOAT3 position = transform->GetPosition();
	DirectX::XMFLOAT3 look = transform->GetForward();
	DirectX::XMFLOAT3 up = transform->GetUp();

	DirectX::XMVECTOR eyePos	= DirectX::XMLoadFloat3(&position);
	DirectX::XMVECTOR focusPos	= DirectX::XMLoadFloat3(&look);
	DirectX::XMVECTOR upDir		= DirectX::XMLoadFloat3(&up);

	matView = DirectX::XMMatrixLookAtLH(eyePos, focusPos, upDir);
	//matView = DirectX::XMMatrixInverse(nullptr, matView);

	return matView;
}

DirectX::XMMATRIX& Camera::GetProjectionMatrix()
{
	matProjection = DirectX::XMMatrixPerspectiveFovLH(fov, aspectRatio, nearClippingPlane, farClippingPlane);

	return matProjection;
}

float Camera::GetFOV()
{
	return fov;
}
float Camera::GetAspectRatio()
{
	return aspectRatio;
}
float Camera::GetNearClippingPlane()
{
	return nearClippingPlane;
}
float Camera::GetFarClippingPlane()
{
	return farClippingPlane;
}

Transform * Camera::GetTransform()
{
	return transform;
}

void Camera::SetTransform(Transform *transform)
{
	this->transform = transform;
}
