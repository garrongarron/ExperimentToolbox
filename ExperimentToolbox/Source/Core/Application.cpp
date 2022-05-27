#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl.h>

#include "Application.h"

#include "Window.h"
#include "Graphics.h"
#include "Primitives.h"
#include "Time.h"
#include "EventSystem.h"

etb::Application::Application() {
	Window::Init();

	window = new Window("Title", 800, 600);

	Graphics::GL::Init();

	Primitives::GeneratePrimitives();
}

etb::Application::Application(const char* title, uint32_t width, uint32_t height) {
	Window::Init();

	window = new Window(title, width, height);

	Graphics::GL::Init();

	Primitives::GeneratePrimitives();
}

etb::Application::~Application() {
	delete window;
}

void etb::Application::Start() {
	bool isRunning = true;

	EventSystem::AddEventListener(EventType::Quit, [&](Event& e) {
		isRunning = false;
	});

	Time::Start();

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	while (isRunning) {
		Time::Tick();
		EventSystem::Poll();

		this->Update();

		Graphics::GL::Clear();
		this->Render();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window->sdlWindow);
		ImGui::NewFrame();

		this->GUI();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window->Swap();
	}

	delete window;
}
