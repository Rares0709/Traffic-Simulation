//
// Created by grama on 5/13/2025.
//

#include "VoertuigGen.h"
void VoertuigGen::simVoertuiggenerator(std::vector<Voertuig>* voertuigen, double currTime) {
    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!voertuigengen.empty(), "Er is geen voertuiggenerator aanwezig.");
    int laatsteTijd = ceil( currTime- this->laatste_tijd());
    if (laatsteTijd > this->freq1()) {
        bool vrij = true;
        for (const auto& voertuig : *voertuigen) {
            if (voertuig.baan1()->naam1() == this->baan1()->naam1() && 0 <= voertuig.positie1() && voertuig.positie1() <= 2 * voertuig.lengte1()) {
                vrij = false;
                break;
            }
        }
        if (vrij){
            Voertuig nieuwVoertuig;
            nieuwVoertuig.set_baan(this->baan1());
            nieuwVoertuig.set_positie(0);
            voertuigen->push_back(nieuwVoertuig);
            this->set_laatste_tijd(currTime);
        }
    }
}