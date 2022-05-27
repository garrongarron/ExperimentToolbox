#include <iostream>
#include <SDL.h>

#include "KeyCode.h"
#include "Input.h"
#include "EventSystem.h"

etb::Input etb::Input::instance;

glm::vec2 etb::Input::GetMousePosition() {
    int x, y;
    SDL_GetMouseState(&x, &y);
    glm::vec2 pos(x, y);
    return pos;
}

void etb::Input::UpdateKeyState() {
    std::fill(instance.keyDownState, instance.keyDownState + 322 * sizeof(bool), false);
    std::fill(instance.keyUpState, instance.keyUpState + 322 * sizeof(bool), false);
}

etb::Input::Input() {
    keyDownState = new bool[322];
    keyUpState = new bool[322];
    keyPressState = new bool[322];

    std::fill(keyPressState, keyPressState + 322 * sizeof(bool), false);

    EventSystem::AddEventListener(EventType::KeyDown, [&](Event &e) {
        this->keyDownState[(uint32_t) e.keyCode] = true;
        this->keyPressState[(uint32_t) e.keyCode] = true;
    });
    
    EventSystem::AddEventListener(EventType::KeyUp, [&](Event &e) {
        this->keyPressState[(uint32_t) e.keyCode] = false;
        this->keyUpState[(uint32_t) e.keyCode] = true;
    });

    EventSystem::AddEventListener(EventType::Tick, [&](Event &e) {
        Input::UpdateKeyState();
    });
}

etb::Input::~Input() {
    delete[] keyDownState;
    delete[] keyUpState;
    delete[] keyPressState;
}
