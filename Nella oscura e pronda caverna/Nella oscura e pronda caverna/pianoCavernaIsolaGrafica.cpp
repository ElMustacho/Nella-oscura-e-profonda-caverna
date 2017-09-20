#include "pianoCavernaIsolaGrafica.h"
#include <iostream>


#include "SFML\Graphics.hpp"
#include "TextBox.h"
#include "UtilityGrafica.h"

int pianoCavernaIsolaGrafica::playPiano()
{
	int spwTurni = 0;
	int totTurni = 0;
	bool a;
	char input = '1';
	std::cout << "Bloat text? y/n: ";
	while (input != 'y'&&input != 'n')
		std::cin >> input;
	if (input == 'y')
		a = true;
	else
		a = false;
	std::deque<std::shared_ptr<Entita>> turni;
	for each (auto it in entitaPresenti)
	{
		turni.push_back(it.first);
	}
	sf::RenderWindow window(sf::VideoMode(32 * larghezza, 32 * lunghezza, 32), "Cartografia della mappa");
	sf::Texture tileTexture;
	sf::Sprite tiles;
	tileTexture.loadFromFile(pavimento.at(0).getPathToFile());
	tiles.setTexture(tileTexture);
	sf::Texture protTexture;
	sf::Sprite prot;
	protTexture.loadFromFile("Tileset/PdiPersonaggio.png");
	prot.setTexture(protTexture);
	sf::Texture enemTexture;
	sf::Sprite enem;
	enemTexture.loadFromFile("Tileset/NdiNemico.png");
	enem.setTexture(enemTexture);
	sf::Texture oggTexture;
	sf::Sprite ogg;
	oggTexture.loadFromFile("Tileset/OdiOggetto.png");
	ogg.setTexture(oggTexture);
	sf::Event evento;
	window.setFramerateLimit(60);

	
	sf::Font font;
	if ( !font.loadFromFile("arial.ttf") )
	{
		//sf::err() << "font error -> An error has occured during font loading from file"; //CHECK
	}

	TextBox messages("Omae Wa Mou Shindeiru \n cucaracia\n", font, larghezza * 32, lunghezza * 32, true);

	while (!turni.empty()) {
		//Here begins trouble
		while (window.pollEvent(evento)) {
			switch (evento.type) {
			case sf::Event::Closed:
				window.close();
				turni.clear();
				return 0;
				break;
			}
		}

		windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages);
		

		if (spwTurni > 50 + rand() % 100) { //dopo ogni 50 turni arriva un ulteriore goblin puzzone, di sicuro dopo 150
			auto caselleOk = floodFill(getPositionOfPlayer());
			cood casellaSpawn;
			do //FIXME se non c'è nessuna casella libera sballo
				casellaSpawn = caselleOk[rand() % caselleOk.size()];
			while (!placeEntita(entityFactory(1), casellaSpawn));
			auto smt = pavimento.at(posizione(casellaSpawn)).getEntita();
			turni.push_back(smt);
			auto nomeDaDare = smt->getNome();
			nomeDaDare.append(" arrivato al turno " + std::to_string(totTurni));
			smt->setNome(nomeDaDare);
			spwTurni = 0;
		}
		auto attivo = turni.front();
		turni.pop_front();
		if (pavimento.at(posizione(getPositionOfEntity(attivo))).getEntita() == nullptr) { //

			continue;
		}
		std::cout << "Adesso sta a " << attivo->getNome() << std::endl; // TextBox
		messages.text.setString( messages.text.getString() + "Adesso sta a " + attivo->getNome() + " \n"); // TextBox
		
		/* Oi, funziona -ttebayo!*/
		windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages);
		/**/

		
		auto posizioneAttivo = getPositionOfEntity(attivo);
		if (getPositionOfPlayer() != posizioneAttivo) {
			//HACK qui si muove e basta, ma poi dovrà decidere l'intelligenza artificiale dell'entità
			auto resultMovement = muoviEntita(posizioneAttivo, getPositionOfPlayer());
		}
		else {
			int resultPlayer;
			do {
				resultPlayer = playerAct(a, window, messages);
				/* Oi, funziona -ttebayo!*/
				windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages);
				/**/
			} while (resultPlayer < 0);
			
			if (resultPlayer == 2) {
				turni.clear();
				break;
			}
			spwTurni++;
			totTurni++;
		}
		turni.push_back(attivo);
	}
	window.close();
	return 0;
}


pianoCavernaIsolaGrafica::pianoCavernaIsolaGrafica(int larghezza, int lunghezza):pianoCavernaIsola(larghezza,lunghezza)
{
}

