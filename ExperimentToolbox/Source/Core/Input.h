#pragma once

#include <cstdint>
#include <glm/glm.hpp>

#include "KeyCode.h"

namespace etb {
	class Input {
	public:
		inline static bool KeyUp(KeyCode keyCode) {
			return instance.keyUpState[(uint8_t)keyCode];
		};

		inline static bool KeyDown(KeyCode keyCode) {
			return instance.keyDownState[(uint8_t)keyCode];
		};

		inline static bool KeyPressed(KeyCode keyCode) {
			return instance.keyPressState[(uint8_t)keyCode];
		};

		static glm::vec2 GetMousePosition();

	private:
		bool* keyPressState;
		bool* keyUpState;
		bool* keyDownState;

		static void UpdateKeyState();

		Input();
		~Input();

		static Input instance;
	};
}
