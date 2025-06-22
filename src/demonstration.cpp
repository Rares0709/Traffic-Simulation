//
// Created by jonas on 6/22/2025.
//

#include <gtest/gtest.h>
#include "ParseFile.h"
TEST(Demonstratie, Verkeerssituatie_inlezen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/Demonstratie.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    trafficSim.TestingModeOn();

    std::cout<<"Aantal banen ingelezen: "<< banen.size()<<std::endl;
    std::cout<<"Aantal verkeerslichten ingelezen: "<< verkeerslichten.size()<<std::endl;
    std::cout<<"Aantal voertuigen ingelezen: "<< voertuigen.size()<<std::endl;
    std::cout<<"Aantal voertuiggenerators ingelezen: "<< voertuigengen.size()<<std::endl;
    std::cout<<"Aantal bushaltes ingelezen: "<< bushaltes.size()<<std::endl;
    std::cout<<"Aantal kruispunten ingelezen: "<< kruispunten.size()<<std::endl;
    ASSERT_EQ(banen.size(), 3u);
    ASSERT_EQ(verkeerslichten.size(), 1u);
    ASSERT_EQ(voertuigen.size(), 2u);
    ASSERT_EQ(voertuigengen.size(), 1u);
    ASSERT_EQ(bushaltes.size(), 1u);
    ASSERT_EQ(kruispunten.size(), 2u);

    Voertuig::resetVolgendeNummer();
}

TEST(Demonstratie, voertuigtype_inlezen) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/Demonstratie.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    trafficSim.TestingModeOn();
    std::vector<std::string> typeWagens;

    for (Voertuig &voertuig:voertuigen) {
        typeWagens.push_back(voertuig.type1());
        std::cout<<"Er werd een voertuig ingelezen met type: "<<voertuig.type1()<<std::endl;
    }
    Voertuig::resetVolgendeNummer();
}
TEST(Demonstratie, simpeleUitvoer) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/Demonstratie.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);

    trafficSim.print();
}

TEST(Demonstratie, rijdenVoertuig) {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    parseFile("test/Demonstratie.xml",&banen,&verkeerslichten,&voertuigen,&voertuigengen,&bushaltes,&kruispunten);
    TrafficSim trafficSim(banen,verkeerslichten,voertuigen,voertuigengen,bushaltes,kruispunten);
    trafficSim.TestingModeOn();
    for (Voertuig &voertuig:voertuigen) {
        std::cout<<"Originele positie van voertuig "<<voertuig.voertuig_nummer()<<": "<<voertuig.positie1() <<std::endl;
    }

    trafficSim.Simulate(10);
    for (Voertuig &voertuig:voertuigen) {
        std::cout<<"Positie van voertuig "<<voertuig.voertuig_nummer()<<" na de simulatie: "<<voertuig.positie1() <<std::endl;
    }
}






int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}