#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Material.h"
#include "Mesh.h"
#include "Bounds.h"

namespace etb {
	namespace Graphics {

		void DrawMesh(Mesh& mesh, glm::vec3 position, glm::vec3 rotation);

		namespace Draw {
			void Circle2D(glm::vec3 color, glm::vec2 position, float radius, float stroke = 1.0f, glm::vec3 strokeColor = { 0, 0, 0 });
			void Vector2D(glm::vec3 color, glm::vec2 start, glm::vec2 dir);
			void Bounds(glm::vec3 color, etb::Bounds bound);
		}

		namespace GL { // Abstraction of Graphic Language
			void Init();
			void ClearColor(glm::vec3 color);
			void Clear();
			void Viewport(float x, float y, float width, float height, float minDepth, float maxDepth);
			
			void Perspective(float fovy, float aspect, float zNear, float zFar);
			void Ortho(float left, float right, float bottom, float top, float zNear, float zFar);

			void UseShader(int32_t program);
			void CullFace(bool mode);
			int32_t GetUniformLocation(int32_t program, const char* name);
		}
	}
}