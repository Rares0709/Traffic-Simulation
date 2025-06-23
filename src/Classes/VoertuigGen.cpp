//
// Created by grama on 5/13/2025.
//

#include "VoertuigGen.h"

Baan* VoertuigGen::baan1() const {
    return baan;
}

void VoertuigGen::set_baan(Baan* baan) {
    REQUIRE(baan != nullptr, "Baan mag niet null zijn.");
    this->baan = baan;
    ENSURE(this->baan == baan, "Baan is correct ingesteld.");
}

int VoertuigGen::freq1() const {
    return freq;
}

void VoertuigGen::set_freq(int freq) {
    REQUIRE(freq > 0, "Frequentie moet positief zijn.");
    this->freq = freq;
    ENSURE(this->freq == freq, "Frequentie is correct ingesteld.");
}

int VoertuigGen::laatste_tijd() const {
    return laatsteTijd;
}

void VoertuigGen::set_laatste_tijd(int laatste_tijd) {
    REQUIRE(laatste_tijd >= 0, "Laatste tijd moet positief of nul zijn.");
    this->laatsteTijd = laatste_tijd;
    ENSURE(this->laatsteTijd == laatste_tijd, "Laatste tijd is correct ingesteld.");
}

void VoertuigGen::simVoertuiggenerator(std::vector<Voertuig>* voertuigen, double currTime) {
    REQUIRE(voertuigen != nullptr, "De voertuigenlijst mag niet null zijn.");
    REQUIRE(currTime >= 0.0, "Huidige tijd moet positief zijn.");
    REQUIRE(this->baan1() != nullptr, "Voertuiggenerator moet aan een geldige baan gekoppeld zijn.");
    REQUIRE(this->freq1() > 0, "Frequentie moet positief zijn.");
    int laatsteTijd = ceil( currTime- this->laatste_tijd());
    if (laatsteTijd > this->freq1()) {
        bool vrij = true;
        for (const auto& voertuig : *voertuigen) {
            REQUIRE(voertuig.baan1() != nullptr, "Voertuig moet een geldige baan hebben.");
            if (voertuig.baan1()->naam1() == this->baan1()->naam1() && 0 <= voertuig.positie1() && voertuig.positie1() <= 2 * voertuig.lengte1()) {
                vrij = false;
                break;
            }
        }
        if (vrij){
            size_t origineleGrootte = voertuigen->size();

            Voertuig nieuwVoertuig;
            nieuwVoertuig.set_baan(this->baan1());
            nieuwVoertuig.set_positie(0);
            voertuigen->push_back(nieuwVoertuig);
            this->set_laatste_tijd(currTime);

            ENSURE(voertuigen->size() == origineleGrootte + 1, "Er is succesvol een voertuig toegevoegd.");
            ENSURE(voertuigen->back().positie1() == 0, "Het nieuwe voertuig start op positie 0.");
        }
    }
}