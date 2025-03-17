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
                {"Baan1", 4, 4, 0, 16.6, 1.44, 0, 0, 1, 0.4, 50, 15, 1, 4.61, 16.6}
            },
            {
                {"Baan1", 10}
            }
        ) {}

    void CheckVehiclePositionAndSpeed(int vehicleNum, double expectedPosition, double expectedSpeed) {
        auto& vehicle = trafficSim.get_voertuigen()[vehicleNum - 1];
        ASSERT_DOUBLE_EQ(vehicle.positie, expectedPosition);
        ASSERT_DOUBLE_EQ(vehicle.snelheid, expectedSpeed);
    }
};

TEST_F(TrafficSimTest, VehicleMovementTest) {
    trafficSim.Simulate();

    CheckVehiclePositionAndSpeed(1, 10.0, 2.0);
}

TEST_F(TrafficSimTest, TrafficLightSwitchTest) {
    auto& verkeerslicht = trafficSim.get_verkeerslichten()[0];

    ASSERT_EQ(verkeerslicht.kleur, "rood");

    trafficSim.verkeerslichtSim(verkeerslicht);

    ASSERT_EQ(verkeerslicht.kleur, "groen");

    trafficSim.verkeerslichtSim(verkeerslicht);
    ASSERT_EQ(verkeerslicht.kleur, "rood");
}

TEST_F(TrafficSimTest, VehicleRemovalTest) {
    trafficSim.Simulate();

    ASSERT_TRUE(trafficSim.get_voertuigen().empty());
}

TEST_F(TrafficSimTest, VehicleGenerationTest) {
    trafficSim.simVoertuiggenerator();

    ASSERT_GT(trafficSim.get_voertuigen().size(), 1);
}

TEST_F(TrafficSimTest, VehicleSpeedAndAccelerationTest) {
    trafficSim.Simulate();

    CheckVehiclePositionAndSpeed(1, 10.0, 5.0);
}