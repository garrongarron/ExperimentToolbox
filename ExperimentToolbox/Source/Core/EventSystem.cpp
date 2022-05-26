#include <backends/imgui_impl_sdl.h>

#include "EventSystem.h"
#include "KeyCode.h"

etb::EventSystem* etb::EventSystem::instance = nullptr;

void etb::EventSystem::AddEventListener(EventType eventType, const std::function<void(etb::Event&)> callback) {
	etb::EventSystem* eventSystem = etb::EventSystem::GetInstance();

	if (!eventSystem->events.count(eventType)) {
		eventSystem->events[eventType] = {};
	}
	
	eventSystem->events[eventType].push_back(callback);
}

void etb::EventSystem::Poll() {
	etb::EventSystem* eventSystem = etb::EventSystem::GetInstance();
	
	Event e;
	EventType type;
	
	while (SDL_PollEvent(&eventSystem->sdlEvent)) {
		ImGui_ImplSDL2_ProcessEvent(&eventSystem->sdlEvent);

		switch (eventSystem->sdlEvent.type) {
		// Window
		case SDL_QUIT:
			type = EventType::Quit;
			break;

		// Keyboard
		case SDL_KEYDOWN:
			type = EventType::KeyDown;
			e.keyCode = (KeyCode) eventSystem->sdlEvent.key.keysym.scancode;
			break;

		case SDL_KEYUP:
			type = EventType::KeyUp;
			e.keyCode = (KeyCode)eventSystem->sdlEvent.key.keysym.scancode;
			break;

		// Mouse
		case SDL_MOUSEBUTTONDOWN:
			type = EventType::MouseButtonDown;
			e.button = eventSystem->sdlEvent.button.button;
			break;

		case SDL_MOUSEBUTTONUP:
			type = EventType::MouseButtonUp;
			e.button = eventSystem->sdlEvent.button.button;
			break;

		default:
			continue;
			break;
		}

		if (eventSystem->events.count(type)) {
			for (auto& callback : eventSystem->events[type]) {
				callback(e);
			}
		}
	}

	type = EventType::Tick;

	if (eventSystem->events.count(type)) {
		for (auto& callback : eventSystem->events[type]) {
			callback(e);
		}
	}
}

etb::EventSystem::EventSystem() {
}

etb::EventSystem::~EventSystem() {
}

etb::EventSystem* etb::EventSystem::GetInstance()
{
	if (etb::EventSystem::instance == nullptr) {
		etb::EventSystem::instance = new etb::EventSystem();
	}

	return etb::EventSystem::instance;
}
