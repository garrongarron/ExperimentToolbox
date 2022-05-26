#pragma once

#include <random>

namespace etb {
	class Random {
	public:
		static int Range(int min, int max);

	private:
		std::random_device dev;
		std::mt19937 rng;

		Random();
		~Random();

		static Random* instance;

		static Random* GetInstance();
	};
}