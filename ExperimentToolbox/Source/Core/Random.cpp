#include "Random.h"

etb::Random* etb::Random::instance;

int etb::Random::Range(int min, int max) {
    std::uniform_int_distribution<std::mt19937::result_type> dist6(min, max);
    return dist6(Random::GetInstance()->rng);
}

etb::Random::Random() : rng(dev()) {
}

etb::Random::~Random() {
}

etb::Random* etb::Random::GetInstance() {
    if (Random::instance == nullptr) {
        Random::instance = new Random();
    }
    return Random::instance;
}
