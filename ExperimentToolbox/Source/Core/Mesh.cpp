#include <GL/glew.h>

#include "Debug.h"
#include "Mesh.h"

etb::Mesh::Mesh() : ebo(0), tbo(0), vbo(0), vao(0) {
}

etb::Mesh::~Mesh() {
	if (ebo == 0) return;

	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &tbo);
	glDeleteBuffers(1, &vbo);
	
	glDeleteVertexArrays(1, &vao);
}

void etb::Mesh::GenBuffers() {
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &tbo);
	glGenBuffers(1, &vbo);

	glGenVertexArrays(1, &vao);
}

void etb::Mesh::StoreData() {
	glBindVertexArray(vao);

	// Elements buffer
	if (elements.size()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(glm::u32vec3), &elements[0], GL_STATIC_DRAW);
	}

	// Vertex buffer
	if (vertex.size()) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}

	// Texture buffer
	if (uv.size()) {
		glBindBuffer(GL_ARRAY_BUFFER, tbo);
		glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);

		glTexCoordPointer(2, GL_FLOAT, sizeof(glm::vec2), (void*) 0);
	}
}

void etb::Mesh::BindBuffers() {
	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}