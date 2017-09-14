#pragma once
#include "SFML\Graphics.hpp"
#include <string>
class Texture
{

public:
	Texture();
	Texture(std::string path, int beginX, int beginY, int endX, int endY);
	~Texture();

private:
	sf::Texture texture; 
	sf::Sprite sprite;
	bool textureOk;
};

