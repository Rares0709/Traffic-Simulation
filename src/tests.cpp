//
// Created by jonas on 3/17/2025.
//

#include <gtest/gtest.h>
#include "ParseFile.h"

class TrafficSimTest : public ::testing::Test {
protected:
    TrafficSim trafficSim;

    TrafficSimTest()
        : trafficSim(
            {
                {"Baan1", 100},
                {"Baan2", 150}
            },
            {
                {"Baan1", 50, 25, "rood", "groen", "rood"}
            },
            {
                {"Baan1", 4, 4, 0, 16.6, 1.44, 0, 0, 0.4, 50, 15, 1, 4.61, 16.6}
            },
            {
                {"Baan1", 10}
            }
        ) {}
    virtual void SetUp() {
        trafficSim.setTime(30.0);
    }
};

class VoertuigGenSimTest : public ::testing::Test {
protected:
    TrafficSim sim;
    VoertuigGenSimTest()
        :sim(parseFile("test/test1.xml")){}
    virtual void SetUp() {
        sim.setTime(0);
    }
};
// Test that verifies if a vehicle is generated when the time exceeds the vehicle generator's frequency
TEST_F(VoertuigGenSimTest, GeenNieuwVoertuigBijBezetting) {
    // Controleer begin: er zijn initieel 2 voertuigen
    ASSERT_EQ(sim.getVoertuigen().size(), 2u);

    // Simuleer voertuiggenerator
    sim.simVoertuiggenerator();

    // Na oproep mag er geen nieuw voertuig zijn toegevoegd, want positie 0 is al bezet
    EXPECT_EQ(sim.getVoertuigen().size(), 2u);
}

/*TEST_F(TrafficSimTest, TrafficLightSwitchTest) {
    auto& verkeerslicht = trafficSim.getVerkeerslichten()[0];

    ASSERT_EQ(verkeerslicht.kleur, "rood");

    trafficSim.verkeerslichtSim(verkeerslicht);

    ASSERT_EQ(verkeerslicht.kleur, "groen");

    trafficSim.verkeerslichtSim(verkeerslicht);
    ASSERT_EQ(verkeerslicht.kleur, "rood");
}*/

/*TEST_F(TrafficSimTest, VehicleRemovalTest) {
    trafficSim.Simulate();

    ASSERT_TRUE(trafficSim.getVoertuigen().empty());
}*/

/*TEST_F(TrafficSimTest, VehicleGenerationTest) {
    trafficSim.simVoertuiggenerator();

    ASSERT_GT(trafficSim.getVoertuigen().size(), 1);
}*/
/*TEST(ParseFileTest, ValidInputFile) {
    TrafficSim sim = parseFile("test/test1.xml");

    ASSERT_FALSE(sim.getVoertuigen().empty());
    ASSERT_FALSE(sim.get_banen().empty());
    ASSERT_FALSE(sim.getVerkeerslichten().empty());
}*/
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}