#pragma once

#include <iostream>

#include "UtilityGrafica.h"
#include "sfml\Graphics.hpp"
#include "TextBox.h"
#include "Casella.h"
#include "Attore.h"


void windowRefresh(sf::RenderWindow& window, std::vector<Casella> pavimento, int larghezza, int lunghezza, sf::Sprite tiles, sf::Sprite ogg, sf::Sprite prot, sf::Sprite enem, TextBox messages)
{
	window.clear();
	//OPTIMIZE
	for (unsigned int i = 0; i < pavimento.size(); i++) {
		auto casella = pavimento.at(i);
		int a = i % larghezza, b = i / larghezza;
		tiles.setPosition((float)a * 32, (float)b * 32);
		tiles.setTextureRect(casella.getRectSprite());
		window.draw(tiles);

		if (!casella.getOggetti().empty()) {
			int a = i % larghezza, b = i / larghezza;
			ogg.setPosition((float)a * 32, (float)b * 32);
			ogg.setTextureRect(sf::IntRect(0, 0, 32, 32));
			window.draw(ogg);
		}
		if (casella.getEntita() != nullptr) {
			if (typeid(*(casella.getEntita())) == typeid(Protagonista)) {
				int a = i % larghezza, b = i / larghezza;
				prot.setPosition((float)a * 32, (float)b * 32);
				prot.setTextureRect(sf::IntRect(0, 0, 32, 32));
				window.draw(prot);
			}
			else if (typeid(*(casella.getEntita())) == typeid(Attore)) {
				int a = i % larghezza, b = i / larghezza;
				enem.setPosition(a * 32, b * 32);
				enem.setTextureRect(sf::IntRect(0, 0, 32, 32));
				window.draw(enem);
			}
			else {
				std::cout << "WTF" << std::endl;
				messages.text.setString(messages.text.getString() + "WTF \n"); // TextBox
			}
		}
	}
	auto look = messages.getText().getString().toAnsiString();
	window.draw(messages.rect); // TextBox
	window.draw(messages.text); // TextBox

	window.display();
}

sf::String graphicInput(sf::RenderWindow& window, TextBox& messages)
{
	bool input = false;
	sf::String text;
	sf::Event evento;
	while (input == false && window.isOpen())
	{
		while (window.pollEvent(evento))
		{
			switch (evento.type)
			{
			case sf::Event::TextEntered:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) // evento.text.unicode == '\n' sf::Keyboard::Return
				{
					input = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Delete)) //
				{
					text.erase(text.getSize() - 1);
					auto  tempStr = messages.text.getString();
					tempStr.erase(tempStr.getSize() - 1);
					messages.text.setString(tempStr);
					std::cout << (int)evento.text.unicode << std::endl;
				}
				else
				{
					if (evento.text.unicode >= '0' && evento.text.unicode <= '9')
					{
						text += (char)evento.text.unicode;
						std::cout << (char)evento.text.unicode << std::endl;
						messages.text.setString(messages.text.getString() + text); // Refresh
					}
				}
				break;

			case sf::Event::Closed:
				window.close();
				return sf::String();
				break;
			}

		}
	}
	return text;
}