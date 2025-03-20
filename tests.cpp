//
// Created by jonas on 3/17/2025.
//

#include <gtest/gtest.h>
#include "main.cpp"

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
                {"Baan1", 50, 30, "rood", "groen", "rood"}
            },
            {
                {"Baan1", 4, 4, 0, 16.6, 1.44, 0, 0, 0.4, 50, 15, 1, 4.61, 16.6}
            },
            {
                {"Baan1", 10}
            }
        ) {}
};

TEST_F(TrafficSimTest, TrafficLightSwitchTest) {
    auto& verkeerslicht = trafficSim.getVerkeerslichten()[0];

    ASSERT_EQ(verkeerslicht.kleur, "rood");

    trafficSim.verkeerslichtSim(verkeerslicht);

    ASSERT_EQ(verkeerslicht.kleur, "groen");

    trafficSim.verkeerslichtSim(verkeerslicht);
    ASSERT_EQ(verkeerslicht.kleur, "rood");
}

TEST_F(TrafficSimTest, VehicleRemovalTest) {
    trafficSim.Simulate();

    ASSERT_TRUE(trafficSim.getVoertuigen().empty());
}

/*TEST_F(TrafficSimTest, VehicleGenerationTest) {
    trafficSim.simVoertuiggenerator();

    ASSERT_GT(trafficSim.getVoertuigen().size(), 1);
}*/