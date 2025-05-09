//
// Created by jonas on 3/17/2025.
//

#include <gtest/gtest.h>
#include "ParseFile.h"

/*class TrafficSimTest : public ::testing::Test {
protected:
    TrafficSim trafficSim;
    TrafficSimTest()
        :trafficSim(parseFile("test/test_InlezenTest.xml")){}
    virtual void SetUp() {
        //trafficSim.setTime(4.9);
        trafficSim.TestingModeOn();
    }
};*/

/*class VoertuigGenSimTest : public ::testing::Test {
protected:
    TrafficSim sim;
    VoertuigGenSimTest()
        :sim(parseFile("test/test_InlezenTest.xml")){}
    virtual void SetUp() {
        sim.setTime(0);
    }
};*/
TEST(VerkeerslichtTest, VoertuigStoptBijRood) {
    TrafficSim trafficSim = parseFile("test/test_VerkeerslichtTest.xml");

    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.baan = "Middelheimlaan";
    double speed = voertuig.snelheid = 16.6;
    voertuig.versnelling = 1.44;
    voertuig.positie = 200;
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid, speed);
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, VoertuigStoptBijRood1) {
    TrafficSim trafficSim = parseFile("test/test_VerkeerslichtTest1.xml");
    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.baan = "Middelheimlaan";
    double speed = voertuig.snelheid = 16.6;
    voertuig.versnelling = 1.44;
    voertuig.positie = 200;
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid, speed);
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, VoertuigStoptBijRood2) {
    TrafficSim trafficSim = parseFile("test/test_VerkeerslichtTest2.xml");
    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.baan = "Middelheimlaan";
    double speed = voertuig.snelheid = 16.6;
    voertuig.versnelling = 1.44;
    voertuig.positie = 200;
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid, speed);
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, VoertuigStoptBijRood3) {
    TrafficSim trafficSim = parseFile("test/test_VerkeerslichtTest3.xml");
    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.baan = "Beukenlaan";
    double speed = voertuig.snelheid = 16.6;
    voertuig.versnelling = 1.44;
    voertuig.positie = 200;
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid, speed);
    Voertuig::volgendeNummer = 1;
}

TEST(VerkeerslichtTest, VoertuigStoptBijRood4) {
    TrafficSim trafficSim = parseFile("test/test_VerkeerslichtTest4.xml");
    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.baan = "Floralienlaan";
    double speed = voertuig.snelheid = 8.02;
    voertuig.versnelling = 1.01;
    voertuig.positie = 200;

    Voertuig voertuig1;
    voertuig1.baan = "Middelheimlaan";
    double speed1 = voertuig1.snelheid = 4.12;
    voertuig1.versnelling = 1.12;
    voertuig1.positie = 200;
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.voegvoertuigtoe(voertuig1);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid, speed);
    ASSERT_LT(trafficSim.getVoertuigen()[1].snelheid, speed1);
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, VoertuigStoptBijRoodFalse) {
    TrafficSim trafficSim = parseFile("test/test_VerkeerslichtTestFalse.xml");

    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.baan = "Middelheimlaan";
    double speed = voertuig.snelheid = 16.6;
    voertuig.versnelling = 1.44;
    voertuig.positie = 200;
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid, speed);
    Voertuig::volgendeNummer = 1;
}

