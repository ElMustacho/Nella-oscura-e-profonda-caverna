#include "pianoCavernaIsolaGrafica.h"
#include <iostream>


#include "SFML\Graphics.hpp"
#include "TextBox.h"
#include "UtilityGrafica.h"

int pianoCavernaIsolaGrafica::playPiano()
{
	int spwTurni = 0;
	int totTurni = 0;
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

	UtilityGrafica finestra(lunghezza, larghezza, tiles, ogg, prot, enem, scale);
	std::dynamic_pointer_cast<Protagonista>(entitaPresenti[0].first)->attachGraphic(&finestra);
	std::deque<std::shared_ptr<Entita>> turni;
	for each (auto it in entitaPresenti)
	{
		turni.push_back(it.first);
	}
	//sf::RenderWindow window(sf::VideoMode(32 * larghezza, 32 * lunghezza+20, 32), "Cartografia della mappa", !sf::Style::Resize|sf::Style::Close);
	sf::RenderWindow& window = finestra.getWindow();
	sf::Event evento;

	TextBox& messages = finestra.getTextBox();
	finestra.windowRefresh(pavimento);

	while (!turni.empty()) {

		//Here begins trouble
		while (window.pollEvent(evento)) 
		{
			switch (evento.type) 
			{
				case sf::Event::Closed:
					window.close();
					turni.clear();
					return 0;
					break;
				case sf::Event::MouseWheelScrolled:
					auto mouseMove = evento.mouseWheelScroll.delta;
					messages.text.move(0, mouseMove*10);
					finestra.windowRefresh(pavimento);
					break;
			}
		}

		if (spwTurni > 50 + rand() % 100) { //dopo ogni 50 turni arriva un ulteriore goblin puzzone, di sicuro dopo 150
			auto caselleOk = floodFill(getPositionOfPlayer());
			coord casellaSpawn;
			do //FIXME se non c'è nessuna casella libera sballo
				casellaSpawn = caselleOk[rand() % caselleOk.size()];
			while (!placeEntita(MonsterFactory::makeMonRand(), casellaSpawn));
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

		if (loquace)
		{
		  std::cout << "Adesso sta a " << attivo->getNome() << std::endl;
		  messages.text.setString( messages.text.getString() + "Adesso sta a " + attivo->getNome() + " \n"); // TextBox
		  finestra.windowRefresh(pavimento);
    }

		

		auto posizioneAttivo = getPositionOfEntity(attivo);
		if (getPositionOfPlayer() != posizioneAttivo) {
			//HACK qui si muove e basta, ma poi dovrà decidere l'intelligenza artificiale dell'entità
			auto resultMovement = muoviEntita(posizioneAttivo, getPositionOfPlayer());
			if (resultMovement == 10) { //adiacente a personaggio
				coord lookAround(posizioneAttivo.first, posizioneAttivo.second);
				std::vector<coord> aroundMe;
				aroundMe.push_back(coord(++lookAround.first, ++lookAround.second));
				aroundMe.push_back(coord(--lookAround.first, lookAround.second));
				aroundMe.push_back(coord(--lookAround.first, lookAround.second));
				aroundMe.push_back(coord(lookAround.first, --lookAround.second));
				aroundMe.push_back(coord(lookAround.first, --lookAround.second));
				aroundMe.push_back(coord(++lookAround.first, lookAround.second));
				aroundMe.push_back(coord(++lookAround.first, lookAround.second));
				aroundMe.push_back(coord(lookAround.first, ++lookAround.second));
				for each (auto adj in aroundMe)
				{
					if (std::dynamic_pointer_cast<Protagonista>(pavimento.at(posizione(adj)).getEntita()) !=nullptr) //questa casella contiene un pg
					{
						auto value=scontro(adj, posizioneAttivo, messages);
						if (value == 2) {//ucciso il giocatore
							finestra.graphicInput2("Sei morto, cosa vuoi che sia scritto sulla tua lapide?\n");
							finestra.popUp("Sei morto, come puoi dire a qualcuno cosa vuoi sulla lapide adesso?");
							exit(EXIT_SUCCESS);
							break;
						}
					}
				}
			}
		}
		else {
			int resultPlayer;
			std::dynamic_pointer_cast<Protagonista>(entitaPresenti[0].first)->regeneration();
			do {
				
				finestra.windowRefresh(pavimento);
				resultPlayer = playerAct(window, messages, finestra);
				
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


int pianoCavernaIsolaGrafica::playerAct(sf::RenderWindow &window, TextBox& messages, UtilityGrafica& finestra)
{
	if (loquace)
	{
		std::cout << std::endl << "Usa il tastierino numerico per muoverti, 5 per uscire, 0 per guardare a terra,p per raccogliere cio' che e' a terra, e per equipaggiare il primo oggetto nell'inventario nel posto dell'arma, k per suicidarsi, i per descrivere il proprio inventario: ";
		messages.text.setString(messages.text.getString() + "\nUsa il tastierino numerico per muoverti, 5 per uscire, 0 per guardare a terra, p per raccogliere cio' che e' a terra, e per equipaggiare, k per suicidarsi, i per descrivere il proprio inventario: ");
		finestra.windowRefresh(pavimento);
	} // TextBox
	char azione;

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
		case sf::Event::MouseWheelScrolled:
		{
			auto mouseMove = evento.mouseWheelScroll.delta;
			messages.text.move(0, mouseMove * 10);
			finestra.windowRefresh(pavimento);
			break;
		}
		case sf::Event::Closed:
			return 3;
		}
	}
	system("CLS");
	messages.text.setString(""); // TextBox
	//finestra.windowRefresh(window, pavimento, larghezza, lunghezza, tiles, ogg, prot, enem, messages, scale);
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
			if (loquace)
			{
				std::cout << "Ho provato a muovermi con successo." << std::endl;
				messages.text.setString(messages.text.getString() + "Ho provato a muovermi con successo.\n"); // TextBox
				finestra.windowRefresh(pavimento);
			}
			return 0;
		}
		else if (result == 2) {
			if (loquace)
			{
				std::cout << "Scontro!" << std::endl;
				messages.text.setString(messages.text.getString() + "Scontro!\n");
			}
			//Salvo prima l'esperienza che il nemico potrebbe offrire perché dopo potrebbe essere morto.
			auto maybeExperience = std::dynamic_pointer_cast<Attore>(pavimento.at(posizione(toPosizione)).getEntita())->getExperienceDrop();
			if (scontro(toPosizione, playerPos, messages) == 1) {
				std::dynamic_pointer_cast<Protagonista>(entitaPresenti[0].first)->guadagnaEsperienza(maybeExperience);
			}
			return 0;
			
		}
		
		else {
			if (loquace)
			{
				std::cout << "Muoversi ha risposto " << result << std::endl;
				messages.text.setString(messages.text.getString() + "Muoversi ha risposto" + std::to_string(result) + "\n");
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
			finestra.graphicInput2("Sei morto, cosa vuoi che sia scritto sulla tua lapide?\n");
			finestra.popUp("Sei morto, come puoi dire a qualcuno cosa vuoi sulla lapide adesso?");
			exit(EXIT_SUCCESS);
			break;
		case 'e':
			pavimento.at(posizione(playerPos)).getEntita()->equip(window, messages);
			break;
		case '0':
			std::cout << pavimento.at(posizione(getPositionOfPlayer())).descriviOggettiTerra();
			messages.text.setString(messages.text.getString() + pavimento.at(posizione(getPositionOfPlayer())).descriviOggettiTerra());
			return -1; // TextBox
		case 'p':
			pavimento.at(posizione(getPositionOfPlayer())).pickup();
			break;
		case '>':
			if (pavimento.at(posizione(getPositionOfPlayer())).getEvento() == 1) {
				return 2;
			}
			else
			{
				messages.text.setString(messages.text.getString() + "Non puoi salire le scale qui.\n");
				return -1;
			}
			break;
		case 'i':
			std::cout << pavimento.at(posizione(playerPos)).getEntita()->describeInventario() << std::endl;
			messages.text.setString(messages.text.getString() + pavimento.at(posizione(playerPos)).getEntita()->describeInventario());
			return -1; // TextBox
		default:
			if (loquace)
			{
				std::cout << "Input non valido" << std::endl;
				messages.text.setString(messages.text.getString() + "Input non valido\n");
				finestra.windowRefresh(pavimento);
			}
			return -1; // TextBox
		}
	}
}


pianoCavernaIsolaGrafica::~pianoCavernaIsolaGrafica()
{
}
