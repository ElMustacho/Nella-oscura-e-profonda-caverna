#include "PianoFileGrafica.h"
#include <string>
#include "SFML\Graphics.hpp"

void PianoFileGrafica::stampaPianoSuFinestra()
{
	sf::Texture tileTexture;
	sf::Sprite tiles;
	tileTexture.loadFromFile("SuperSimpleTileSet.png");
	tiles.setTexture(tileTexture);
	//HACK so a priori le dimensioni, devo arrivarci dinamicamente
	sf::Vector2i map[18][17];
	sf::Vector2i loadcounter = sf::Vector2i(0, 0);
	sf::RenderWindow window(sf::VideoMode(32 * 18, 32 * 17, 32), "Cartografia della mappa");

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
				tiles.setTextureRect(sf::IntRect(32, 32, 32, 32));
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
