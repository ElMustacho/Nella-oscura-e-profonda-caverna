#include "stdafx.h"

TEST(TestEntita, TestSuiDanniDelleEntita) {
	std::cout << "Test sulla gestione dei danni\n";
	auto entita1 = MonsterFactory::makeMonRand(0);
	auto entita2 = MonsterFactory::makeMonRand(1);
	auto pianoPerTest = pianoCavernaIsola(10, 10);
	pianoPerTest.at(0, 0).Scava();
	pianoPerTest.at(0, 1).Scava();
	pianoPerTest.placeEntita(entita1, coord(0, 0));
	pianoPerTest.placeEntita(entita2, coord(0, 1));
	pianoPerTest.scontro(coord(0, 0), Danno({1},10));
	ASSERT_GT(pianoPerTest.at(0, 0).getEntita()->getAttributi().getMaxHp(), pianoPerTest.at(0, 0).getEntita()->getAttributi().getHp()) << "Non sono stato ferito!";
	pianoPerTest.scontro(coord(0, 1), Danno({1},900000)); //mi aspetto che muoia con così tanti danni
	ASSERT_EQ(pianoPerTest.at(0, 1).getEntita(), nullptr) << "Se fossi morto ora io non ci sarei.";
	pianoPerTest.scontro(coord(0, 0), Danno({ 1 }, -50)); //questo è l'equivalente di un colpo di una spada che guarisce. No, non spiegherò come questo possa succedere.
	ASSERT_EQ(pianoPerTest.at(0, 0).getEntita()->getAttributi().getMaxHp(), pianoPerTest.at(0, 0).getEntita()->getAttributi().getHp()) << "Mi hanno curato fino a piena vita ma non ho piena vita (?)";
	pianoPerTest.scontro(coord(0, 0), Danno({ 1 }, 0)); //Attacco che non fa niente.
	ASSERT_EQ(pianoPerTest.at(0, 0).getEntita()->getAttributi().getMaxHp(), pianoPerTest.at(0, 0).getEntita()->getAttributi().getHp()) << "Non ho subito niente ma mi sento peggio di prima!";
}

TEST(TestEntita, TestEquipaggiamento) {
	std::cout << "Test sull'equipaggiamento di oggetti.\n";
	auto prot = Protagonista("HeroTest", {}, Attributi(true), Equipaggiamento(), 1, 50, 50, "");
	auto armaDelTest = std::make_shared<Arma>(10, "Ammazza che test", "Miiii, è un gioco di parole!", 50, Danno({ 0,1 }, 15));
	prot.addInventario(armaDelTest);
	prot.equip(0);
	ASSERT_EQ(prot.getEquipaggiamento().getArmaPrimaria(), armaDelTest) << "Sono diverso anche se sono uguale!";
	ASSERT_EQ(prot.getInventario().size(), 0) << "Ho qualcosa nell'inventario, ma dovrebbe essere vuoto!";
}