#include "Camera.h"

Camera::Camera()
{ }

void Camera::Init()
{
	fov = 0.785398163f;
	aspectRatio = 1706.0f / 960.0f;
	nearClippingPlane = 0.1f;
	farClippingPlane = 100.0f;
}

DirectX::XMMATRIX& Camera::GetViewMatrix()
{
	DirectX::XMFLOAT3 position = transform->GetPosition();
	DirectX::XMFLOAT3 look = DirectX::XMFLOAT3(transform->GetPosition().x + transform->GetForward().x, transform->GetPosition().y + transform->GetForward().y, transform->GetPosition().z + transform->GetForward().z);
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

void Camera::SetFOV(float fov)
{
	this->fov = fov;
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
	else if (this->nearClippingPlane > farClippingPlane)
	{
		this->nearClippingPlane = farClippingPlane - 0.1f;
	}
}

void Camera::SetFarClippingPlane(float farClippingPlane)
{
	this->farClippingPlane = farClippingPlane;

	if (this->farClippingPlane < nearClippingPlane)
	{
		this->farClippingPlane = nearClippingPlane + 0.1f;
	}
}

std::string Camera::Export()
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();
	writer.Key("camera");
	writer.StartObject();
	writer.Key("fov");
	writer.Double(fov);
	writer.Key("nearClippingPlane");
	writer.Double(nearClippingPlane);
	writer.Key("farClippingPlane");
	writer.Double(farClippingPlane);
	writer.EndObject();
	writer.EndObject();

	return s.GetString();
}

void Camera::Import(std::string json)
{
	Document d;
	d.Parse(json.c_str());

	fov = d["camera"]["fov"].GetFloat();
	nearClippingPlane = d["camera"]["nearClippingPlane"].GetFloat();
	farClippingPlane = d["camera"]["farClippingPlane"].GetFloat();
}
