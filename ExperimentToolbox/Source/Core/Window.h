#pragma once

#include <SDL.h>
#include <iostream>
#include <glm/glm.hpp>

namespace etb {

	class Window
	{
	public:
		SDL_Window *sdlWindow;
		SDL_GLContext sdlGLContext;

		static void Init();

		Window(const std::string& title, uint32_t width, uint32_t height);
		~Window();

		void Swap();

		void SetTitle(const char* title);
		const char* GetTitle();

		void SetSize(uint32_t width, uint32_t height);
		glm::u32vec2 GetSize();
		
	private:
		uint32_t width;
		uint32_t height;
	};

}
