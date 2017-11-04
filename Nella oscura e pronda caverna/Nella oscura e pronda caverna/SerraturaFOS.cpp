#include "SerraturaFOS.h"


//angolo indica il punto di sblocco, la tolleranza quanto in su o in giù si può andare
SerraturaFOS::SerraturaFOS(double angolo, double tolleranzaAngolo, double distanza, double tolleranzaDistanza) : finestraSerratura(sf::VideoMode(800,600, 32), "Serratura FOS", !sf::Style::Resize | sf::Style::Close)
{
	fontTesto.loadFromFile("arial.ttf");
	finestraSerratura.setFramerateLimit(60);
	this->angolo = angolo;
	this->tolleranzaAngolo = tolleranzaAngolo;
	this->tolleranzaDistanza = tolleranzaDistanza;
	this->distanza = distanza;
}


SerraturaFOS::~SerraturaFOS()
{
}

int SerraturaFOS::scassina()
{
	
	sf::Event evento;
	sf::Text testo;
	sf::CircleShape shape(2);
	shape.setFillColor(sf::Color::Green);
	testo.setCharacterSize(24); 
	testo.setFillColor(sf::Color::Red);
	testo.setFont(fontTesto);
	std::string stringa;
	finestraSerratura.display();
	bool apribile = false;
	while (finestraSerratura.isOpen()) {
		while (finestraSerratura.pollEvent(evento))
		{
		switch (evento.type)
		{
		case sf::Event::LostFocus:
		case sf::Event::Closed:
			finestraSerratura.close();
			break;
		case sf::Event::TextEntered:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				finestraSerratura.close();
				break;
			}
		default:
			auto distanzaCalcolata = prendiDistanza();
			auto angoloCalcolato = prendiAngolo();
			stringa = "Angolo Calcolato= "+std::to_string(angoloCalcolato)+"°";
			stringa += "\nDistanza Calcolata= " + std::to_string(distanzaCalcolata) + "px";
			std::cout << std::endl<< angoloCalcolato << std::endl;
			if ((tolleranzaAngolo > abs(angoloCalcolato - angolo))&&(tolleranzaDistanza > abs (distanzaCalcolata-distanza))) {
				stringa += "\nOk\n";
				apribile = true;
			}
			else {
				stringa += "\nNope";
				apribile = false;
			}
			testo.setString(stringa);
			break;
		}
		}
		finestraSerratura.clear();
		finestraSerratura.draw(testo);
		shape.setPosition(400, 300);
		finestraSerratura.draw(shape);
		finestraSerratura.display();
	}
	if (apribile)
	return 1;
	return 0;
}

double SerraturaFOS::prendiAngolo()
{
	sf::Vector2i posMouse = sf::Mouse::getPosition();
	int dX = posMouse.x - (int)sf::VideoMode::getDesktopMode().width / 2;
	int dY = posMouse.y - (int)sf::VideoMode::getDesktopMode().height / 2;
	return atan2(dX, dY)*(180 / (4 * atan(1))) + 180;
}
//si intende dal centro dello schermo non la finestra.
//TODOFAR solo la finestra
double SerraturaFOS::prendiDistanza()
{
	sf::Vector2i posMouse = sf::Mouse::getPosition();
	int dX = posMouse.x - (int)sf::VideoMode::getDesktopMode().width / 2;
	int dY = posMouse.y - (int)sf::VideoMode::getDesktopMode().height / 2;
	return sqrt(dX * dX + dY * dY);
}
