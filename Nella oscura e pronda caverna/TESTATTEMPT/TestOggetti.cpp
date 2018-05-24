#include "stdafx.h"

TEST(TestOggetti, testConsistenzaCostruttore) {
	std::cout << "Test consistenza costruttori.\n";
	Oggetto oggettoTest(15., "Hatkanda", "L'oggetto di un film generico", 400);
	EXPECT_EQ(oggettoTest.getPeso(), 15.);
	EXPECT_EQ(oggettoTest.getNome(), "Hatkanda");
	EXPECT_EQ(oggettoTest.getDescrizione(), "L'oggetto di un film generico");
	EXPECT_EQ(oggettoTest.getValore(), 400);
	EXPECT_GT(oggettoTest.attacca().getAmmontare(), 2.5); //ln(16) non so quanto faccia di preciso
}

TEST(testOggetti, testArmi) {
	std::cout << "Test armi e danni inflitti.\n";
	Danno dannoInflittoTest(std::vector<double>{1},10);
	Arma test(4, "Spada test", "Per controllare che le spade funzionino correttamente.", 5, dannoInflittoTest);
	auto dannoTest = test.attacca();
	EXPECT_EQ(dannoTest.calcolaDannoTotale(std::vector<double>(16,1)), 10) << "WTF";
	EXPECT_EQ(dannoTest.getParteDanno(0), 10) << "Ok";
	EXPECT_EQ(dannoTest.getParteDanno(5), 0);
	test.Incanta();
	EXPECT_GT(test.attacca().getAmmontare(), dannoTest.getAmmontare());
}