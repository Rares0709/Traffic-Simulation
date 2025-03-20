//
// Created by grama on 2/27/2025.
//

#include "main.h"
#include <cmath>
#include <vector>
#include "TrafficSimulation.h"
#include "ParseFile.h"

int main() {
    TrafficSim traffic = parseFile("test/test1.xml");
    traffic.Simulate();
    return 0;
}
