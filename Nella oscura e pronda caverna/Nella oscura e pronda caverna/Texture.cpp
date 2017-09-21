#include "Texture.h"

//In una mossa sistemo 2 variabili
Texture::Texture(std::string path, int beginX, int beginY, int endX, int endY)
{
	this->textureOk=this->texture.loadFromFile(path);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(beginX,beginY,endX,endY));
}

Texture::Texture() {
	this->textureOk = false;
}

Texture::~Texture()
{
}
