#pragma once

#include "Window.h"

namespace etb {
	class Application {
	public:
		Window* window;

		Application();
		Application(const char* title, uint32_t width, uint32_t height);

		~Application();

		void Start();

		virtual void Tick() {};

	private:
	};
}