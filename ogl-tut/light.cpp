#include "light.h"
#include <SDL2\SDL.h>
#include <iostream>

Light::~Light()
{
}

void Light::move()
{
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_U])
		{
			position.y += 0.02f;
			std::cout << "UP!\n";
			std::cout << "x y z: " << position.x << position.y << position.z << "\n";
		}

		if (state[SDL_SCANCODE_J])
		{
			position.y -= 0.02f;
			std::cout << "DOWN!\n";
			std::cout << "x y z: " << position.x << position.y << position.z << "\n";
		}

		if (state[SDL_SCANCODE_K])
		{
			position.x -= 0.02f;
			std::cout << "LEFT!\n";
			std::cout << "x y z: " << position.x << position.y << position.z << "\n";
		}

		if (state[SDL_SCANCODE_L])
		{
			position.x += 0.02f;
			std::cout << "RIGHT!\n";
			std::cout << "x y z: " << position.x << position.y << position.z << "\n";
		}

		if (state[SDL_SCANCODE_O])
		{
			position.z -= 0.02f;
			std::cout << "FAR!\n";
			std::cout << "x y z: " << position.x << position.y << position.z << "\n";
		}

		if (state[SDL_SCANCODE_P])
		{
			position.z += 0.02f;
			std::cout << "NEAR!\n";
			std::cout << "x y z: " << position.x << position.y << position.z << "\n";
		}

}