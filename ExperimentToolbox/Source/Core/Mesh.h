#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace etb {

	class Mesh {
	public:
		std::vector<glm::vec3> vertex;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> uv;
		std::vector<glm::u32vec3> elements;

		Mesh();
		~Mesh();

		void GenBuffers();
		void StoreData();
		void BindBuffers();
		
	private:
		uint32_t vao; // Vertex Array
		uint32_t vbo; // Vertex Buffer
		uint32_t nbo; // Normal Buffer
		uint32_t tbo; // Texture Buffer
		uint32_t ebo; // Element Buffer	
	};

}