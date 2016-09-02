#include "Mesh.h"

Mesh::Mesh()
{ }

Mesh::~Mesh()
{ }

std::vector<Vertex>& Mesh::GetVertices()
{
	return vertices;
}

std::vector<DWORD>& Mesh::GetIndices()
{
	return indices;
}

void Mesh::SetVertices(std::vector<Vertex>& vertices)
{
	this->vertices = vertices;
}

void Mesh::SetIndices(std::vector<DWORD>& indices)
{
	this->indices = indices;
}