// Test that verifies if a vehicle is generated when the time exceeds the vehicle generator's frequency
/*TEST(VoertuigGenSimTest, GeenNieuwVoertuigBijBezetting) {
    TrafficSim trafficSim = parseFile("test/test_InlezenTest.xml");
    // Controleer begin: er zijn initieel 2 voertuigen
    ASSERT_EQ(trafficSim.getVoertuigen().size(), 2u);

    // Simuleer voertuiggenerator
    trafficSim.simVoertuiggenerator();

    // Na oproep mag er geen nieuw voertuig zijn toegevoegd, want positie 0 is al bezet
    EXPECT_EQ(trafficSim.getVoertuigen().size(), 2u);
    Voertuig::volgendeNummer = 1;
}*/
//test if lightcolor switches
TEST(InlezenTest, TrafficLightSwitchTest) {
    TrafficSim trafficSim = parseFile("test/test_InlezenTest.xml");
    trafficSim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur, verkeerslicht1.kleur);
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, TrafficLightSwitchTest1) {
    TrafficSim trafficSim = parseFile("test/test_InlezenTest1.xml");
    trafficSim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur, verkeerslicht1.kleur);
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, TrafficLightSwitchTest2) {
    TrafficSim trafficSim = parseFile("test/test_InlezenTest2.xml");
    trafficSim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur, verkeerslicht1.kleur);
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, TrafficLightSwitchTest3) {
    TrafficSim trafficSim = parseFile("test/test_InlezenTest3.xml");
    trafficSim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur, verkeerslicht1.kleur);
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, TrafficLightSwitchTest4) {
    TrafficSim trafficSim = parseFile("test/test_InlezenTest4.xml");
    trafficSim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur, verkeerslicht1.kleur);
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, TrafficLightSwitchTestFalse) {
    TrafficSim trafficSim = parseFile("test/test_InlezenTestFalse.xml");
    trafficSim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur, verkeerslicht1.kleur);
    Voertuig::volgendeNummer = 1;
}
//defective test
/*TEST_F(TrafficSimTest, VehicleRemovalTest) {
    trafficSim.Simulate();

    ASSERT_TRUE(trafficSim.getVoertuigen().empty());
}*/

//defective test
/*TEST_F(TrafficSimTest, VehicleGenerationTest) {
    trafficSim.simVoertuiggenerator();

    ASSERT_GT(trafficSim.getVoertuigen().size(), 1);
}*/
TEST(ParseFileTest, ValidInputFile) {
    TrafficSim sim = parseFile("test/test_InlezenBaan.xml");

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::volgendeNummer = 1;
}
TEST(ParseFileTest, ValidInputFile1) {
    TrafficSim sim = parseFile("test/test_InlezenBaan1.xml");

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::volgendeNummer = 1;
}
TEST(ParseFileTest, ValidInputFile2) {
    TrafficSim sim = parseFile("test/test_InlezenBaan2.xml");

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::volgendeNummer = 1;
}
TEST(ParseFileTest, ValidInputFile3) {
    TrafficSim sim = parseFile("test/test_InlezenBaan3.xml");

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::volgendeNummer = 1;
}
TEST(ParseFileTest, ValidInputFile4) {
    TrafficSim sim = parseFile("test/test_InlezenBaan4.xml");

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::volgendeNummer = 1;
}
TEST(ParseFileTest, ValidInputFileFalse) {
    TrafficSim sim = parseFile("test/test_InlezenBaanFalse.xml");

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::volgendeNummer = 1;
}

