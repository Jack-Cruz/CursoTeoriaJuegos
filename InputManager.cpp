#include "InputManager.h"

void InputManager::setMouseCoords(float x, float y)
{
	mouseCoords.x = x;
	mouseCoords.y = y;
}

void InputManager::pressKeys(unsigned int keyCode)
{
	keys[keyCode] = true;
}

void InputManager::releaseKeys(unsigned int keyCode)
{
	keys[keyCode] = false;
}

bool InputManager::isKeyPressed(unsigned int keyCode)
{
	auto it = keys.find(keyCode);
	if (it != keys.end()) {
		return it->second;
	}
	return false;
}

InputManager::InputManager():mouseCoords(0.0f, 0.0f)
{

}

InputManager::~InputManager()
{
}
