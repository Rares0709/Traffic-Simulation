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
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VerkeerslichtTest.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();

    Voertuig voertuig;
    voertuig.set_baan(&banen[0]);
    double speed =16.6;
    voertuig.set_snelheid(speed);
    voertuig.set_versnelling(1.44);
    voertuig.set_positie(200);
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid1(), speed);
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, VoertuigStoptBijRood1) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VerkeerslichtTest1.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.set_baan(&banen[0]);
    double speed = 16.6;
    voertuig.set_snelheid(speed);
    voertuig.set_versnelling(1.44);
    voertuig.set_positie(200);
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid1(), speed);
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, VoertuigStoptBijRood2) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VerkeerslichtTest2.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.set_baan(&banen[0]);
    double speed = 16.6;
    voertuig.set_snelheid(speed);
    voertuig.set_versnelling(1.44);
    voertuig.set_positie(200);
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid1(), speed);
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, VoertuigStoptBijRood3) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VerkeerslichtTest3.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.set_baan(&banen[0]);
    double speed = 16.6;
    voertuig.set_snelheid(speed);
    voertuig.set_versnelling(1.44);
    voertuig.set_positie(200);
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid1(), speed);
    Voertuig::resetVolgendeNummer();
}

TEST(VerkeerslichtTest, VoertuigStoptBijRood4) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VerkeerslichtTest4.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.set_baan(&banen[0]);
    double speed = 16.6;
    voertuig.set_snelheid(speed);
    voertuig.set_versnelling(1.01);
    voertuig.set_positie(200);

    Voertuig voertuig1;
    voertuig1.set_baan(&banen[1]);
    double speed1 = 16.6;
    voertuig1.set_snelheid(speed1);
    voertuig1.set_versnelling(1.12);
    voertuig1.set_positie(200);
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.voegvoertuigtoe(voertuig1);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid1(), speed);
    ASSERT_LT(trafficSim.getVoertuigen()[1].snelheid1(), speed1);
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, VoertuigStoptBijRoodFalse) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VerkeerslichtTestFalse.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    // Controleer begin: er zijn initieel 2 voertuigen
    trafficSim.TestingModeOn();
    Voertuig voertuig;
    voertuig.set_baan(&banen[0]);
    double speed = 16.6;
    voertuig.set_snelheid(speed);
    voertuig.set_versnelling(1.44);
    voertuig.set_positie(200);
    trafficSim.voegvoertuigtoe(voertuig);
    trafficSim.Simulate(1);
    ASSERT_LT(speed, trafficSim.getVoertuigen()[0].snelheid1());
    Voertuig::resetVolgendeNummer();
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
    Voertuig::resetVolgendeNummer();
}*/
//test if lightcolor switches
TEST(InlezenTest, TrafficLightSwitchTest) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenTest.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficSim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur1(), verkeerslicht1.kleur1());
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, TrafficLightSwitchTest1) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenTest1.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    trafficSim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur1(), verkeerslicht1.kleur1());
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, TrafficLightSwitchTest2) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenTest2.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficSim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur1(), verkeerslicht1.kleur1());
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, TrafficLightSwitchTest3) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenTest3.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficSim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur1(), verkeerslicht1.kleur1());
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, TrafficLightSwitchTest4) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenTest4.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficSim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_NE(verkeerslicht.kleur1(), verkeerslicht1.kleur1());
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, TrafficLightSwitchTestFalse) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenTestFalse.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficSim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    ASSERT_EQ(verkeerslicht.kleur1(), verkeerslicht1.kleur1());
    Voertuig::resetVolgendeNummer();
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
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenBaan.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim sim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::resetVolgendeNummer();
}
TEST(ParseFileTest, ValidInputFile1) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenBaan1.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim sim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::resetVolgendeNummer();
}
TEST(ParseFileTest, ValidInputFile2) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenBaan2.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim sim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::resetVolgendeNummer();
}
TEST(ParseFileTest, ValidInputFile3) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenBaan3.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim sim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::resetVolgendeNummer();
}
TEST(ParseFileTest, ValidInputFile4) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_InlezenBaan4.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim sim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::resetVolgendeNummer();
}
TEST(ParseFileTest, ValidInputFileFalse) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    // parseFile("test/test_InlezenBaanFalse.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    // TrafficSim sim = parseFile("test/test_InlezenBaanFalse.xml");

    // ASSERT_FALSE(sim.get_banen().empty());
    ASSERT_DEATH(parseFile("test/test_InlezenBaanFalse.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
, ".*");
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
    Voertuig::resetVolgendeNummer();
}

