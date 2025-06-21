//
// Created by grama on 5/13/2025.
//

#include "VoertuigGen.h"
void VoertuigGen::simVoertuiggenerator() {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigengen.empty(), "Er is geen voertuiggenerator aanwezig.");
    for (auto& generator : voertuigengen) {
        int laatsteTijd = ceil(time - generator.laatste_tijd());
        if (laatsteTijd > generator.freq1()) {
            bool vrij = true;
            for (const auto& voertuig : voertuigen) {
                if (voertuig.baan1() == generator.baan1() && 0 <= voertuig.positie1() && voertuig.positie1() <= 2 * voertuig.lengte1()) {
                    vrij = false;
                    break;
                }
            }
            if (vrij){
                Voertuig nieuwVoertuig;
                nieuwVoertuig.set_baan(generator.baan1());
                nieuwVoertuig.set_positie(0);
                voertuigen.push_back(nieuwVoertuig);
                generator.set_laatste_tijd(time);
            }
        }
    }
}