//voor Verkeessituatie in te lezen!
TEST(InlezenTest, VerkeersSituatieWordtCorrectIngelezen) {
    TrafficSim trafficsim = parseFile("test/test_verkeersinlezing.xml");
    trafficsim.TestingModeOn();

    std::vector<Baan> banen = trafficsim.get_banen();
    ASSERT_EQ(banen.size(), size_t(1));
    EXPECT_EQ(banen[0].naam, "Middelheimlaan");
    EXPECT_EQ(banen[0].lengte, 500);

    std::vector<Verkeerslicht> verkeerslichten = trafficsim.getVerkeerslichten();
    ASSERT_EQ(verkeerslichten.size(), size_t(1));
    EXPECT_EQ(verkeerslichten[0].baan, "Middelheimlaan");
    EXPECT_EQ(verkeerslichten[0].positie, 400);
    EXPECT_EQ(verkeerslichten[0].cyclus, 20);

    std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
    ASSERT_EQ(voertuigen.size(), size_t(2));

    EXPECT_EQ(voertuigen[0].baan, "Middelheimlaan");
    EXPECT_EQ(voertuigen[1].baan, "Middelheimlaan");
    EXPECT_EQ(voertuigen[0].positie, 20);
    EXPECT_EQ(voertuigen[1].positie, 0);
    Voertuig::volgendeNummer = 1;
}
//VoertuigGen wordt ingelezen!
TEST(InlezenTest, VoertuiggeneratorWordtCorrectIngelezen) {
    TrafficSim trafficsim = parseFile("test/test_voertuigGenInlezen.xml");
    trafficsim.TestingModeOn();

    std::vector<VoertuigGen> generators = trafficsim.get_VoertuigGen();
    ASSERT_EQ(generators.size(), size_t(1));
    EXPECT_EQ(generators[0].baan, "Middelheimlaan");
    EXPECT_EQ(generators[0].freq, 5);
    Voertuig::volgendeNummer = 1;
}
//Type auto inlezen!
TEST(InlezenTest, VoertuigenMetTypeWordenCorrectIngelezen) {
    TrafficSim trafficsim = parseFile("test/test_voertuigTypeInlezen.xml");
    trafficsim.TestingModeOn();

    std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
    ASSERT_EQ(voertuigen.size(), size_t(4));
    EXPECT_EQ(voertuigen[0].type, "bus");
    EXPECT_EQ(voertuigen[1].type, "brandweerwagen");
    EXPECT_EQ(voertuigen[2].type, "ziekenwagen");
    EXPECT_EQ(voertuigen[3].type, "politiecombi");
    Voertuig::volgendeNummer = 1;
}
//Bushalte inlezen!
TEST(InlezenTest, BushaltesWordenCorrectIngelezen) {
    TrafficSim trafficsim = parseFile("test/test_bushalteInlezen.xml");
    trafficsim.TestingModeOn();

    std::vector<Bushalte> haltes = trafficsim.get_bushaltes();
    ASSERT_EQ(haltes.size(), size_t(1));
    EXPECT_EQ(haltes[0].baan, "Middelheimlaan");
    EXPECT_EQ(haltes[0].positie, 250);
    EXPECT_EQ(haltes[0].wachttijd, 20);
    Voertuig::volgendeNummer = 1;
}
//Kruispunt inlezen!
TEST(InlezenTest, KruispuntenWordenCorrectIngelezen) {
    TrafficSim trafficsim = parseFile("test/test_kruispuntInlezen.xml");
    trafficsim.TestingModeOn();

    std::vector<Kruispunt> kruispunten = trafficsim.get_kruispunten();
    ASSERT_EQ(kruispunten.size(), size_t(2));

    EXPECT_EQ(kruispunten[0].fromBaan, "Middelheimlaan");
    EXPECT_EQ(kruispunten[0].fromPositie, 250);
    EXPECT_EQ(kruispunten[0].toBaan, "Floralienlaan");
    EXPECT_EQ(kruispunten[0].toPositie, 500);

    EXPECT_EQ(kruispunten[1].fromBaan, "Middelheimlaan");
    EXPECT_EQ(kruispunten[1].fromPositie, 500);
    EXPECT_EQ(kruispunten[1].toBaan, "Beukenlaan");
    EXPECT_EQ(kruispunten[1].toPositie, 500);
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, VoertuigVerwijderen) {
    TrafficSim trafficsim = parseFile("test/test_VoertuigVerwijderen.xml");
    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, VoertuigVerwijderen1) {
    TrafficSim trafficsim = parseFile("test/test_VoertuigVerwijderen1.xml");
    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, VoertuigVerwijderen2) {
    TrafficSim trafficsim = parseFile("test/test_VoertuigVerwijderen2.xml");
    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, VoertuigVerwijderen3) {
    TrafficSim trafficsim = parseFile("test/test_VoertuigVerwijderen3.xml");
    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(2));
    Voertuig::volgendeNummer = 1;
}
TEST(InlezenTest, VoertuigVerwijderen4) {
    TrafficSim trafficsim = parseFile("test/test_VoertuigVerwijderen4.xml");
    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
    Voertuig::volgendeNummer = 1;
}