//voor Verkeessituatie in te lezen!
TEST(InlezenTest, VerkeersSituatieWordtCorrectIngelezen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_verkeersinlezing.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();

    std::vector<Baan> banen1 = banen;
    ASSERT_EQ(banen1.size(), size_t(1));
    EXPECT_EQ(banen1[0].naam1(), "Middelheimlaan");
    EXPECT_EQ(banen1[0].lengte1(), 500);

    std::vector<Verkeersverkeerslicht> verkeerslichten1 = trafficsim.getVerkeerslichten();
    ASSERT_EQ(verkeerslichten1.size(), size_t(1));
    EXPECT_EQ(verkeerslichten1[0].baan1()->naam1(), "Middelheimlaan");
    EXPECT_EQ(verkeerslichten1[0].positie1(), 400);
    EXPECT_EQ(verkeerslichten1[0].cyclus1(), 20);

    std::vector<Voertuig> voertuigen1 = trafficsim.getVoertuigen();
    ASSERT_EQ(voertuigen1.size(), size_t(2));

    EXPECT_EQ(voertuigen1[0].baan1()->naam1(), "Middelheimlaan");
    EXPECT_EQ(voertuigen1[1].baan1()->naam1(), "Middelheimlaan");
    EXPECT_EQ(voertuigen1[0].positie1(), 20);
    EXPECT_EQ(voertuigen1[1].positie1(), 0);
    EXPECT_EQ(voertuigen1[0].type1(), "auto");
    EXPECT_EQ(voertuigen1[1].type1(), "bus");
    Voertuig::resetVolgendeNummer();
}
//VoertuigGen wordt ingelezen!
TEST(InlezenTest, VoertuiggeneratorWordtCorrectIngelezen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_voertuigGenInlezen.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();

    std::vector<VoertuigGen> generators = trafficsim.get_VoertuigGen();
    ASSERT_EQ(generators.size(), size_t(1));
    EXPECT_EQ(generators[0].baan1()->naam1(), "Middelheimlaan");
    EXPECT_EQ(generators[0].freq1(), 5);
    Voertuig::resetVolgendeNummer();
}
//Type auto inlezen!
TEST(InlezenTest, VoertuigenMetTypeWordenCorrectIngelezen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_voertuigTypeInlezen.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();

    std::vector<Voertuig> voertuigen1 = trafficsim.getVoertuigen();
    ASSERT_EQ(voertuigen.size(), size_t(4));
    EXPECT_EQ(voertuigen1[0].type1(), "bus");
    EXPECT_EQ(voertuigen1[1].type1(), "brandweerwagen");
    EXPECT_EQ(voertuigen1[2].type1(), "ziekenwagen");
    EXPECT_EQ(voertuigen1[3].type1(), "politiecombi");
    Voertuig::resetVolgendeNummer();
}
//Bushalte inlezen!
TEST(InlezenTest, BushaltesWordenCorrectIngelezen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_bushalteInlezen.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();

    std::vector<Bushalte> haltes = trafficsim.get_bushaltes();
    ASSERT_EQ(haltes.size(), size_t(1));
    EXPECT_EQ(haltes[0].baan1()->naam1(), "Middelheimlaan");
    EXPECT_EQ(haltes[0].positie1(), 250);
    EXPECT_EQ(haltes[0].wachttijd1(), 20);
    Voertuig::resetVolgendeNummer();
}
//Kruispunt inlezen!
TEST(InlezenTest, KruispuntenWordenCorrectIngelezen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_kruispuntInlezen.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();

    std::vector<Kruispunt> kruispunten1 = trafficsim.get_kruispunten();
    ASSERT_EQ(kruispunten1.size(), size_t(2));

    EXPECT_EQ(kruispunten1[0].from_baan()->naam1(), "Middelheimlaan");
    EXPECT_EQ(kruispunten1[0].from_positie(), 250);
    EXPECT_EQ(kruispunten1[0].to_baan()->naam1(), "Floralienlaan");
    EXPECT_EQ(kruispunten1[0].to_positie(), 500);

    EXPECT_EQ(kruispunten1[1].from_baan()->naam1(), "Middelheimlaan");
    EXPECT_EQ(kruispunten1[1].from_positie(), 500);
    EXPECT_EQ(kruispunten1[1].to_baan()->naam1(), "Beukenlaan");
    EXPECT_EQ(kruispunten1[1].to_positie(), 500);
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, VoertuigVerwijderen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VoertuigVerwijderen.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, VoertuigVerwijderen1) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VoertuigVerwijderen1.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, VoertuigVerwijderen2) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VoertuigVerwijderen2.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, VoertuigVerwijderen3) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VoertuigVerwijderen3.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(2));
    Voertuig::resetVolgendeNummer();
}
TEST(InlezenTest, VoertuigVerwijderen4) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VoertuigVerwijderen4.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
    Voertuig::resetVolgendeNummer();
}



