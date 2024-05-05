#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache()
{
}

TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(string texturePath)
{
	// Dos formas de crear un iterador
	/*map<string, GLTexture>::iterator it 
		= textureMap.find(texturePath);*/
	auto it = textureMap.find(texturePath);

	if (it == textureMap.end()) {
		GLTexture texture = ImageLoader::loadPng(texturePath);
		
		// Dos formas de insertar un elemento en un pair
		/*pair<string, GLTexture> newPair(texturePath, texture);
		textureMap.insert(newPair);*/
		textureMap[texturePath] = texture;
		return texture;
	}
	return it->second;
}