TEST(BerekenSnelheidTest, SnelheidEnPositie) {
    TrafficSim trafficsim = parseFile("test/test_VoertuigBerekenSnelheidEnPositie.xml");
    trafficsim.TestingModeOn();
    Voertuig &voertuig= trafficsim.getVoertuigen()[0];
    voertuig.snelheid=6;
    voertuig.versnelling=1.03;
    trafficsim.setDeltaTime(1.0);
    trafficsim.berekenSnelheid(voertuig);
    EXPECT_EQ(voertuig.snelheid, 7.03);
    EXPECT_EQ(voertuig.positie, 27.545);
    Voertuig::volgendeNummer = 1;
}

TEST(BerekenSnelheidTest, Versnelling) {
    TrafficSim trafficsim = parseFile("test/test_VoertuigBerekenVersnelling.xml");
    trafficsim.TestingModeOn();
    Voertuig &voertuig = trafficsim.getVoertuigen()[0];
    double versnelling = voertuig.versnelling;
    voertuig.snelheid = 14;

    trafficsim.berekenVersnelling(voertuig);
    EXPECT_GT(voertuig.versnelling, versnelling);
    // EXPECT_EQ(voertuig.versnelling, 0.7114786517627);
    // EXPECT_EQ(voertuig1.versnelling, 0.3298317128635);

    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, LichtSwitch) {
    TrafficSim trafficsim = parseFile("test/test_verkeerslichtSwitch.xml");
    trafficsim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur, "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur, "groen");
    trafficsim.Simulate(verkeerslicht.cyclus*2+1);
    Verkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur, "rood");
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, LichtSwitch1) {
    TrafficSim trafficsim = parseFile("test/test_verkeerslichtSwitch1.xml");
    trafficsim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur, "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur, "groen");
    trafficsim.Simulate(verkeerslicht.cyclus*2+1);
    Verkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur, "rood");
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, LichtSwitch2) {
    TrafficSim trafficsim = parseFile("test/test_verkeerslichtSwitch2.xml");
    trafficsim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur, "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur, "groen");
    trafficsim.Simulate(verkeerslicht.cyclus*2+1);
    Verkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur, "rood");
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, LichtSwitch3) {
    TrafficSim trafficsim = parseFile("test/test_verkeerslichtSwitch3.xml");
    trafficsim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur, "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur, "groen");
    trafficsim.Simulate(verkeerslicht.cyclus*2+1);
    Verkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur, "rood");
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, LichtSwitch4) {
    TrafficSim trafficsim = parseFile("test/test_verkeerslichtSwitch4.xml");
    trafficsim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur, "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur, "groen");
    trafficsim.Simulate(verkeerslicht.cyclus*2+1);
    Verkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur, "rood");
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, LichtSwitchFalse) {
    TrafficSim trafficsim = parseFile("test/test_verkeerslichtSwitch.xml");
    trafficsim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur, "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur, "groen");
    trafficsim.Simulate(verkeerslicht.cyclus*2+1);
    Verkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur, "rood");
    Voertuig::volgendeNummer = 1;
}
TEST(VerkeerslichtTest, BussenStoppenBijBushaltes) {
    TrafficSim trafficSim = parseFile("test/test_BusStoptBijBushalte.xml");
    trafficSim.TestingModeOn();
    Voertuig bus;
    bus.baan = trafficSim.get_bushaltes()[0].baan;
    double speed = bus.snelheid = 10.0;
    bus.versnelling = 0.88;
    bus.positie = 249;
    bus.setType("bus");
    trafficSim.voegvoertuigtoe(bus);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid, speed);
    Voertuig::volgendeNummer = 1;
}
TEST(RijdenTest, VersnellenEnVertragen) {
    TrafficSim trafficsim = parseFile("test/test_autoRijden.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    voertuig.snelheid = 12;
    voertuig.versnelling = 0.5;
    Voertuig voertuig1 = voertuig;
    trafficsim.vertragen(voertuig1);
    for (int i = 0; i < 6; ++i) {
        trafficsim.berekenSnelheid(voertuig1);
        trafficsim.berekenVersnelling(voertuig1);
    }
    EXPECT_GT(voertuig.snelheid,voertuig1.snelheid);
    Voertuig voertuig2 = voertuig1;
    trafficsim.versnellen(voertuig2);
    for (int i = 0; i < 10; ++i) {
        trafficsim.berekenSnelheid(voertuig2);
        trafficsim.berekenVersnelling(voertuig2);
    }
    EXPECT_GT(voertuig2.snelheid, voertuig1.snelheid);
    Voertuig::volgendeNummer = 1;
}
TEST(ToevoegenVoertuigen, VoertuigGenSim) {
    TrafficSim trafficsim = parseFile("test/test_autoRijden.xml");
    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen.size(),size_t(2));
    int freq = trafficsim.get_VoertuigGen()[0].freq+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen.size());
    Voertuig::volgendeNummer = 1;
}

