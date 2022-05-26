#pragma once

#include "Mesh.h"

namespace etb {
	class Primitives {
	public:
		static etb::Mesh quad;
		// static etb::Mesh Plane;
		static etb::Mesh cube;
		// static etb::Mesh Sphere;
		// static etb::Mesh Capsule;

		static void GeneratePrimitives();
	};
}

