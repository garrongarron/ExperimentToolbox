#pragma once

#include <chrono>

namespace etb {
	class Time {
	public:
		static float deltaTime;
		static float playTime;

		static void Start();
		static void Tick();

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start;

		static Time* instance;

		Time();
		~Time();

		static Time* GetInstance();
	};
}