TEST(ToevoegenVoertuigen, VoertuigGenSim1) {
    TrafficSim trafficsim = parseFile("test/test_autoRijden1.xml");
    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen.size(),size_t(1));
    int freq = trafficsim.get_VoertuigGen()[0].freq+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen.size());
    Voertuig::volgendeNummer = 1;
}
TEST(ToevoegenVoertuigen, VoertuigGenSim2) {
    TrafficSim trafficsim = parseFile("test/test_autoRijden2.xml");
    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen.size(),size_t(1));
    int freq = trafficsim.get_VoertuigGen()[0].freq+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen.size());
    Voertuig::volgendeNummer = 1;
}
TEST(ToevoegenVoertuigen, VoertuigGenSim3) {
    TrafficSim trafficsim = parseFile("test/test_autoRijden3.xml");
    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen.size(),size_t(2));
    int freq = trafficsim.get_VoertuigGen()[0].freq+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen.size());
    Voertuig::volgendeNummer = 1;
}
TEST(ToevoegenVoertuigen, VoertuigGenSim4) {
    TrafficSim trafficsim = parseFile("test/test_autoRijden4.xml");
    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen.size(),size_t(0));
    int freq = trafficsim.get_VoertuigGen()[0].freq+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen.size());
    Voertuig::volgendeNummer = 1;
}
// TEST(ToevoegenVoertuigen, VoertuigGenSimFalse) {
//     TrafficSim trafficsim = parseFile("test/test_autoRijdenFalse.xml");
//     trafficsim.TestingModeOn();
//     std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
//     EXPECT_EQ(voertuigen.size(),size_t(2));
//     int freq = trafficsim.get_VoertuigGen()[0].freq+1;
//     trafficsim.Simulate(freq);
//     std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
//     EXPECT_GT(voertuigenTest.size(), voertuigen.size());
//     Voertuig::volgendeNummer = 1;
// }
TEST(KruispuntWegen, WegenKiezen) {
    TrafficSim trafficsim = parseFile("test/test_Wegkiezen.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan;
    trafficsim.kruispuntSim(voertuig);
    std::string voertuigBaanLast = voertuig.baan;
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::volgendeNummer = 1;
}
TEST(KruispuntWegen, WegenKiezen1) {
    TrafficSim trafficsim = parseFile("test/test_Wegkiezen1.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan;
    trafficsim.kruispuntSim(voertuig);
    std::string voertuigBaanLast = voertuig.baan;
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::volgendeNummer = 1;
}
TEST(KruispuntWegen, WegenKiezen2) {
    TrafficSim trafficsim = parseFile("test/test_Wegkiezen2.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan;
    trafficsim.kruispuntSim(voertuig);
    std::string voertuigBaanLast = voertuig.baan;
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::volgendeNummer = 1;
}
TEST(KruispuntWegen, WegenKiezen3) {
    TrafficSim trafficsim = parseFile("test/test_Wegkiezen3.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan;
    trafficsim.kruispuntSim(voertuig);
    std::string voertuigBaanLast = voertuig.baan;
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::volgendeNummer = 1;
}
TEST(KruispuntWegen, WegenKiezen4) {
    TrafficSim trafficsim = parseFile("test/test_Wegkiezen4.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan;
    trafficsim.kruispuntSim(voertuig);
    std::string voertuigBaanLast = voertuig.baan;
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::volgendeNummer = 1;
}
// TEST(KruispuntWegen, WegenKiezenFalse) {
//     TrafficSim trafficsim = parseFile("test/test_WegkiezenFalse.xml");
//     trafficsim.TestingModeOn();
//     Voertuig voertuig = trafficsim.getVoertuigen()[0];
//     std::string voertuigBaanFirst = voertuig.baan;
//     trafficsim.kruispuntSim(voertuig);
//     std::string voertuigBaanLast = voertuig.baan;
//     if (voertuigBaanFirst == voertuigBaanLast) {
//         EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
//     }
//     else {
//         EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
//     }
//     Voertuig::volgendeNummer = 1;
// }
TEST(TypeVoertuig,VoertuigLatenDoorrijden) {
    TrafficSim trafficsim = parseFile("test/test_DoorrijdenType.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie <= verkeerslicht.positie) {
        trafficsim.checkverkeerslicht();
        trafficsim.berekenSnelheid(voertuig);
        trafficsim.berekenVersnelling(voertuig);
    }
    EXPECT_GT(voertuig.positie,verkeerslicht.positie);
    Voertuig::volgendeNummer = 1;
}
TEST(TypeVoertuig,VoertuigLatenDoorrijden1) {
    TrafficSim trafficsim = parseFile("test/test_DoorrijdenType1.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie <= verkeerslicht.positie) {
        trafficsim.checkverkeerslicht();
        trafficsim.berekenSnelheid(voertuig);
        trafficsim.berekenVersnelling(voertuig);
    }
    EXPECT_GT(voertuig.positie,verkeerslicht.positie);
    Voertuig::volgendeNummer = 1;
}
TEST(TypeVoertuig,VoertuigLatenDoorrijden2) {
    TrafficSim trafficsim = parseFile("test/test_DoorrijdenType2.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie <= verkeerslicht.positie) {
        trafficsim.checkverkeerslicht();
        trafficsim.berekenSnelheid(voertuig);
        trafficsim.berekenVersnelling(voertuig);
    }
    EXPECT_GT(voertuig.positie,verkeerslicht.positie);
    Voertuig::volgendeNummer = 1;
}
TEST(TypeVoertuig,VoertuigLatenDoorrijden3) {
    TrafficSim trafficsim = parseFile("test/test_DoorrijdenType3.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie <= verkeerslicht.positie) {
        trafficsim.checkverkeerslicht();
        trafficsim.berekenSnelheid(voertuig);
        trafficsim.berekenVersnelling(voertuig);
    }
    EXPECT_GT(voertuig.positie,verkeerslicht.positie);
    Voertuig::volgendeNummer = 1;
}
TEST(TypeVoertuig,VoertuigLatenDoorrijden4) {
    TrafficSim trafficsim = parseFile("test/test_DoorrijdenType4.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie <= verkeerslicht.positie) {
        trafficsim.checkverkeerslicht();
        trafficsim.berekenSnelheid(voertuig);
        trafficsim.berekenVersnelling(voertuig);
    }
    EXPECT_GT(voertuig.positie,verkeerslicht.positie);
    Voertuig::volgendeNummer = 1;
}
TEST(TypeVoertuig,VoertuigLatenDoorrijdenFalse) {
    TrafficSim trafficsim = parseFile("test/test_DoorrijdenTypeFalse.xml");
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie <= verkeerslicht.positie) {
        trafficsim.checkverkeerslicht();
        trafficsim.berekenSnelheid(voertuig);
        trafficsim.berekenVersnelling(voertuig);
    }
    EXPECT_GT(voertuig.positie,verkeerslicht.positie);
    Voertuig::volgendeNummer = 1;
}
//Alle testen!
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
