#pragma once

#include <iostream>
#include <map>

namespace etb {
	class Shader {
		friend class Material;
	public:
		Shader();
		Shader(const char* path);
		~Shader();

		void LoadSources(const char* path);
		bool Compile();
		
		void LoadBinary(const char* path);
		void SaveBinary(const char* path);

	private:
		int32_t program;
		
		time_t fragMTime;
		time_t vertMTime;

		std::string path;

		std::string fragSource;
		std::string vertSource;

		void SetupHotReload();
	};
}