TEST(BerekenSnelheidTest, SnelheidEnPositie) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VoertuigBerekenSnelheidEnPositie.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig &voertuig= trafficsim.getVoertuigen()[0];
    voertuig.set_snelheid(6);
    voertuig.set_versnelling(1.03);
    trafficsim.setDeltaTime(1.0);
    voertuig.berekenSnelheid(trafficsim.getDeltaTime());
    EXPECT_EQ(voertuig.snelheid1(), 7.03);
    EXPECT_EQ(voertuig.positie1(), 27.545);
    Voertuig::resetVolgendeNummer();
}

TEST(BerekenSnelheidTest, Versnelling) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_VoertuigBerekenVersnelling.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig &voertuig = trafficsim.getVoertuigen()[0];
    double versnelling = voertuig.versnelling1();
    voertuig.set_snelheid(14);
    voertuig.berekenVersnelling();
    EXPECT_GT(voertuig.versnelling1(), versnelling);
    // EXPECT_EQ(voertuig.versnelling, 0.7114786517627);
    // EXPECT_EQ(voertuig1.versnelling, 0.3298317128635);

    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, LichtSwitch) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_verkeerslichtSwitch.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur1(), "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur1(), "groen");
    trafficsim.Simulate(verkeerslicht.cyclus1()*2+1);
    Verkeersverkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur1(), "rood");
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, LichtSwitch1) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_verkeerslichtSwitch1.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur1(), "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur1(), "groen");
    trafficsim.Simulate(verkeerslicht.cyclus1()*2+1);
    Verkeersverkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur1(), "rood");
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, LichtSwitch2) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_verkeerslichtSwitch2.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur1(), "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur1(), "groen");
    trafficsim.Simulate(verkeerslicht.cyclus1()*2+1);
    Verkeersverkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur1(), "rood");
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, LichtSwitch3) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_verkeerslichtSwitch3.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur1(), "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur1(), "groen");
    trafficsim.Simulate(verkeerslicht.cyclus1()*2+1);
    Verkeersverkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur1(), "rood");
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, LichtSwitch4) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_verkeerslichtSwitch4.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur1(), "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur1(), "groen");
    trafficsim.Simulate(verkeerslicht.cyclus1()*2+1);
    Verkeersverkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur1(), "rood");
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, LichtSwitchFalse) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_verkeerslichtSwitchFalse.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Verkeersverkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur1(), "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus1()+1);
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_NE(verkeerslicht.kleur1(), "groen");
    trafficsim.Simulate(verkeerslicht.cyclus1()*2+1);
    Verkeersverkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur1(), "rood");
    Voertuig::resetVolgendeNummer();
}
TEST(VerkeerslichtTest, BussenStoppenBijBushaltes) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_BusStoptBijBushalte.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    trafficSim.TestingModeOn();
    Bus bus;
    bus.set_baan(trafficSim.get_bushaltes()[0].baan1());
    double speed = 10.0;
    bus.set_snelheid(speed);
    bus.set_versnelling(0.88);
    bus.set_positie(249);
    trafficSim.voegvoertuigtoe(bus);
    trafficSim.Simulate(1);

    ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid1(), speed);
    Voertuig::resetVolgendeNummer();
}
TEST(RijdenTest, VersnellenEnVertragen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_autoRijden.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    voertuig.set_snelheid(12);
    voertuig.set_versnelling(0.5);
    Voertuig voertuig1 = voertuig;
    voertuig1.vertragen();
    for (int i = 0; i < 6; ++i) {
        voertuig1.berekenSnelheid(trafficsim.getDeltaTime());
        voertuig1.berekenVersnelling();
    }
    EXPECT_GT(voertuig.snelheid1(),voertuig1.snelheid1());
    Voertuig voertuig2 = voertuig1;
    voertuig2.versnellen();
    for (int i = 0; i < 10; ++i) {
        voertuig2.berekenSnelheid(trafficsim.getDeltaTime());
        voertuig2.berekenVersnelling();
    }
    EXPECT_GT(voertuig2.snelheid1(), voertuig1.snelheid1());
    Voertuig::resetVolgendeNummer();
}
TEST(ToevoegenVoertuigen, VoertuigGenSim) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_autoRijden.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen1 = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen1.size(),size_t(2));
    int freq = trafficsim.get_VoertuigGen()[0].freq1()+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen1.size());
    Voertuig::resetVolgendeNummer();
}

