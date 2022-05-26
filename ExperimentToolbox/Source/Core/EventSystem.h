#pragma once

#include <functional>
#include <vector>
#include <map>
#include <SDL.h>

#include "KeyCode.h"

namespace etb {
	enum class EventType {
		// Game Loop
		Tick,

		// Window
		Quit,

		// Keyboard
		KeyDown,
		KeyUp,
		KeyPress,

		// Mouse
		MouseButtonDown,
		MouseButtonUp,
		MouseButtonPress,
	};

	class Event {
	public:
		KeyCode keyCode;
		uint32_t button;

	private:

	};

	class EventSystem
	{
	public:
		static void AddEventListener(EventType EventType, const std::function<void(etb::Event&)> callback);
		
		static void Poll();

	private:
		SDL_Event sdlEvent;

		std::map<EventType, std::vector<std::function<void(etb::Event&)>>> events;

		// Singleton

		static EventSystem* instance;

		EventSystem();
		~EventSystem();

		static EventSystem* GetInstance();
	};
}