#include "Primitives.h"

#include "../Utils/Loaders/OBJLoader.h"

etb::Mesh etb::Primitives::quad;
etb::Mesh etb::Primitives::cube;

void etb::Primitives::GeneratePrimitives() {
	// Quad
	Primitives::quad.GenBuffers();

	Primitives::quad.vertex = {
		{-.5f, -.5f, 0},
		{-.5f,  .5f, 0},
		{ .5f, -.5f, 0},
		{ .5f,  .5f, 0},
	};
	Primitives::quad.normals = {
		{0, 0, -1},
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

	// Cube
	OBJFile file = OBJLoader::FromFile("Build-In/Models/Cube.obj");
	Primitives::cube = file.GetMesh("Cube");

	Primitives::cube.GenBuffers();
	Primitives::cube.StoreData();
}
