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
	// glDeleteBuffers(1, &nbo);
	
	glDeleteVertexArrays(1, &vao);
}

void etb::Mesh::GenBuffers() {
	glGenBuffers(1, &ebo);
	glGenBuffers(1, &tbo);
	glGenBuffers(1, &vbo);
	// glGenBuffers(1, &nbo);

	glGenVertexArrays(1, &vao);
}

void etb::Mesh::StoreData() {
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// Elements buffer
	if (elements.size()) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(glm::u32vec3), &elements[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	// Vertex buffer
	if (vertex.size()) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	}

	// Normal buffer
	if (normals.size()) {
		glBindBuffer(GL_ARRAY_BUFFER, nbo);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*) 0);
	}

	// Texture buffer
	if (uv.size()) {
		glBindBuffer(GL_ARRAY_BUFFER, tbo);
		glBufferData(GL_ARRAY_BUFFER, uv.size() * sizeof(glm::vec2), &uv[0], GL_STATIC_DRAW);

		glTexCoordPointer(2, GL_FLOAT, sizeof(glm::vec2), (void*) 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindVertexArray(0);
}

void etb::Mesh::BindBuffers() {
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, nbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
}