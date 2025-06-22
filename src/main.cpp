//
// Created by grama on 2/27/2025.
//

#include "main.h"
#include "ParseFile.h"

int main() {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/test1.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim traffic(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    traffic.Simulate();
    return 0;
}
