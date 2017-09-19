#pragma once

#include <iostream>

#include "sfml\Graphics.hpp"
#include "TextBox.h"
#include "Casella.h"
#include "Attore.h"

void windowRefresh(sf::RenderWindow& window, std::vector<Casella> pavimento, int larghezza, int lunghezza, sf::Sprite tiles, sf::Sprite ogg, sf::Sprite prot, sf::Sprite enem, TextBox messages);
void windowRefresh2(sf::RenderWindow& window, TextBox mesagges);

sf::String graphicInput(sf::RenderWindow& window, TextBox& messages);

sf::String graphicInput2(sf::String text);