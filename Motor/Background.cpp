#include "Background.h"

Background::Background(string path) : path(path)
{
	textureID = ResourceManager::getTexture(path).id;
}

Background::~Background()
{
}

void Background::draw(SpriteBatch& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(-width/2, -height/2, width, height);
	spriteBatch.draw(destRect, uvRect, textureID, 0.0f, color);
}

void Background::setResolution(int width, int height)
{
	this->width = width;
	this->height = height;
}
