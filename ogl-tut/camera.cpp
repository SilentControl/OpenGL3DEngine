#include "camera.h"
#include <SDL2\SDL_keyboard.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_keycode.h>
#include <iostream>

Camera::Camera()
{
	position = glm::vec3(0.0f, 4.0f, 0.0f);
	yaw = 0.0;
	pitch = 0.0;
	roll = 0.0;
}

void Camera::move()
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_W])
	{
		position.z -= 1.0f;
		std::cout << "NEAR!\n";
	}

	if (state[SDL_SCANCODE_S])
	{
		position.z += 1.0f;
		std::cout << "FAR!\n";
	}

	if (state[SDL_SCANCODE_A])
	{
		position.x -= 1.0f;
		std::cout << "LEFT!\n";
	}

	if (state[SDL_SCANCODE_D])
	{
		position.x += 1.0f;
		std::cout << "RIGHT!\n";
	}

	if (state[SDL_SCANCODE_Z])
	{
		position.y -= 1.0f;
		std::cout << "DOWN!\n";
	}

	if (state[SDL_SCANCODE_X])
	{
		position.y += 1.0f;
		std::cout << "UP!\n";
	}

	if (state[SDL_SCANCODE_Y])
	{
		yaw += 1.0f;
		std::cout << "YAW+\n";
	}

	if (state[SDL_SCANCODE_T])
	{
		yaw -= 1.0f;
		std::cout << "YAW-\n";
	}

	if (state[SDL_SCANCODE_P])
	{
		pitch += 1.0f;
		std::cout << "PITCH+\n";
	}

	if (state[SDL_SCANCODE_O])
	{
		pitch -= 1.0f;
		std::cout << "PITCH-\n";
	}

	if (state[SDL_SCANCODE_R])
	{
		roll += 1.0f;
		std::cout << "ROLL+\n";
	}

	if (state[SDL_SCANCODE_E])
	{
		roll -= 1.0f;
		std::cout << "PITCH-\n";
	}

}

Camera::~Camera()
{
}
