#include "Mesh.h"

//////////////////////////////////
/*		Public Functions		*/
//////////////////////////////////

Mesh::Mesh(
	const std::vector<Quad>	quads, 
	const Texture*			texture
) 
{
	this->quads		= quads;
	this->texture	= texture;
	this->quads.reserve(1000);
}

Mesh::Mesh(const Texture* texture)
{
	this->texture = texture;
	this->quads.reserve(1000);
}

bool Mesh::isLoaded() 
{
	return vao.get() == nullptr;
}

void Mesh::clearVertexObject() 
{
	vao.reset();
}

void Mesh::scale(float x, float y, float z)
{
	modelMatrix = glm::scale(modelMatrix, glm::vec3(x, y, z));
}

void Mesh::translate(float x, float y, float z)
{
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, y, z));
}

void Mesh::draw()
{
	if(quads.empty()) return;
	if(!vao) loadVertexObject();

	vao->draw();
}

void Mesh::loadVertexObject()
{
	if (quads.empty()) return;

	clearVertexObject();
	vao = std::make_unique<VertexArrayObject>(&this->quads);
}

std::vector<Quad>& Mesh::getQuads()
{
	return quads;
}

void Mesh::setModelMatrix(const glm::mat4 model)
{
	this->modelMatrix = model;
}

glm::mat4& Mesh::getModelMatrix()
{
	return modelMatrix;
}

