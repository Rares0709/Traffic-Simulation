//
// Created by jonas on 3/17/2025.
//

#include <gtest/gtest.h>
#include "ParseFile.h"

/*class TrafficSimTest : public ::testing::Test {
protected:
    TrafficSim trafficSim;
    TrafficSimTest()
        :trafficSim(parseFile("test/test1.xml")){}
    virtual void SetUp() {
        //trafficSim.setTime(4.9);
        trafficSim.TestingModeOn();
    }
};*/

/*class VoertuigGenSimTest : public ::testing::Test {
protected:
    TrafficSim sim;
    VoertuigGenSimTest()
        :sim(parseFile("test/test1.xml")){}
    virtual void SetUp() {
        sim.setTime(0);
    }
};*/
/*TEST(VerkeerslichtTest, VoertuigStoptBijRood) {
    TrafficSim trafficSim = parseFile("test/test2.xml");
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
    Voertuig voertuig1;
    voertuig1.volgendeNummer = 0;
}*/
// Test that verifies if a vehicle is generated when the time exceeds the vehicle generator's frequency
/*TEST(VoertuigGenSimTest, GeenNieuwVoertuigBijBezetting) {
    TrafficSim trafficSim = parseFile("test/test1.xml");
    // Controleer begin: er zijn initieel 2 voertuigen
    ASSERT_EQ(trafficSim.getVoertuigen().size(), 2u);

    // Simuleer voertuiggenerator
    trafficSim.simVoertuiggenerator();

    // Na oproep mag er geen nieuw voertuig zijn toegevoegd, want positie 0 is al bezet
    EXPECT_EQ(trafficSim.getVoertuigen().size(), 2u);
    Voertuig voertuig;
    voertuig.volgendeNummer = 0;
}*/
//test if lightcolor switches
/*TEST_F(TrafficSimTest, TrafficLightSwitchTest) {
    Verkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    if (trafficSim.getTime() > verkeerslicht.cyclus) {
        ASSERT_NE(verkeerslicht.kleur, verkeerslicht1.kleur);
    }
}*/

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
/*TEST(ParseFileTest, ValidInputFile) {
    TrafficSim sim = parseFile("test/test1.xml");

    ASSERT_FALSE(sim.getVoertuigen().empty());
    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
}*/
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
}
//VoertuigGen wordt ingelezen!
TEST(InlezenTest, VoertuiggeneratorWordtCorrectIngelezen) {
    TrafficSim trafficsim = parseFile("test/test_voertuigGenInlezen.xml");
    trafficsim.TestingModeOn();

    std::vector<VoertuigGen> generators = trafficsim.get_VoertuigGen();
    ASSERT_EQ(generators.size(), size_t(1));
    EXPECT_EQ(generators[0].baan, "Middelheimlaan");
    EXPECT_EQ(generators[0].freq, 5);
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
}
TEST(InlezenTest, VoertuigVerwijderen) {
    TrafficSim trafficsim = parseFile("test/test_VoertuigVerwijderen.xml");
    trafficsim.TestingModeOn();
    ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
    trafficsim.Simulate(1);
    EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}