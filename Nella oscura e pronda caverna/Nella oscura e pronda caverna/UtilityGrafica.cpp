#pragma once

#include <iostream>

#include "UtilityGrafica.h"
#include "sfml\Graphics.hpp"
#include "TextBox.h"
#include "Casella.h"
#include "Attore.h"


void UtilityGrafica:: windowRefresh(std::vector<Casella> pavimento)
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
			if (typeid( *(casella.getEntita()) ) == typeid(Protagonista)) {
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
  
	sf::RectangleShape underHP(sf::Vector2f(larghezza*32/3, 20));
	underHP.setFillColor(sf::Color(0xF4,0x43,0x36));
	underHP.setPosition(0, lunghezza * 32);
	window.draw(underHP);
	auto look = (double)(percHP*larghezza * 32) / (double)3;
	sf::RectangleShape overHP(sf::Vector2f(look, 20));
	overHP.setFillColor(sf::Color(0xd5,0x00,0x00));
	overHP.setPosition(0, lunghezza * 32);
	window.draw(overHP);

	sf::RectangleShape underSt(sf::Vector2f(larghezza * 32 / 3, 20));
	underSt.setFillColor(sf::Color(0x66, 0xBB, 0x6A));
	underSt.setPosition((larghezza * 32 / 3), lunghezza * 32);
	window.draw(underSt);
	sf::RectangleShape overSt(sf::Vector2f(percSt*larghezza * 32 / 3, 20));
	overSt.setFillColor(sf::Color(0x2E, 0x7D, 0x32));
	auto shm = (double)larghezza * (double)32 / (double)3;
	overSt.setPosition(shm, lunghezza * 32);
	window.draw(overSt);

	sf::RectangleShape underMa(sf::Vector2f(larghezza * 32 / 3, 20));
	underMa.setFillColor(sf::Color(0x64, 0xb5, 0xf6));
	underMa.setPosition((2 * larghezza * 32 / 3), lunghezza * 32);
	window.draw(underMa);
	sf::RectangleShape overMa(sf::Vector2f(percMa*larghezza * 32 / 3, 20));
	overMa.setFillColor(sf::Color(0x0d, 0x47, 0xa1));
	overMa.setPosition((2 * larghezza * 32 / 3), lunghezza * 32);
	window.draw(overMa);

	
	if (livelloPG > 1)
		messages.rect.setFillColor(sf::Color(0xb2, 0x22, 0x22, 0x99));

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

	//window.draw(messages.rect); // TextBox
	//window.draw(messages.text); // TextBox

	//auto look = messages.getText().getString().toAnsiString();
	
	window.draw(messages.rect);
	//window.draw(messages.text);

	//messages.view.setSize(messages.view.getSize().x, messages.text.getLocalBounds().height);
	window.setView(messages.view);
	window.draw(messages.text);
	window.setView(window.getDefaultView());

	window.display();
}

//CHECK Introduce refresh here (catena di eventi disastrosa)
sf::String UtilityGrafica::graphicInput(sf::RenderWindow& window, TextBox& messages)
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

void UtilityGrafica::windowMessageRefresh(TextBox messages)
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

void UtilityGrafica::windowRefresh2(sf::RenderWindow& window, TextBox messages)
{
	window.clear();
	window.setView(window.getDefaultView());

	//window.setView(messages.view);
	window.draw(messages.rect);
	window.draw(messages.text);

	window.setView(messages.view);
	window.display();
}
//TODO in tutte le funzioni modificate c'è da ottimizzare: guardare tutta la stringa ogni volta è costoso, inutile e lento
sf::String UtilityGrafica::graphicInput2( sf::String text )
{
	int larghezza = 20;
	int lunghezza = 10;
	int firstText = text.getSize();
	sf::RenderWindow window(sf::VideoMode(32 * larghezza, 32 * lunghezza, 32), "Input here", sf::Style::None);
	window.setFramerateLimit(60);

	sf::Event evento;
	
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		//err...
	}

	TextBox messages(text, font, larghezza * 32 -5, lunghezza * 32 -5);
	const int containerWidth = window.getSize().x*0.98;
	for (auto i = 0; i < text.getSize(); ++i)
	{
		if (messages.text.findCharacterPos(i).x > containerWidth)
		{
			auto str = messages.text.getString();
			str.insert(i, "\n");
			messages.text.setString(str);
		}
	}
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
						const int containerWidthNow = messages.rect.getSize().x;
						for (auto i = 0; i < text.getSize(); ++i)
						{
							if (messages.text.findCharacterPos(i).x*1.05 > containerWidthNow);
							{
								auto str = messages.text.getString();
								if (str[i + firstText] != '\n')
								str.insert(i+ firstText, "\n");
								messages.text.setString(str);
							}
						}
						messages.text.setString(messages.text.getString() + text); // Refresh
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
						auto biggest = 0;
						const int containerWidthNow = messages.rect.getSize().x;
						for (auto i = 0, accapoRecently=0; i < text.getSize(); ++i)
						{
							auto numero = messages.text.findCharacterPos(i+firstText).x*1.04;
							biggest = numero;
							if (numero > containerWidthNow)
							{
								auto str = messages.text.getString();
								if(str[i+firstText]!='\n')
								str.insert(i+firstText, "\n");
								std::string shm(str);
								messages.text.setString(str);
							}
						}
						biggest = 0;
						std::string shm(messages.text.getString());
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

void UtilityGrafica::popUp(sf::String text) {
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
	const int containerWidthNow = messages.rect.getSize().x;
	for (auto i = 0; i < text.getSize(); ++i)
	{
		auto numero = messages.text.findCharacterPos(i).x*1.04;
		if (numero > containerWidthNow) {
			auto str = messages.text.getString();
			
			if (str[i] != '\n')
				str.insert(i, "\n");
			messages.text.setString(str);
		}
	}
	std::string shm(messages.text.getString());
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
//Vita, Stamina, Magia
void UtilityGrafica::update(double a, double b, double c)
{
	this->percHP = a;
	this->percSt = b;
	this->percMa = c;
}

void UtilityGrafica::updateLevel(int livello)
{
	livelloPG = livello;
}

UtilityGrafica::UtilityGrafica(int lung, int larg, sf::Sprite tiles, sf::Sprite ogg, sf::Sprite prot, sf::Sprite enem, sf::Sprite scale) 
	: window(sf::VideoMode(32 * larg, 32 * lung + 20, 32), "Cartografia della mappa", !sf::Style::Resize | sf::Style::Close)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		//err...
	}
	messages = TextBox("", font, larg * 32, lung * 32, true);
	
	this->lunghezza = lung;
	this->larghezza = larg;
	this->tiles = tiles;
	this->ogg = ogg;
	this->prot = prot;
	this->enem = enem;
	this->scale = scale;

	window.setFramerateLimit(60);
}

UtilityGrafica::UtilityGrafica() 
{
}

UtilityGrafica::~UtilityGrafica()
{
}
