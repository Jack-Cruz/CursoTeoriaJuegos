#pragma once
#include <string>
#include <glm/glm.hpp>
#include "SpriteBatch.h"
#include "ResourceManager.h"
using namespace std;

class Background
{
private:
	string path;
	int textureID;
	int width, height;
	Color color;
public:
	Background(string path);
	~Background();
	void draw(SpriteBatch& spriteBatch);
	void setResolution(int width, int height);
};
	
	
	

