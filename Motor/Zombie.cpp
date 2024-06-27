#include "Zombie.h"
#include <random>
#include <ctime>
#include<glm/gtx/rotate_vector.hpp>

Zombie::Zombie()
{
}

Zombie::~Zombie()
{
}

void Zombie::init(float speed, glm::vec2 position)
{
	this->speed = speed;
	this->position = position;
	color.set(0, 255, 0, 255);

	std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randDir(-1.0f, 1.0f);
	direction = glm::vec2(randDir(randomEngine), randDir(randomEngine));
	if (direction.length() == 0) {
		direction = glm::vec2(1.0f, 1.0f);
	} 

}

void Zombie::update(vector<string>& levelData, vector<Human*>& humans, vector<Zombie*>& zombies)
{
	collideWithLevel(levelData);
	Human* closeHuman = getNearestHuman(humans);
	if (closeHuman != nullptr) {
		glm::vec2 direction = glm::normalize(
			closeHuman->getPosition() - position
		);
		position += direction * speed;
	}
	/*std::mt19937 randomEngine(time(nullptr));
	std::uniform_real_distribution<float>randRotate(-60.0f, 60.0f);
	
	position += direction * speed;
	if (collideWithLevel(levelData)) {
		direction = glm::rotate(direction, randRotate(randomEngine));
	}*/
}

Human* Zombie::getNearestHuman(vector<Human*>& humans)
{
	Human* closeHuman = nullptr;
	float smallestDistance = 8888888888.0f;
	for (size_t i = 0; i < humans.size(); i++)
	{
		glm::vec2 dist = humans[i]->getPosition() - position;
		float distance = glm::length(dist);
		if (distance < smallestDistance) {
			smallestDistance = distance;
			closeHuman = humans[i];
		}
	}
	return closeHuman;
}
