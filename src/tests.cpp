//
// Created by jonas on 3/17/2025.
//

#include <gtest/gtest.h>
#include "ParseFile.h"

class TrafficSimTest : public ::testing::Test {
protected:
    TrafficSim trafficSim;
    TrafficSimTest()
        :trafficSim(parseFile("test/test1.xml")){}
    virtual void SetUp() {
        trafficSim.setTime(0.0);
    }
};

/*class VoertuigGenSimTest : public ::testing::Test {
protected:
    TrafficSim sim;
    VoertuigGenSimTest()
        :sim(parseFile("test/test1.xml")){}
    virtual void SetUp() {
        sim.setTime(0);
    }
};*/
// Test that verifies if a vehicle is generated when the time exceeds the vehicle generator's frequency
/*TEST_F(TrafficSimTest, GeenNieuwVoertuigBijBezetting) {
    // Controleer begin: er zijn initieel 2 voertuigen
    ASSERT_EQ(trafficSim.getVoertuigen().size(), 2u);

    // Simuleer voertuiggenerator
    trafficSim.simVoertuiggenerator();

    // Na oproep mag er geen nieuw voertuig zijn toegevoegd, want positie 0 is al bezet
    EXPECT_EQ(trafficSim.getVoertuigen().size(), 2u);
}*/
//test if lightcolor switches
TEST_F(TrafficSimTest, TrafficLightSwitchTest) {
    Verkeerslicht verkeerslicht1 = trafficSim.getVerkeerslichten()[0];
    trafficSim.Simulate(verkeerslicht1.cyclus+1);
    Verkeerslicht verkeerslicht = trafficSim.getVerkeerslichten()[0];
    if (trafficSim.getTime() > verkeerslicht.cyclus) {
        ASSERT_NE(verkeerslicht.kleur, verkeerslicht1.kleur);
    }
}

//defective test
/*TEST_F(TrafficSimTest, VehicleRemovalTest) {
    trafficSim.Simulate();

    ASSERT_TRUE(trafficSim.getVoertuigen().empty());
}*/

/*TEST_F(TrafficSimTest, VehicleGenerationTest) {
    trafficSim.simVoertuiggenerator();

    ASSERT_GT(trafficSim.getVoertuigen().size(), 1);
}*/
TEST(ParseFileTest, ValidInputFile) {
    TrafficSim sim = parseFile("test/test1.xml");

    ASSERT_FALSE(sim.getVoertuigen().empty());
    ASSERT_FALSE(sim.get_banen().empty());
    //ASSERT_FALSE(sim.getVerkeerslichten().empty());
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}