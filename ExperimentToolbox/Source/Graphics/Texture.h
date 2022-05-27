#pragma once

#include <iostream>

namespace etb {
	
	class Texture {
	public:
		Texture(const std::string& path);
		~Texture();

		void LoadImage(const std::string& path);
		
		inline int32_t GetWidth() { return width; }
		inline int32_t GetHeight() { return height; }

	private:
		uint32_t texture;
		int32_t width;
		int32_t height;
	};

}