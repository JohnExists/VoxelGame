#include "GLObject.h"

//////////////////////////////////
/*		Vertex Buffer Object	*/
//////////////////////////////////


VertexObject::VertexObject(std::vector<Quad>* quads)
{
	glGenBuffers(1, &data);

	this->use();
	if(&quads->at(0) != nullptr)
		glBufferData(
			GL_ARRAY_BUFFER,
			quads->size() * (sizeof(Quad)),
			&quads->at(0),
			GL_STATIC_DRAW
		);

}

void VertexObject::use()
{	
	glBindBuffer(GL_ARRAY_BUFFER, data);
}

void VertexObject::abandon()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//////////////////////////////////
/*	Vertex Array Object			*/
//////////////////////////////////

VertexArrayObject::VertexArrayObject(std::vector<Quad>* quads)
	: quads(quads)
{
	glGenVertexArrays(1, &data);
	this->use();
	vertexData = std::make_unique<VertexObject>(quads);
	this->link();
	this->abandon();
	vertexData->abandon();
}

void VertexArrayObject::use()
{
	glBindVertexArray(data);
}

void VertexArrayObject::abandon()
{
	glBindVertexArray(0);
}

void VertexArrayObject::draw()
{
	use();
	glDrawArrays(GL_TRIANGLES, 0, quads->size() * 6);
	abandon();
}

void VertexArrayObject::link()
{
	linkData(0, 3, (void*) 0);
	linkData(1, 1, (void*) offsetof(Vertex, blockFace));
	linkData(2, 2, (void*) offsetof(Vertex, texCoords));
}

void VertexArrayObject::linkData(int slot, int size, void* offset)
{
	glEnableVertexAttribArray(slot);
	glVertexAttribPointer(
		slot , size, GL_FLOAT, GL_FALSE, sizeof(Vertex), offset
	);

}