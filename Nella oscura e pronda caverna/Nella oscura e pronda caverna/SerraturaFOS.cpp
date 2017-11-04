#include "SerraturaFOS.h"


//angolo indica il punto di sblocco, la tolleranza quanto in su o in giù si può andare
SerraturaFOS::SerraturaFOS(double angolo, double tolleranza) : finestraSerratura(sf::VideoMode(400, 400, 32), "Serratura FOS", !sf::Style::Resize | sf::Style::Close)
{
	fontTesto.loadFromFile("arial.ttf");
	finestraSerratura.setFramerateLimit(60);
	this->angolo = angolo;
	this->tolleranza = tolleranza;
}


SerraturaFOS::~SerraturaFOS()
{
}

int SerraturaFOS::scassina()
{
	
	sf::Event evento;
	sf::Text testo;
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

			auto angoloCalcolato = prendiAngolo();
			stringa = "Angolo Calcolato="+std::to_string(angoloCalcolato)+"°";
			
			std::cout << std::endl<< angoloCalcolato << std::endl;
			if (tolleranza > abs(angoloCalcolato - angolo)) {
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
		finestraSerratura.display();
	}
	if (apribile)
	return 1;
	return 0;
}

double SerraturaFOS::prendiAngolo()
{
	sf::Vector2i posMouse = sf::Mouse::getPosition();;
	int dX = posMouse.x - (int)sf::VideoMode::getDesktopMode().width / 2;
	int dY = posMouse.y - (int)sf::VideoMode::getDesktopMode().height / 2;
	return atan2(dX, dY)*(180 / (4 * atan(1))) + 180;
}
