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
// TEST(VerkeerslichtTest, VoertuigStoptBijRood) {
//     TrafficSim trafficSim = parseFile("test/test2.xml");
//     // Controleer begin: er zijn initieel 2 voertuigen
//     trafficSim.TestingModeOn();
//     Voertuig voertuig;
//     voertuig.baan = "Middelheimlaan";
//     double speed = voertuig.snelheid = 16.6;
//     voertuig.versnelling = 1.44;
//     voertuig.positie = 200;
//     trafficSim.voegvoertuigtoe(voertuig);
//     trafficSim.Simulate(1);
//
//     ASSERT_LT(trafficSim.getVoertuigen()[0].snelheid, speed);
//     Voertuig::volgendeNummer = 1;
// }
// // Test that verifies if a vehicle is generated when the time exceeds the vehicle generator's frequency
// /*TEST(VoertuigGenSimTest, GeenNieuwVoertuigBijBezetting) {
//     TrafficSim trafficSim = parseFile("test/test1.xml");
//     // Controleer begin: er zijn initieel 2 voertuigen
//     ASSERT_EQ(trafficSim.getVoertuigen().size(), 2u);
//
//     // Simuleer voertuiggenerator
//     trafficSim.simVoertuiggenerator();
//
//     // Na oproep mag er geen nieuw voertuig zijn toegevoegd, want positie 0 is al bezet
//     EXPECT_EQ(trafficSim.getVoertuigen().size(), 2u);
//     Voertuig::volgendeNummer = 1;
// }*/
// //test if lightcolor switches
// TEST(InlezenTest, TrafficLightSwitchTest) {
//     TrafficSim trafficSim = parseFile("test/test1.xml");
//     trafficSim.TestingModeOn();
//     Verkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
//     trafficSim.Simulate(verkeerslicht1.cyclus+1);
//     Verkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
//     ASSERT_NE(verkeerslicht.kleur, verkeerslicht1.kleur);
//     Voertuig::volgendeNummer = 1;
// }
//
// //defective test
// /*TEST_F(TrafficSimTest, VehicleRemovalTest) {
//     trafficSim.Simulate();
//
//     ASSERT_TRUE(trafficSim.getVoertuigen().empty());
// }*/
//
// //defective test
// /*TEST_F(TrafficSimTest, VehicleGenerationTest) {
//     trafficSim.simVoertuiggenerator();
//
//     ASSERT_GT(trafficSim.getVoertuigen().size(), 1);
// }*/
// TEST(ParseFileTest, ValidInputFile) {
//     TrafficSim sim = parseFile("test/test1.xml");
//
//     ASSERT_FALSE(sim.getVoertuigen().empty());
//     ASSERT_FALSE(sim.get_banen().empty());
//     //ASSERT_FALSE(sim.getVerkeerslichten().empty());
//     Voertuig::volgendeNummer = 1;
// }
// //voor Verkeessituatie in te lezen!
//  TEST(InlezenTest, VerkeersSituatieWordtCorrectIngelezen) {
//     TrafficSim trafficsim = parseFile("test/test_verkeersinlezing.xml");
//     trafficsim.TestingModeOn();
//
//     std::vector<Baan> banen = trafficsim.get_banen();
//     ASSERT_EQ(banen.size(), size_t(1));
//     EXPECT_EQ(banen[0].naam, "Middelheimlaan");
//     EXPECT_EQ(banen[0].lengte, 500);
//
//     std::vector<Verkeerslicht> verkeerslichten = trafficsim.getVerkeerslichten();
//     ASSERT_EQ(verkeerslichten.size(), size_t(1));
//     EXPECT_EQ(verkeerslichten[0].baan, "Middelheimlaan");
//     EXPECT_EQ(verkeerslichten[0].positie, 400);
//     EXPECT_EQ(verkeerslichten[0].cyclus, 20);
//
//     std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
//     ASSERT_EQ(voertuigen.size(), size_t(2));
//
//     EXPECT_EQ(voertuigen[0].baan, "Middelheimlaan");
//     EXPECT_EQ(voertuigen[1].baan, "Middelheimlaan");
//     EXPECT_EQ(voertuigen[0].positie, 20);
//     EXPECT_EQ(voertuigen[1].positie, 0);
//     Voertuig::volgendeNummer = 1;
//  }
//  //VoertuigGen wordt ingelezen!
//  TEST(InlezenTest, VoertuiggeneratorWordtCorrectIngelezen) {
//     TrafficSim trafficsim = parseFile("test/test_voertuigGenInlezen.xml");
//     trafficsim.TestingModeOn();
//
//     std::vector<VoertuigGen> generators = trafficsim.get_VoertuigGen();
//     ASSERT_EQ(generators.size(), size_t(1));
//     EXPECT_EQ(generators[0].baan, "Middelheimlaan");
//     EXPECT_EQ(generators[0].freq, 5);
//     Voertuig::volgendeNummer = 1;
//  }
//  //Type auto inlezen!
//  TEST(InlezenTest, VoertuigenMetTypeWordenCorrectIngelezen) {
//     TrafficSim trafficsim = parseFile("test/test_voertuigTypeInlezen.xml");
//     trafficsim.TestingModeOn();
//
//     std::vector<Voertuig> voertuigen = trafficsim.getVoertuigen();
//     ASSERT_EQ(voertuigen.size(), size_t(4));
//     EXPECT_EQ(voertuigen[0].type, "bus");
//     EXPECT_EQ(voertuigen[1].type, "brandweerwagen");
//     EXPECT_EQ(voertuigen[2].type, "ziekenwagen");
//     EXPECT_EQ(voertuigen[3].type, "politiecombi");
//     Voertuig::volgendeNummer = 1;
//  }
//  //Bushalte inlezen!
//  TEST(InlezenTest, BushaltesWordenCorrectIngelezen) {
//     TrafficSim trafficsim = parseFile("test/test_bushalteInlezen.xml");
//     trafficsim.TestingModeOn();
//
//     std::vector<Bushalte> haltes = trafficsim.get_bushaltes();
//     ASSERT_EQ(haltes.size(), size_t(1));
//     EXPECT_EQ(haltes[0].baan, "Middelheimlaan");
//     EXPECT_EQ(haltes[0].positie, 250);
//     EXPECT_EQ(haltes[0].wachttijd, 20);
//     Voertuig::volgendeNummer = 1;
//  }
//  //Kruispunt inlezen!
//  TEST(InlezenTest, KruispuntenWordenCorrectIngelezen) {
//     TrafficSim trafficsim = parseFile("test/test_kruispuntInlezen.xml");
//     trafficsim.TestingModeOn();
//
//     std::vector<Kruispunt> kruispunten = trafficsim.get_kruispunten();
//     ASSERT_EQ(kruispunten.size(), size_t(2));
//
//     EXPECT_EQ(kruispunten[0].fromBaan, "Middelheimlaan");
//     EXPECT_EQ(kruispunten[0].fromPositie, 250);
//     EXPECT_EQ(kruispunten[0].toBaan, "Floralienlaan");
//     EXPECT_EQ(kruispunten[0].toPositie, 500);
//
//     EXPECT_EQ(kruispunten[1].fromBaan, "Middelheimlaan");
//     EXPECT_EQ(kruispunten[1].fromPositie, 500);
//     EXPECT_EQ(kruispunten[1].toBaan, "Beukenlaan");
//     EXPECT_EQ(kruispunten[1].toPositie, 500);
//     Voertuig::volgendeNummer = 1;
//  }
//  TEST(InlezenTest, VoertuigVerwijderen) {
//     TrafficSim trafficsim = parseFile("test/test_VoertuigVerwijderen.xml");
//     trafficsim.TestingModeOn();
//     ASSERT_EQ(trafficsim.getVoertuigen().size(), size_t(2));
//     trafficsim.Simulate(1);
//     EXPECT_EQ(trafficsim.getVoertuigen().size(),size_t(1));
//     Voertuig::volgendeNummer = 1;
//  }
//
//  TEST(BerekenSnelheidTest, SnelheidEnPositie) {
//     TrafficSim trafficsim = parseFile("test/test_VoertuigBerekenSnelheidEnPositie.xml");
//     trafficsim.TestingModeOn();
//     Voertuig &voertuig= trafficsim.getVoertuigen()[0];
//     voertuig.snelheid=6;
//     voertuig.versnelling=1.03;
//     trafficsim.setDeltaTime(1.0);
//     trafficsim.berekenSnelheid(voertuig);
//     EXPECT_EQ(voertuig.snelheid, 7.03);
//     EXPECT_EQ(voertuig.positie, 27.545);
//     Voertuig::volgendeNummer = 1;
//  }
//
// TEST(BerekenSnelheidTest, Versnelling) {
//     TrafficSim trafficsim = parseFile("test/test_VoertuigBerekenVersnelling.xml");
//     trafficsim.TestingModeOn();
//     Voertuig &voertuig = trafficsim.getVoertuigen()[0];
//     double versnelling = voertuig.versnelling;
//     voertuig.snelheid = 14;
//
//     trafficsim.berekenVersnelling(voertuig);
//     EXPECT_GT(voertuig.versnelling, versnelling);
//     // EXPECT_EQ(voertuig.versnelling, 0.7114786517627);
//     // EXPECT_EQ(voertuig1.versnelling, 0.3298317128635);
//
//     Voertuig::volgendeNummer = 1;
// }
TEST(VerkeerslichtTest, LichtSwitch) {
    TrafficSim trafficsim = parseFile("test/test_verkeerslichtSwitch.xml");
    trafficsim.TestingModeOn();
    Verkeerslicht verkeerslicht1 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht1.kleur, "rood");
    trafficsim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht.kleur, "groen");
    trafficsim.Simulate(verkeerslicht.cyclus+1);
    Verkeerslicht verkeerslicht2 = trafficsim.getVerkeerslichten()[0];
    EXPECT_EQ(verkeerslicht2.kleur, "rood");
}




int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
