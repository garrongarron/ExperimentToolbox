#include <glm/glm.hpp>
#include "Graphics.h"

void etb::Graphics::DrawMesh(Mesh &mesh, Material& material, glm::vec3 position, glm::vec3 rotation) {
	glPushMatrix();
	
	// Position
	glTranslatef(position.x, position.y, position.z);

	// Rotation
	glRotatef(rotation.x, 1, 0, 0);
	glRotatef(rotation.y, 0, 1, 0);
	glRotatef(rotation.z, 0, 0, 1);

	glColor3f(1, 1, 1);

	// Use Material
	material.Use();

	// Draw

	mesh.BindBuffers();
	glDrawElements(GL_TRIANGLES, (GLsizei) mesh.elements.size() * 3, GL_UNSIGNED_INT, 0);
	
	glPopMatrix();
}

void etb::Graphics::GL::Init() {
	if (glewInit() != GLEW_OK) {
		Debug::Print("Glew Init Error");
	}

	glEnable(GL_MULTISAMPLE);
}

void etb::Graphics::GL::ClearColor(glm::vec3 color) {
	glClearColor(color.r, color.g, color.b, 1.0f);
}

void etb::Graphics::GL::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void etb::Graphics::GL::Viewport(float x, float y, float width, float height, float minDepth, float maxDepth) {
	glViewport(
		(GLint) x,
		(GLint) y,
		(GLint) width,
		(GLint) height
	);
}

void etb::Graphics::GL::Perspective(float fovy, float aspect, float zNear, float zFar) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(fovy, aspect, zNear, zFar);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void etb::Graphics::GL::Ortho(float left, float right, float bottom, float top, float zNear, float zFar) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(left, right, bottom, top, zNear, zFar);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glAlphaFunc(GL_GREATER, 0.5);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void etb::Graphics::GL::UseShader(int32_t program) {
	glUseProgram(program);
}

void etb::Graphics::GL::CullFace(bool mode) {
	if (mode) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);
}

int32_t etb::Graphics::GL::GetUniformLocation(int32_t program, const char* name) {
	return glGetUniformLocation(program, name);
}

void etb::Graphics::Draw::Circle2D(glm::vec3 color, glm::vec2 position, float radius, float stroke, glm::vec3 strokeColor) {
	static Shader cirlce2DShader("shaders/circle2d");
	static Material cirlce2DMaterial(&cirlce2DShader);

	cirlce2DMaterial.Use();
	cirlce2DMaterial.SetVector3("color", color);
	cirlce2DMaterial.SetVector3("strokeColor", strokeColor);
	cirlce2DMaterial.SetFloat("radius", radius * 2.0f);
	cirlce2DMaterial.SetFloat("stroke", stroke);
	DrawMesh(Primitives::quad, cirlce2DMaterial, glm::vec3(position, 0), { 0, 0, 0 });
}

void etb::Graphics::Draw::Vector2D(glm::vec3 color, glm::vec2 start, glm::vec2 dir) {
	glUseProgram(0);

	glDisable(GL_TEXTURE_2D);
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINES);
	glVertex2f(start.x, start.y);
	glVertex2f(start.x + dir.x, start.y + dir.y);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

void etb::Graphics::Draw::Bounds(glm::vec3 color, etb::Bounds bound) {
	glUseProgram(0);
	
	glDisable(GL_TEXTURE_2D);
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_LINES);
	{
		glm::vec3 min = bound.GetMin();
		glm::vec3 max = bound.GetMax();

		glVertex3f(min.x, min.y, min.z);
		glVertex3f(max.x, min.y, min.z);

		glVertex3f(min.x, min.y, min.z);
		glVertex3f(min.x, max.y, min.z);

		glVertex3f(min.x, min.y, min.z);
		glVertex3f(min.x, min.y, max.z);

		glVertex3f(max.x, max.y, max.z);
		glVertex3f(min.x, max.y, max.z);

		glVertex3f(max.x, max.y, max.z);
		glVertex3f(max.x, min.y, max.z);

		glVertex3f(max.x, max.y, max.z);
		glVertex3f(max.x, max.y, min.z);
	}
	glEnd();
	glEnable(GL_TEXTURE_2D);
}
