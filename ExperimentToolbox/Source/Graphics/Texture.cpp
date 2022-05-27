
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>

#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../Core/Debug.h"
#include "../IO/File.h"

#include "Texture.h"

etb::Texture::Texture(const std::string& path) {
	if (!File::Exists(path)) {
		Debug::Print("Image \"" + path + "\" does not exists");
	}

	LoadImage(path);
}

etb::Texture::~Texture() {
	glDeleteTextures(1, &texture);
}

void etb::Texture::LoadImage(const std::string& path) {
	uint32_t format = 0;

	int32_t w, h, n;
	uint8_t* image = stbi_load(path.c_str(), &w, &h, &n, 0);

	if (image == nullptr) {
		Debug::Print("Image \"" + path + "\" error on load (stbi_load)");
	}

	switch (n) {
	case 1: /* format = GL_GRAY; */ break;
	case 2: /* format = GL_GRAY; */ break;
	case 3: format = GL_RGB; break;
	case 4: format = GL_RGBA; break;
	default: break;
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, n, w, h, 0, format, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);

	delete image;

	width = w;
	height = h;
}
