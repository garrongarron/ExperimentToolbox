#include "Bounds.h"

etb::Bounds::Bounds() {
}

etb::Bounds::Bounds(glm::vec3 c, glm::vec3 s) : center(c), size(s) {
}

bool etb::Bounds::Intersect(Bounds& b) {
	return	(min.x <= b.max.x && max.x >= b.min.x) &&
		(min.y <= b.max.y && max.y >= b.min.y) &&
		(min.z <= b.max.z && max.z >= b.min.z);
}

void etb::Bounds::SetCenter(glm::vec3 c) {
	center = c;

	extends = size / 2.0f;
	min = center - extends;
	max = center + extends;
}

void etb::Bounds::SetSize(glm::vec3 s) {
	size = s;

	extends = size / 2.0f;
	min = center - extends;
	max = center + extends;
}

void etb::Bounds::SetExtends(glm::vec3 e) {
	extends = e;

	size = extends * 2.0f;
	min = center - extends;
	max = center + extends;
}
