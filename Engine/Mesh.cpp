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
}

void Mesh::SetVertices(std::vector<Vertex>& vertices)
{
	this->vertices = vertices;
}
void Mesh::SetIndices(std::vector<DWORD>& indices)
{
	this->indices = indices;
}
