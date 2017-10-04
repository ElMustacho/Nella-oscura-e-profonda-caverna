#include "pianoCavernaIsolaGrafica.h"
#include <iostream>

#include "MonsterFactory.h"
#include "SFML\Graphics.hpp"
#include "TextBox.h"
#include "UtilityGrafica.h"

int pianoCavernaIsolaGrafica::playPiano(char bloat)
{
	int spwTurni = 0;
	int totTurni = 0;
	bool a;
	if (bloat == 'y')
		a = true;
	else if (bloat == 'n')
		a = false;
	else {
		std::cout << "Bloat text? y/n: ";
		while (bloat != 'y'&&bloat != 'n')
			std::cin >> bloat;
		if (bloat == 'y')
			a = true;
		else
			a = false;
	}
	
	std::deque<std::shared_ptr<Entita>> turni;
	for each (auto it in entitaPresenti)
	{
		turni.push_back(it.first);
	}
	sf::RenderWindow window(sf::VideoMode(32 * larghezza, 32 * lunghezza, 32), "Cartografia della mappa", !sf::Style::Resize|sf::Style::Close);
	sf::Sprite tiles;
	tiles.setTexture(texturePavimento);
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
	sf::Texture scaleTexture;
	sf::Sprite scale;
	scaleTexture.loadFromFile("Tileset/Scale.png");
	scale.setTexture(scaleTexture);
	sf::Event evento;
	window.setFramerateLimit(60);

	
	sf::Font font;
	if ( !font.loadFromFile("arial.ttf") )
	{
		//sf::err() << "font error -> An error has occured during font loading from file"; //CHECK
	}

	TextBox messages("", font, larghezza * 32, lunghezza * 32, true);

	windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);

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

		if (spwTurni > 50 + rand() % 100) { //dopo ogni 50 turni arriva un ulteriore goblin puzzone, di sicuro dopo 150
			auto caselleOk = floodFill(getPositionOfPlayer());
			cood casellaSpawn;
			do //FIXME se non c'è nessuna casella libera sballo
				casellaSpawn = caselleOk[rand() % caselleOk.size()];
			while (!placeEntita(MonsterFactory::makeMon(), casellaSpawn));
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

		if (a)
    {
		  std::cout << "Adesso sta a " << attivo->getNome() << std::endl;
		  messages.text.setString( messages.text.getString() + "Adesso sta a " + attivo->getNome() + " \n"); // TextBox
		  /* Oi, funziona -ttebayo!*/
		  windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
		  /**/
    }
		

		auto posizioneAttivo = getPositionOfEntity(attivo);
		if (getPositionOfPlayer() != posizioneAttivo) {
			//HACK qui si muove e basta, ma poi dovrà decidere l'intelligenza artificiale dell'entità
			auto resultMovement = muoviEntita(posizioneAttivo, getPositionOfPlayer());
			if (resultMovement == 10) { //adiacente a personaggio
				cood lookAround(posizioneAttivo.first, posizioneAttivo.second);
				std::vector<cood> aroundMe;
				aroundMe.push_back(cood(lookAround.first++, lookAround.second++));
				aroundMe.push_back(cood(lookAround.first--, lookAround.second));
				aroundMe.push_back(cood(lookAround.first--, lookAround.second));
				aroundMe.push_back(cood(lookAround.first, lookAround.second--));
				aroundMe.push_back(cood(lookAround.first, lookAround.second--));
				aroundMe.push_back(cood(lookAround.first++, lookAround.second));
				aroundMe.push_back(cood(lookAround.first++, lookAround.second));
				aroundMe.push_back(cood(lookAround.first, lookAround.second++));
				for each (auto adj in aroundMe)
				{
					if (std::dynamic_pointer_cast<Protagonista>(pavimento.at(posizione(adj)).getEntita()) !=nullptr) //questa casella contiene un pg
					{
						auto value=scontro(adj, posizioneAttivo, messages);
						if (value == 2) {//ucciso il giocatore
							graphicInput2("Sei morto, cosa vuoi che sia scritto sulla tua lapide?\n");
							popUp("Sei morto, come puoi dire a qualcuno cosa vuoi sulla lapide adesso?");
							exit(EXIT_SUCCESS);
							break;
						}
					}
				}
			}
		}
		else {
			int resultPlayer;
			do {
				windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
				resultPlayer = playerAct(a, window, tiles, ogg, prot, enem, messages, scale);
				/* Oi, funziona -ttebayo!*/
				
				/**/
			} while (resultPlayer < 0);
			
			if (resultPlayer == 2) { //uscito dal piano con scale
				turni.clear();
				return 1;
				break;
			}
			if (resultPlayer == 3) { //uscita con disonore
				turni.clear();
				return 0;
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


pianoCavernaIsolaGrafica::pianoCavernaIsolaGrafica(int larghezza, int lunghezza, std::string posizioneFile, std::vector<std::shared_ptr<Oggetto>> oggettiPossibili, std::shared_ptr<Entita> player, std::vector<std::shared_ptr<Entita>> entitaGenerabili):pianoCavernaIsola(larghezza,lunghezza,oggettiPossibili,player, entitaGenerabili)
{
	sf::Image immagineDim;
	if (posizioneFile == "") {
		this->posizioneFile = "Tileset/FirstSeriousTile.png";
	}
	else
		this->posizioneFile = posizioneFile;
	texturePavimento.loadFromFile(this->posizioneFile);
	auto maxX = texturePavimento.getSize().x;
	auto maxY = texturePavimento.getSize().y;
	
	for (int i = 0; i < pavimento.size(); i++) {
		pavimento.at(i).setMaxxTexture(maxX);
		pavimento.at(i).setMaxyTexture(maxY);
		pavimento.at(i).chooseTile();
	}
	
}


int pianoCavernaIsolaGrafica::playerAct(bool a, sf::RenderWindow &window, sf::Sprite tiles, sf::Sprite ogg, sf::Sprite prot, sf::Sprite enem, TextBox& messages, sf::Sprite scale)
{
	if (a)
	{
		std::cout << std::endl << "Usa il tastierino numerico per muoverti, 5 per uscire, 0 per guardare a terra,p per raccogliere cio' che e' a terra, e per equipaggiare il primo oggetto nell'inventario nel posto dell'arma, k per suicidarsi, i per descrivere il proprio inventario: ";
		messages.text.setString(messages.text.getString() + "\nUsa il tastierino numerico per muoverti, 5 per uscire, 0 per guardare a terra, p per raccogliere cio' che e' a terra, e per equipaggiare, k per suicidarsi, i per descrivere il proprio inventario: ");
		windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
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

		window.waitEvent(evento);
		switch (evento.type) {
		case sf::Event::TextEntered: {
			azione = (char)evento.text.unicode;
			go = false;
			break;
		}
		case sf::Event::Closed:
			return 3;
		}
	}
	system("CLS");
	messages.text.setString(""); // TextBox
	windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
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
				windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
			}
			return 0;
		}
		else if (result == 2) {
			if (a)
			{
				std::cout << "Scontro!" << std::endl;
				messages.text.setString(messages.text.getString() + "Scontro!\n");
			}
			scontro(toPosizione, playerPos, messages);
			return 0;
			
		}
		else if (result == 100) {
			sf::Event premiY;
			std::cout << "Premi y per scalire le scale" << std::endl;
			messages.text.setString(messages.text.getString() + "Premi y per scalire le scale\n");
			windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
			while (window.waitEvent(premiY)) {
				if (premiY.type == sf::Event::TextEntered) {
					if ((char)premiY.text.unicode=='y') {
						return 2;
					}
					else
						return 0;
				}
			}
		}
		else {
			if (a)
			{
				std::cout << "Muoversi ha risposto " << result << std::endl;
				messages.text.setString(messages.text.getString() + "Muoversi ha risposto" + std::to_string(result) + "\n");
				windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
			}
			return -1;
		}
		return 0;

	}
	else {
		switch (azione) {
		case '5':
			return 3; //uscita con disonore
		case 's':
			scontro(playerPos, Danno(std::vector<double>{1}, 4000), messages);
			windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
			graphicInput2("Sei morto, cosa vuoi che sia scritto sulla tua lapide?\n");
			popUp("Sei morto, come puoi dire a qualcuno cosa vuoi sulla lapide adesso?");
			exit(EXIT_SUCCESS);
			break;
		case 'e':
			pavimento.at(posizione(playerPos)).getEntita()->equip(window, messages);
			windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
			break;
		case '0':
			std::cout << pavimento.at(posizione(getPositionOfPlayer())).descriviOggettiTerra();
			messages.text.setString(messages.text.getString() + pavimento.at(posizione(getPositionOfPlayer())).descriviOggettiTerra());
			windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
			return -1; // TextBox
		case 'p':
			pavimento.at(posizione(getPositionOfPlayer())).pickup();
			windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
			break;
		case 'i':
			std::cout << pavimento.at(posizione(playerPos)).getEntita()->describeInventario() << std::endl;
			messages.text.setString(messages.text.getString() + pavimento.at(posizione(playerPos)).getEntita()->describeInventario());
			windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
			return -1; // TextBox
		default:
			if (a)
			{
				std::cout << "Input non valido" << std::endl;
				messages.text.setString(messages.text.getString() + "Input non valido\n");
				windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
			}
			return -1; // TextBox
		}
	}
}
void pianoCavernaIsolaGrafica::stampaPianoSuFinestra()
{
	sf::Sprite tiles;
	tiles.setTexture(texturePavimento);
	sf::Texture protTexture;
	sf::Sprite prot;
	//TODOFAR quando avremo tanti oggetti e nemici le texture andranno caricate dinamicamente, e magari una volta sola
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
	sf::Texture scaleTexture;
	sf::Sprite scale;
	scaleTexture.loadFromFile("Tileset/Scale.png");
	scale.setTexture(scaleTexture);
	sf::RenderWindow window(sf::VideoMode(32 * larghezza, 32 * lunghezza, 32), "Cartografia della mappa");
	window.setFramerateLimit(60);
	while (window.isOpen()) {
		sf::Event evento;
		
		//OPTIMIZE
		for (unsigned int i = 0; i < pavimento.size(); i++) {
			auto casella = pavimento.at(i);
			int a = i % larghezza, b = i / larghezza;
			tiles.setPosition((float)a * 32, (float) b* 32);
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

		while (window.waitEvent(evento)) {
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


		//CHECK no messages?
		//windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages);

	}
}

pianoCavernaIsolaGrafica::~pianoCavernaIsolaGrafica()
{
}
