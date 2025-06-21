//
// Created by grama on 5/13/2025.
//

#include "Kruispunt.h"
void Kruispunt::kruispuntSim(/*std::vector<Kruispunt> kruispunten, */Voertuig& voertuig/*, std::vector<Baan>& banen*/) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!kruispunten.empty(), "Er bevindt zich geen kruispunt op de baan.");
    REQUIRE(banen.size()>=2, "Er moeten minstens 2 banen aanwezig zijn.");
    for (Kruispunt kruispunt: kruispunten) {
        int breedte = 0;
        if (!voertuig.gedraait1()) {
            if (kruispunt.from_baan() == voertuig.baan1()) {
                //int breedte;
                for (const Baan& b : banen) {
                    if (b.naam1() == kruispunt.from_baan()) {
                        breedte = b.breedte1();
                        break;
                    }
                }
                /*std::vector<std::string> baantje;
                baantje.push_back(kruispunt.fromBaan);
                baantje.push_back(kruispunt.toBaan);*/
                if (voertuig.positie1() >= kruispunt.from_positie() && voertuig.positie1() <= kruispunt.from_positie() + breedte) {
                    std::srand(std::time(0));
                    bool keuze = std::rand() % 2;
                    // voertuig.baan = baantje[keuze];
                    // voertuig.positie = baantje[]
                    if (keuze) {
                        voertuig.set_baan(kruispunt.to_baan());
                        voertuig.set_positie(kruispunt.to_positie());
                        voertuig.set_gedraait(true);
                    }
                }
            }
            else if (kruispunt.to_baan() == voertuig.baan1()) {
                for (const Baan& b : banen) {
                    if (b.naam1() == kruispunt.to_baan()) {
                        breedte = b.breedte1();
                        break;
                    }
                }
                /*std::vector<std::string> baantje;
                baantje.push_back(kruispunt.fromBaan);
                baantje.push_back(kruispunt.toBaan);*/
                if (voertuig.positie1() >= kruispunt.to_positie() && voertuig.positie1() <= kruispunt.to_positie() + breedte) {
                    std::srand(std::time(0));
                    bool keuze = std::rand() % 2;
                    // voertuig.baan = baantje[keuze];
                    // voertuig.positie = baantje[]
                    if (keuze) {
                        voertuig.set_baan(kruispunt.from_baan());
                        voertuig.set_positie(kruispunt.from_positie());
                        voertuig.set_gedraait(true);
                    }
                }
            }
        }
        else if (voertuig.baan1() == kruispunt.from_baan()) {
            for (auto& baan : banen) {
                if (kruispunt.from_baan() == baan.naam1()) {
                    if (voertuig.positie1() > kruispunt.from_positie() + baan.breedte1()) {
                        voertuig.set_gedraait(false);
                    }
                }
            }
        }
        else if (voertuig.baan1() == kruispunt.to_baan()) {
            for (auto& baan : banen) {
                if (kruispunt.to_baan() == baan.naam1()) {
                    if (voertuig.positie1() > kruispunt.to_positie() + baan.breedte1()) {
                        voertuig.set_gedraait(false);
                    }
                }
            }
        }
    }
    ENSURE(std::find_if(banen.begin(), banen.end(), [&](const Baan& b) { return b.naam1() == voertuig.baan1(); }) != banen.end(), "Voertuig moet op een bestaande baan blijven.");
}