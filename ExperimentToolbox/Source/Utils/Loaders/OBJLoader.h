#pragma once

#include <map>
#include <string>

#include "../../Core/Mesh.h"

namespace etb {
	class OBJFile {
	public:
		OBJFile(const std::string& path);
		~OBJFile();

		Mesh GetMesh(const std::string& name);

	private:
		std::string path;
		std::string source;
	};

	class OBJLoader {
	public:
		static inline OBJFile FromFile(const std::string& path) { return OBJFile(path); }
	};

}