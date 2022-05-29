#pragma once

#include "../Graphics/Texture.h"
#include "../Etb.h"

namespace etb {
	class Material {
	public:
		Material();
		Material(Shader* shader);
		~Material();

		void Use();

		inline void SetShader(Shader* shader) { this->shader = shader; };

		// Uniforms
		void SetInt(const char* name, int value);
		void SetFloat(const char* name, float value);
		void SetVector2(const char* name, glm::vec2 value);
		void SetVector3(const char* name, glm::vec3 value);
		void SetSampler2D(const char* name, Texture texture);

	private:
		Shader* shader;
		uint32_t samplerCount;
	};
}