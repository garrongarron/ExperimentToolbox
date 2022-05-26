#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include "KeyCode.h"

namespace etb {
	class Input {
	public:
		inline static bool KeyUp(KeyCode keyCode) {
			return Input::GetInstance()->keyUpState[(uint8_t)keyCode];
		};

		inline static bool KeyDown(KeyCode keyCode) {
			return Input::GetInstance()->keyDownState[(uint8_t)keyCode];
		};

		inline static bool KeyPressed(KeyCode keyCode) {
			return Input::GetInstance()->keyPressState[(uint8_t)keyCode];
		};

		static glm::vec2 GetMousePosition();
		
		static void UpdateKeyState();

	private:
		bool* keyPressState;
		bool* keyUpState;
		bool* keyDownState;

		static Input* instance;

		Input();
		~Input();

		static Input* GetInstance();
	};
}
