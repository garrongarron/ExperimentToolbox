#include "Time.h"

float etb::Time::deltaTime = 0;
float etb::Time::playTime = 0;
etb::Time* etb::Time::instance = nullptr;

void etb::Time::Start()
{
    etb::Time::GetInstance()->start = std::chrono::high_resolution_clock::now();
}

void etb::Time::Tick()
{
    etb::Time* time = etb::Time::GetInstance();

    std::chrono::time_point<std::chrono::high_resolution_clock> now;
    now = std::chrono::high_resolution_clock::now();

    etb::Time::deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - time->start).count() / 1000000.0;

    etb::Time::playTime += etb::Time::deltaTime;

    time->start = std::chrono::high_resolution_clock::now();
}

etb::Time::Time()
{
}

etb::Time::~Time()
{
}

etb::Time* etb::Time::GetInstance()
{
    if (etb::Time::instance == nullptr) {
        etb::Time::instance = new etb::Time();
    }

    return etb::Time::instance;
}