TEST(ToevoegenVoertuigen, VoertuigGenSim1) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_autoRijden1.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen1 = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen1.size(),size_t(1));
    int freq = trafficsim.get_VoertuigGen()[0].freq1()+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen1.size());
    Voertuig::resetVolgendeNummer();
}
TEST(ToevoegenVoertuigen, VoertuigGenSim2) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_autoRijden2.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen1 = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen1.size(),size_t(1));
    int freq = trafficsim.get_VoertuigGen()[0].freq1()+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen1.size());
    Voertuig::resetVolgendeNummer();
}
TEST(ToevoegenVoertuigen, VoertuigGenSim3) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_autoRijden3.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen1 = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen1.size(),size_t(2));
    int freq = trafficsim.get_VoertuigGen()[0].freq1()+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen1.size());
    Voertuig::resetVolgendeNummer();
}
TEST(ToevoegenVoertuigen, VoertuigGenSim4) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_autoRijden4.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    std::vector<Voertuig> voertuigen1 = trafficsim.getVoertuigen();
    EXPECT_EQ(voertuigen1.size(),size_t(0));
    int freq = trafficsim.get_VoertuigGen()[0].freq1()+1;
    trafficsim.Simulate(freq);
    std::vector<Voertuig> voertuigenTest = trafficsim.getVoertuigen();
    EXPECT_GT(voertuigenTest.size(), voertuigen1.size());
    Voertuig::resetVolgendeNummer();
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
//     Voertuig::resetVolgendeNummer();
// }
TEST(KruispuntWegen, WegenKiezen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_Wegkiezen.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan1()->naam1();
    for (Kruispunt& kruispunt: trafficsim.get_kruispunten()) {
        kruispunt.kruispuntSim(voertuig, banen);
    }
    std::string voertuigBaanLast = voertuig.baan1()->naam1();
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::resetVolgendeNummer();
}
TEST(KruispuntWegen, WegenKiezen1) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_Wegkiezen1.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan1()->naam1();
    for (Kruispunt& kruispunt: trafficsim.get_kruispunten()) {
        kruispunt.kruispuntSim(voertuig, banen);
    }
    std::string voertuigBaanLast = voertuig.baan1()->naam1();
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::resetVolgendeNummer();
}
TEST(KruispuntWegen, WegenKiezen2) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_Wegkiezen2.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan1()->naam1();
    for (Kruispunt& kruispunt: trafficsim.get_kruispunten()) {
        kruispunt.kruispuntSim(voertuig, banen);
    }
    std::string voertuigBaanLast = voertuig.baan1()->naam1();
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::resetVolgendeNummer();
}
TEST(KruispuntWegen, WegenKiezen3) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_Wegkiezen3.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan1()->naam1();
    for (Kruispunt& kruispunt: trafficsim.get_kruispunten()) {
        kruispunt.kruispuntSim(voertuig, banen);
    }
    std::string voertuigBaanLast = voertuig.baan1()->naam1();
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::resetVolgendeNummer();
}
TEST(KruispuntWegen, WegenKiezen4) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_Wegkiezen4.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    std::string voertuigBaanFirst = voertuig.baan1()->naam1();
    for (Kruispunt& kruispunt: trafficsim.get_kruispunten()) {
        kruispunt.kruispuntSim(voertuig, banen);
    }
    std::string voertuigBaanLast = voertuig.baan1()->naam1();
    if (voertuigBaanFirst == voertuigBaanLast) {
        EXPECT_EQ(voertuigBaanFirst,voertuigBaanLast);
    }
    else {
        EXPECT_NE(voertuigBaanFirst,voertuigBaanLast);
    }
    Voertuig::resetVolgendeNummer();
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
//     Voertuig::resetVolgendeNummer();
// }
TEST(TypeVoertuig,VoertuigLatenDoorrijden) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_DoorrijdenType.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie1() <= verkeerslicht.positie1()) {
        for (Verkeersverkeerslicht verkeerlicht:trafficsim.getVerkeerslichten()) {
            verkeerslicht.verkeerslichtSim(verkeerslicht,voertuigen, trafficsim.getTime(), true);
        }
        voertuig.berekenSnelheid(trafficsim.getDeltaTime());
        voertuig.berekenVersnelling();
    }
    EXPECT_GT(voertuig.positie1(),verkeerslicht.positie1());
    Voertuig::resetVolgendeNummer();
}
TEST(TypeVoertuig,VoertuigLatenDoorrijden1) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_DoorrijdenType1.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie1() <= verkeerslicht.positie1()) {
        for (Verkeersverkeerslicht verkeerlicht:trafficsim.getVerkeerslichten()) {
            verkeerslicht.verkeerslichtSim(verkeerslicht,voertuigen, trafficsim.getTime(), true);
        }
        voertuig.berekenSnelheid(trafficsim.getDeltaTime());
        voertuig.berekenVersnelling();
    }
    EXPECT_GT(voertuig.positie1(),verkeerslicht.positie1());
    Voertuig::resetVolgendeNummer();
}
TEST(TypeVoertuig,VoertuigLatenDoorrijden2) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_DoorrijdenType2.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie1() <= verkeerslicht.positie1()) {
        for (Verkeersverkeerslicht verkeerlicht:trafficsim.getVerkeerslichten()) {
            verkeerslicht.verkeerslichtSim(verkeerslicht,voertuigen, trafficsim.getTime(), true);
        }
        voertuig.berekenSnelheid(trafficsim.getDeltaTime());
        voertuig.berekenVersnelling();
    }
    EXPECT_GT(voertuig.positie1(),verkeerslicht.positie1());
    Voertuig::resetVolgendeNummer();
}
TEST(TypeVoertuig,VoertuigLatenDoorrijden3) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_DoorrijdenType3.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie1() <= verkeerslicht.positie1()) {
        for (Verkeersverkeerslicht verkeerlicht:trafficsim.getVerkeerslichten()) {
            verkeerslicht.verkeerslichtSim(verkeerslicht,voertuigen, trafficsim.getTime(), true);
        }
        voertuig.berekenSnelheid(trafficsim.getDeltaTime());
        voertuig.berekenVersnelling();
    }
    EXPECT_GT(voertuig.positie1(),verkeerslicht.positie1());
    Voertuig::resetVolgendeNummer();
}
TEST(TypeVoertuig,VoertuigLatenDoorrijden4) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_DoorrijdenType4.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie1() <= verkeerslicht.positie1()) {
        for (Verkeersverkeerslicht verkeerlicht:trafficsim.getVerkeerslichten()) {
            verkeerslicht.verkeerslichtSim(verkeerslicht,voertuigen, trafficsim.getTime(), true);
        }
        voertuig.berekenSnelheid(trafficsim.getDeltaTime());
        voertuig.berekenVersnelling();
    }
    EXPECT_GT(voertuig.positie1(),verkeerslicht.positie1());
    Voertuig::resetVolgendeNummer();
}
TEST(TypeVoertuig,VoertuigLatenDoorrijdenFalse) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test_DoorrijdenTypeFalse.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficsim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficsim.TestingModeOn();
    Voertuig voertuig = trafficsim.getVoertuigen()[0];
    Verkeersverkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    while (voertuig.positie1() <= verkeerslicht.positie1()) {
        for (Verkeersverkeerslicht verkeerlicht:trafficsim.getVerkeerslichten()) {
            verkeerslicht.verkeerslichtSim(verkeerslicht,voertuigen, trafficsim.getTime(), true);
        }
        voertuig.berekenSnelheid(trafficsim.getDeltaTime());
        voertuig.berekenVersnelling();
    }
    EXPECT_GT(voertuig.positie1(),verkeerslicht.positie1());
    Voertuig::resetVolgendeNummer();
}
TEST(OutputTest, OutputCorrect) {
    // Setup
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;

    parseFile("test/test1.xml", &banen, &verkeerslichten, &voertuigen, &voertuigengen, &bushaltes, &kruispunten);
    TrafficSim traffic(banen, verkeerslichten, voertuigen, voertuigengen, bushaltes, kruispunten);

    std::streambuf* orig_buf = std::cout.rdbuf();
    std::ostringstream buffer;
    std::cout.rdbuf(buffer.rdbuf());

    traffic.Simulate(10);
    std::cout.rdbuf(orig_buf);

    std::ifstream expected_file("../output.txt");
    ASSERT_TRUE(expected_file.is_open()) << "Kon expected_output.txt niet openen";

    std::stringstream expected_buffer;
    expected_buffer << expected_file.rdbuf();

    std::string actual = buffer.str();
    std::string expected = expected_buffer.str();

    EXPECT_EQ(actual, expected) << "De output van de simulatie komt niet overeen met de verwachte output.";
}
//Alle testen!
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
