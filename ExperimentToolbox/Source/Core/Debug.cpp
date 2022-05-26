#include "Debug.h"
#include <SDL.h>

void etb::Debug::Print(const std::string & str)
{
	SDL_Log(str.c_str());
}