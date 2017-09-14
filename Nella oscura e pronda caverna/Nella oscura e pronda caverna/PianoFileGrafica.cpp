#include "PianoFileGrafica.h"
#include <string>
#include <vector>
#include "SFML\Graphics.hpp"

void PianoFileGrafica::stampaPianoSuFinestra()
{
	sf::Texture tileTexture;
	sf::Sprite tiles;
	tileTexture.loadFromFile("Tileset/SuperSimpleTileSet.png");
	tiles.setTexture(tileTexture);
	sf::Vector2i loadcounter = sf::Vector2i(0, 0);
	sf::RenderWindow window(sf::VideoMode(32 * larghezza, 32 * lunghezza, 32), "Cartografia della mappa");
	window.setFramerateLimit(60);
	while (window.isOpen()) {
		sf::Event evento;
		while (window.pollEvent(evento)) {
			switch (evento.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					window.close();
				}
				break;
			}
		}
		window.clear();
		for (unsigned int i = 0; i < pavimento.size(); i++) {
			if (pavimento.at(i).isMuro()) {
				int a = i % larghezza, b = i/larghezza;
				tiles.setPosition(a*32,b*32);
				tiles.setTextureRect(sf::IntRect(0, 0, 32, 32));
				window.draw(tiles);
			}
			else
			{
				int a = i % larghezza, b = i / larghezza;
				tiles.setPosition(a * 32, b * 32);
				tiles.setTextureRect(sf::IntRect(0, 32, 32, 32));
				window.draw(tiles);
			}
		}
		window.display();
	}
}

PianoFileGrafica::PianoFileGrafica(std::string posizione, bool successo):PianoFile(posizione, successo)
{
}


PianoFileGrafica::~PianoFileGrafica()
{
}
