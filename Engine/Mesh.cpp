#include "Mesh.h"

Mesh::Mesh()
{ }

Mesh::~Mesh()
{ }

Bounds3D& Mesh::GetBounds()
{
	return bounds;
}

std::vector<Vertex>& Mesh::GetVertices()
{
	return vertices;
}
std::vector<DWORD>& Mesh::GetIndices()
{
	return indices;
}

std::vector<Triangle>& Mesh::GetTriangles()
{
	return triangles;
}

std::string Mesh::GetPath()
{
	return path;
}

void Mesh::SetBounds()
{
	float minx = vertices[0].position.x, miny = vertices[0].position.y, minz = vertices[0].position.x;
	float maxx = vertices[0].position.x, maxy = vertices[0].position.y, maxz = vertices[0].position.x;

	for (int i = 1; i < vertices.size(); i++)
	{
		if (vertices[i].position.x < minx) { minx = vertices[i].position.x; }
		if (vertices[i].position.y < miny) { miny = vertices[i].position.y; }
		if (vertices[i].position.z < minz) { minz = vertices[i].position.z; }

		if (vertices[i].position.x > maxx) { maxx = vertices[i].position.x; }
		if (vertices[i].position.y > maxy) { maxy = vertices[i].position.y; }
		if (vertices[i].position.z > maxz) { maxz = vertices[i].position.z; }
	}

	bounds.SetXBounds(minx, maxx);
	bounds.SetYBounds(miny, maxy);
	bounds.SetZBounds(minz, maxz);
}

void Mesh::SetTriangles()
{
	for (int i = 0; i < indices.size(); i += 3)
	{
		DirectX::XMFLOAT3 pointA = DirectX::XMFLOAT3(vertices[indices[i]].position.x, vertices[indices[i]].position.y, vertices[indices[i]].position.z);
		DirectX::XMFLOAT3 pointB = DirectX::XMFLOAT3(vertices[indices[i + 1]].position.x, vertices[indices[i + 1]].position.y, vertices[indices[i + 1]].position.z);
		DirectX::XMFLOAT3 pointC = DirectX::XMFLOAT3(vertices[indices[i + 2]].position.x, vertices[indices[i + 2]].position.y, vertices[indices[i + 2]].position.z);

		Triangle triangle = Triangle(pointA, pointB, pointC);

		triangles.push_back(triangle);
	}
}

void Mesh::SetVertices(std::vector<Vertex>& vertices)
{
	this->vertices = vertices;
}
void Mesh::SetIndices(std::vector<DWORD>& indices)
{
	this->indices = indices;
}

void Mesh::SetPath(std::string path)
{
	this->path = path;
}