int pianoCavernaIsolaGrafica::playerAct(bool a, sf::RenderWindow &window, TextBox& messages)
{
	if (a)
	{
		std::cout << std::endl << "Usa il tastierino numerico per muoverti, 5 per uscire, 0 per guardare a terra,p per raccogliere cio' che e' a terra, e per equipaggiare il primo oggetto nell'inventario nel posto dell'arma, k per suicidarsi, i per descrivere il proprio inventario: ";
		messages.text.setString( messages.text.getString() + "\nUsa il tastierino numerico per muoverti, 5 per uscire, 0 per guardare a terra,p per raccogliere cio' che e' a terra, e per equipaggiare il primo oggetto nell'inventario nel posto dell'arma, k per suicidarsi, i per descrivere il proprio inventario: ");
	} // TextBox
	
	char azione;
	/*std::cin >> azione;
	std::cout << std::endl;*/
	
	auto playerPos = getPositionOfPlayer();
	auto toPosizione = playerPos;
	int result;
	sf::Event evento;
	bool go = true;
	while (go) {
		sf::sleep(sf::milliseconds(20));
		window.pollEvent(evento);
		switch (evento.type) {
		case sf::Event::TextEntered: {
			azione = (char)evento.text.unicode;
			go=false;
			break;
		}
		}
	}
	system("CLS");
	messages.text.setString(""); // TextBox
	switch (azione) {
		case '1':
			toPosizione.first--;
			toPosizione.second++;
			break;
		case '2':
			toPosizione.second++;
			break;
		case '3':
			toPosizione.first++;
			toPosizione.second++;
			break;
		case '4':
			toPosizione.first--;
			break;
		case '6':
			toPosizione.first++;
			break;
		case '7':
			toPosizione.first--;
			toPosizione.second--;
			break;
		case '8':
			toPosizione.second--;
			break;
		case '9':
			toPosizione.first++;
			toPosizione.second--;
			break;
		}
		if (playerPos != toPosizione) //L'azione scelta è un movimento
		{
			result = muoviEntita(playerPos.first, playerPos.second, toPosizione.first, toPosizione.second);
			if (result == 0) {
				if (a) 
				{
					std::cout << "Ho provato a muovermi con successo." << std::endl;
					messages.text.setString(messages.text.getString() + "Ho provato a muovermi con successo.\n"); // TextBox
				} // TextBox
				return 0;
			}
			else if (result == 2) {
				if (a)
				{
					std::cout << "Scontro!" << std::endl;
					messages.text.setString(messages.text.getString() + "Scontro!\n"); // TextBox
				}
					
				scontro(toPosizione, playerPos, messages);
				return 0;
			}
			else {
				if (a)
				{
					std::cout << "Muoversi ha risposto " << result << std::endl;
					messages.text.setString(messages.text.getString() + "Muoversi ha risposto" + std::to_string(result) + "\n");
				} // TextBox
					
				return -1;
			}
		}
		else {
			switch (azione) {
			case '5':
				return 2;
			case 's':
				scontro(playerPos, Danno(std::vector<double>{1}, 4000), messages);
				break;
			case 'e':
				pavimento.at(posizione(playerPos)).getEntita()->equip(window, messages);
				break;
			case '0':
				std::cout << pavimento.at(posizione(getPositionOfPlayer())).descriviOggettiTerra();
				messages.text.setString(messages.text.getString() + pavimento.at(posizione(getPositionOfPlayer())).descriviOggettiTerra() );
				return -1; // TextBox
			case 'p':
				pavimento.at(posizione(getPositionOfPlayer())).pickup();
				break;
			case 'i':
				std::cout << pavimento.at(posizione(playerPos)).getEntita()->describeInventario() << std::endl;
				messages.text.setString(messages.text.getString() + pavimento.at(posizione(playerPos)).getEntita()->describeInventario() );
				return -1; // TextBox
			default:
				if (a)
				{
					std::cout << "Input non valido" << std::endl;
					messages.text.setString(messages.text.getString() + "Input non valido\n");
				} 
				return -1; // TextBox
			}
		}
	
	return 0;

}


void pianoCavernaIsolaGrafica::stampaPianoSuFinestra()
{
	sf::Texture tileTexture;
	sf::Sprite tiles;
	tileTexture.loadFromFile(pavimento.at(0).getPathToFile());
	tiles.setTexture(tileTexture);
	sf::Texture protTexture;
	sf::Sprite prot;
	protTexture.loadFromFile("Tileset/PdiPersonaggio.png");
	prot.setTexture(protTexture);
	sf::Texture enemTexture;
	sf::Sprite enem;
	enemTexture.loadFromFile("Tileset/NdiNemico.png");
	enem.setTexture(enemTexture);
	sf::Texture oggTexture;
	sf::Sprite ogg;
	oggTexture.loadFromFile("Tileset/OdiOggetto.png");
	ogg.setTexture(oggTexture);
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
		//OPTIMIZE
		for (unsigned int i = 0; i < pavimento.size(); i++) {
			auto casella = pavimento.at(i);
			int a = i % larghezza, b = i / larghezza;
			tiles.setPosition((float)a * 32, (float) b* 32);
			tiles.setTextureRect(casella.getRectSprite());
			window.draw(tiles);
			
			if (!pavimento.at(i).getOggetti().empty()) {
				int a = i % larghezza, b = i / larghezza;
				ogg.setPosition((float)a * 32, (float)b * 32);
				ogg.setTextureRect(sf::IntRect(0, 0, 32, 32));
				window.draw(ogg);
			}
			if (pavimento.at(i).getEntita() != nullptr) {
				if (typeid(*(pavimento.at(i).getEntita())) == typeid(Protagonista)) {
					int a = i % larghezza, b = i / larghezza;
					prot.setPosition((float)a * 32, (float)b * 32);
					prot.setTextureRect(sf::IntRect(0, 0, 32, 32));
					window.draw(prot);
				}
				else if (typeid(*(pavimento.at(i).getEntita())) == typeid(Attore)) {
					int a = i % larghezza, b = i / larghezza;
					enem.setPosition((float)a * 32, (float)b * 32);
					enem.setTextureRect(sf::IntRect(0, 0, 32, 32));
					window.draw(enem);
				}
				else {
					std::cout << "WTF" << std::endl;
				}
			}
			}
		window.display();

		//CHECK no messages?
		//windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages);
	}
}

pianoCavernaIsolaGrafica::~pianoCavernaIsolaGrafica()
{
}
