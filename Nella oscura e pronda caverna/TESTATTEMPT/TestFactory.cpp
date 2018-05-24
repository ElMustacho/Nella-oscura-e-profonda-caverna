#include "stdafx.h"

TEST(TestFactory, TestMonsterFactory) {
	std::cout << "Test sulla creazione di entità con Monster Factory,\n";
	// Da qui fino al prossimo commento è solo fase di preparazione
	Attributi casuale(true), manuale(4, 4, 4, 4, 4, 4, 4, 10);
	Equipaggiamento inventario1, inventario2;
	std::vector<std::shared_ptr<Oggetto>> lista1, lista2;
	Oggetto oggettoTest1(0.1,"\"Esci gratis di prigione\"","L'utilissimo cartoncino del Monopoli",2000), oggettoTest2(1,"Pettine","Per la cura dei capelli ed altri tipi di pelurie",5);
	Attore scelta1("Abramo",lista1,casuale,inventario1,5), scelta2("Lincoln",lista2,manuale,inventario2,20);
	auto punt1 = std::make_shared<Attore>(scelta1), punt2 = std::make_shared<Attore>(scelta2);
	std::vector<std::shared_ptr<Entita>> elencoAttori;
	elencoAttori.push_back(punt1);
	elencoAttori.push_back(punt2);
	MonsterFactory monFactTest(elencoAttori);
	auto monMade1 = monFactTest.makeMon(0);
	auto monMade2 = monFactTest.makeMon(1);
	// Fine fase preparazione

	//Per esempio, controllo i nomi di due entità che dovrebbero avere nomi diversi
	EXPECT_FALSE(monMade1->getNome() == monMade2->getNome()) << "Abbiamo lo stesso nome, ma uno è Abramo e l'altro è Lincoln!";
}

TEST(TestFactory, TestObjectFactory) {
	std::cout << "Test sulla creazione di oggetti con Object Factory.\n";
	// Da qui fino al prossimo commento è solo fase di preparazione
	Oggetto oggetto1(10, "Qualcosa", "Ciò che non è ben specificato", 20), oggetto2(0.2, "Forbici", "È sconsigliata la corsa", 15), oggetto3(9000, "9 metri cubi d'acqua", "In caso di disidratazione, consumarne una piccola frazione", 500);
	Arma arma1(3, "Tagliaunghie Atomico", "Contro le unghie radioattive non c'è arma migliore.", 4, Danno({ 1 }, 4)), arma2(2.1, "Spada Lasel", "Spada cleata pel i guellieli Jedi con la elle moscia", 150, Danno({0.5,0,0,0.5},35));
	std::vector<std::shared_ptr<Oggetto>> soloObj;
	std::vector<std::shared_ptr<Arma>> soloWeap;
	std::vector<std::shared_ptr<Oggetto>> mixed;
	soloObj.push_back(std::make_shared<Oggetto>(oggetto1));
	soloObj.push_back(std::make_shared<Oggetto>(oggetto2));
	soloObj.push_back(std::make_shared<Oggetto>(oggetto3));
	soloWeap.push_back(std::make_shared<Arma>(arma1));
	soloWeap.push_back(std::make_shared<Arma>(arma2));
	mixed = soloObj;
	mixed.insert(mixed.end(), soloWeap.begin(), soloWeap.end());
	ObjectFactory objFactTestOnlyObj(soloObj);
	ObjectFactory objFactTestOnlyWeap(soloWeap);
	ObjectFactory objFactTestMixed(mixed);
	//Fine fase di preparazione

	auto pointSoloObj1 = objFactTestOnlyObj.makeObj(0);
	auto pointSoloObj2 = objFactTestOnlyObj.makeObj(1);

	EXPECT_FALSE(pointSoloObj1->getNome() == pointSoloObj2->getNome()) << "Sono oggetti diversi, eppure sono uguali!";

	auto pointSoloWeap1 = objFactTestOnlyWeap.makeWeap(0);
	auto pointSoloWeap2 = objFactTestOnlyWeap.makeWeap(1);

	EXPECT_NE(pointSoloWeap1->getNome(), pointSoloWeap2->getNome()) << "Sono armi diverse, eppure sono uguali!";

	auto pointMixed1 = objFactTestMixed.makeObj(0);
	auto pointMixed2 = objFactTestMixed.makeObj(1);

	EXPECT_FALSE(pointMixed1->getNome() == pointMixed2->getNome()) << "Sono oggetti generici diversi, eppure sono uguali!";

	EXPECT_TRUE(std::dynamic_pointer_cast<Arma>(objFactTestMixed.makeObj(4))!=nullptr) << "Sarei dovuto essere un'arma, ma non lo sono!";
}