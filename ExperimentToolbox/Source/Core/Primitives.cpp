#include "Primitives.h"

etb::Mesh etb::Primitives::quad;

void etb::Primitives::GeneratePrimitives() {
	Primitives::quad.GenBuffers();

	Primitives::quad.vertex = {
		{-.5f, -.5f, 0},
		{-.5f,  .5f, 0},
		{ .5f, -.5f, 0},
		{ .5f,  .5f, 0},
	};
	Primitives::quad.uv = {
		{0, 1},
		{0, 0},
		{1, 1},
		{1, 0},
	};
	Primitives::quad.elements = {
		{1, 0, 2},
		{1, 2, 3}
	};

	Primitives::quad.StoreData();
}
