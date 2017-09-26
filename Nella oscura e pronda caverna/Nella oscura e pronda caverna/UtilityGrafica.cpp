#pragma once

#include <iostream>

#include "UtilityGrafica.h"
#include "sfml\Graphics.hpp"
#include "TextBox.h"
#include "Casella.h"
#include "Attore.h"


void windowRefresh(sf::RenderWindow& window, std::vector<Casella> pavimento, int larghezza, int lunghezza, sf::Sprite tiles, sf::Sprite ogg, sf::Sprite prot, sf::Sprite enem, TextBox messages, sf::Sprite scale )
{
	window.clear();
	window.setView(window.getDefaultView());
	
	//OPTIMIZE
	for (unsigned int i = 0; i < pavimento.size(); i++) {
		auto casella = pavimento.at(i);
		int a = i % larghezza, b = i / larghezza;
		tiles.setPosition((float)a * 32, (float)b * 32);
		tiles.setTextureRect(casella.getRectSprite());
		window.draw(tiles);
		if (casella.getEvento() == 1)//scale here
		{
			int a = i % larghezza, b = i / larghezza;
			scale.setPosition(a * 32, b * 32);
			scale.setTextureRect(sf::IntRect(0, 0, 32, 32));
			window.draw(scale);
		}
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

	//HACK non so' perché ma deve essere 1.05, mettici le mani te poi.
	const int containerWidth = messages.rect.getSize().x*1.05;
	for (auto i = 0; i < messages.text.getString().getSize(); ++i)
	{
		if (messages.text.findCharacterPos(i).x > containerWidth-5)
		{
			auto str = messages.text.getString();
			str.insert(i, "\n");
			messages.text.setString(str);
		}
	}

	auto look = messages.getText().getString().toAnsiString();
	
	window.draw(messages.rect);
	//window.draw(messages.text);

	//messages.view.setSize(messages.view.getSize().x, messages.text.getLocalBounds().height);
	window.setView(messages.view);
	window.draw(messages.text);
	window.setView(window.getDefaultView());
	window.display();
}

//CHECK Introduce refresh here (catena di eventi disastrosa)
sf::String graphicInput(sf::RenderWindow& window, TextBox& messages)
{
	bool input = false;
	sf::String text;
	sf::Event evento;
	while (input == false && window.isOpen())
	{
		while (window.waitEvent(evento) && input == false )
		{
			switch (evento.type)
			{
			case sf::Event::TextEntered:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) // evento.text.unicode == '\n' sf::Keyboard::Return
				{
					input = true;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
				{
					if (text.getSize() > 0)
					{
						text.erase(text.getSize() - 1);
						auto  tempStr = messages.text.getString();
						tempStr.erase(tempStr.getSize() - 1);
						messages.text.setString(tempStr);
						std::cout << (int)evento.text.unicode << std::endl;
					}
				}
				else
				{
					if (evento.text.unicode >= '0' && evento.text.unicode <= '9')
					{
						text += (char)evento.text.unicode;
						std::cout << (char)evento.text.unicode << std::endl;
						messages.text.setString(messages.text.getString() + text); // Refresh
						//windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages);
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

void windowMessageRefresh(sf::RenderWindow& window, TextBox messages)
{
	window.setView(window.getDefaultView());

	window.draw(messages.rect);
	auto strTemp = messages.text.getString();

	messages.text.setString("");
	window.draw(messages.text);

	messages.text.setString(strTemp);
	window.draw(messages.text);

	window.setView(messages.view);
	window.display();
}

void windowRefresh2(sf::RenderWindow& window, TextBox messages)
{
	window.clear();
	window.setView(window.getDefaultView());

	//window.setView(messages.view);
	window.draw(messages.rect);
	window.draw(messages.text);

	window.setView(messages.view);
	window.display();
}

sf::String graphicInput2( sf::String text )
{
	int larghezza = 20;
	int lunghezza = 10;

	sf::RenderWindow window(sf::VideoMode(32 * larghezza, 32 * lunghezza, 32), "Input here", sf::Style::None);
	window.setFramerateLimit(60);

	sf::Event evento;
	
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		//err...
	}
	TextBox messages(text, font, larghezza * 32 -5, lunghezza * 32 -5);

	windowRefresh2(window, messages);

	text = "";

	bool input = false;
	while (input == false && window.isOpen())
	{
		while (window.waitEvent(evento) && input == false)
		{
			switch (evento.type)
			{
			case sf::Event::TextEntered:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				{
					if (text.getSize() > 0)
					{
						input = true;
						window.close();
					}
					/*else
					{
						messages.text.setString(messages.text.getString() + "\n Inserisci un valore prima di premere Invio: ");
						windowRefresh2(window, messages);
					}*/
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) // CHECK Non prende il delete
				{
					if (text.getSize() > 0)
					{
						
						text.erase(text.getSize() - 1);

						auto  tempStr = messages.text.getString();
						tempStr.erase(tempStr.getSize() - 1);
						messages.text.setString(tempStr);

						std::cout << (int)evento.text.unicode << std::endl;
						windowRefresh2(window, messages);
					}
				}
				else
				{
					if ((evento.text.unicode > 31 && evento.text.unicode < 128) ) {
						text += (char)evento.text.unicode;
						std::cout << (char)evento.text.unicode << std::endl;
						messages.text.setString(messages.text.getString() + (char)evento.text.unicode);
						windowRefresh2(window, messages);
					}
				}
				break;

			case sf::Event::Closed:
				window.close();
				return sf::String();
			}

		}
	}
	std::cout << "->" << text.toAnsiString() <<std::endl;
	return text;
}

void popUp(sf::String text) {
	int larghezza = 20;
	int lunghezza = 10;

	sf::RenderWindow window(sf::VideoMode(32 * larghezza, 32 * lunghezza, 32), "Input here", sf::Style::None);
	window.setFramerateLimit(60);

	sf::Event evento;

	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		//err...
	}
	TextBox messages(text, font, larghezza * 32 - 5, lunghezza * 32 - 5);
	windowRefresh2(window, messages);

	bool input = false;
	while (input == false && window.isOpen())
	{
		while (window.waitEvent(evento))
		{
			if (evento.type == sf::Event::TextEntered)
				return;
		}
	}
}