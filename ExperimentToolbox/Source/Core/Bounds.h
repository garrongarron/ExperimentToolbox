#pragma once

#include <glm/glm.hpp>

namespace etb {
	class Bounds {
	public:
		Bounds();
		Bounds(glm::vec3 center, glm::vec3 size);

		bool Intersect(Bounds& bounds);


		void SetCenter(glm::vec3 center);
		inline glm::vec3 GetCenter()  { return center; }

		void SetSize(glm::vec3 size);
		inline glm::vec3 GetSize()    { return size; }

		inline glm::vec3 GetMin()     { return min; }

		inline glm::vec3 GetMax()     { return max; }

		void SetExtends(glm::vec3 extends);
		inline glm::vec3 GetExtends() { return extends; }

	private:
		glm::vec3 center;
		glm::vec3 size;
		glm::vec3 extends;
		glm::vec3 min;
		glm::vec3 max;
	};
}