#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"

#include "Window.h"

etb::Window::Window(const std::string& title, uint32_t _width, uint32_t _height) : width(_width), height(_height) {
	sdlWindow = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		(int32_t)_width, (int32_t)_height,
		SDL_WINDOW_OPENGL
	);
	
	sdlGLContext = SDL_GL_CreateContext(sdlWindow);

	// Decide GL+GLSL versions
#ifdef __APPLE__
	// GL 3.2 Core + GLSL 150
	const char* glsl_version = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplSDL2_InitForOpenGL(sdlWindow, sdlGLContext);
	ImGui_ImplOpenGL3_Init();
}

etb::Window::~Window() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();

	ImGui::DestroyContext();

	SDL_GL_DeleteContext(sdlGLContext);
	SDL_DestroyWindow(sdlWindow);
	SDL_Quit();
}

void etb::Window::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return;
	}
}

void etb::Window::Swap() {
	SDL_GL_SwapWindow(sdlWindow);
}

void etb::Window::SetTitle(const char* title) {
	SDL_SetWindowTitle(sdlWindow, title);
}

const char* etb::Window::GetTitle() {
	return SDL_GetWindowTitle(sdlWindow);
}

void etb::Window::SetSize(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;

	SDL_SetWindowSize(sdlWindow, width, height);
}

glm::u32vec2 etb::Window::GetSize() {
	return glm::u32vec2(width, height);
}
