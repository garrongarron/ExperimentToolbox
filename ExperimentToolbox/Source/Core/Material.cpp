#include "Material.h"

etb::Material::Material() {
}

etb::Material::Material(Shader* shader) {
	SetShader(shader);
}

etb::Material::~Material() {
}

void etb::Material::Use() {
	glUseProgram(shader->program);
	samplerCount = 0;
}

void etb::Material::SetInt(const char* name, int value) {
	glUniform1i(
		Graphics::GL::GetUniformLocation(shader->program, name),
		value
	);
}

void etb::Material::SetFloat(const char* name, float value) {
	glUniform1f(
		Graphics::GL::GetUniformLocation(shader->program, name),
		value
	);
}

void etb::Material::SetVector2(const char* name, glm::vec2 value) {
	glUniform2f(
		Graphics::GL::GetUniformLocation(shader->program, name),
		value.x, value.y
	);
}

void etb::Material::SetVector3(const char* name, glm::vec3 value) {
	glUniform3f(
		Graphics::GL::GetUniformLocation(shader->program, name),
		value.x, value.y, value.z
	);
}

void etb::Material::SetSampler2D(const char* name, Texture texture) {
	glActiveTexture(GL_TEXTURE0 + samplerCount);

	// texture.BindTexture();

	// glUniform1i(name, samplerCount);

	samplerCount++;
}
