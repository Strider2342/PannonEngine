#include "Camera.h"

Camera::Camera()
{ }

void Camera::Init()
{
	fov = 0.785398163f;
	aspectRatio = 1706.0f / 960.0f;
	nearClippingPlane = 0.1f;
	farClippingPlane = 1000.0f;
}

DirectX::XMMATRIX& Camera::GetViewMatrix()
{
	DirectX::XMFLOAT3 position = transform->GetPosition();

	XMFLOAT3 forward = transform->GetForward();
	DirectX::XMFLOAT3 look = DirectX::XMFLOAT3(transform->GetPosition().x + forward.x, transform->GetPosition().y + forward.y, transform->GetPosition().z + forward.z);
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

Transform* Camera::GetTransform()
{
	return transform;
}

void Camera::SetTransform(Transform *transform)
{
	this->transform = transform;
}

void Camera::SetFOV(float fov)
{
	if (fov <= 0.0f)
	{
		this->fov = 0.1f;
	}
	else
	{
		this->fov = fov;
	}
}

void Camera::SetAspectRatio(float aspectRatio)
{
	this->aspectRatio = aspectRatio;
}

void Camera::SetNearClippingPlane(float nearClippingPlane)
{
	this->nearClippingPlane = nearClippingPlane;

	if (this->nearClippingPlane < 0.01f)
	{
		this->nearClippingPlane = 0.01f;
	}
	/*else if (this->nearClippingPlane > farClippingPlane)
	{
		this->nearClippingPlane = farClippingPlane - 0.1f;
	}*/
}

void Camera::SetFarClippingPlane(float farClippingPlane)
{
	this->farClippingPlane = farClippingPlane;

	if (this->farClippingPlane < nearClippingPlane)
	{
		this->farClippingPlane = nearClippingPlane + 0.1f;
	}
}