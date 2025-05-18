//
// Created by grama on 5/13/2025.
//

#ifndef VERKEERSVERKEERSLICHT_H
#define VERKEERSVERKEERSLICHT_H

#include "Classes/Voertuig.h"

class Verkeersverkeerslicht {
    std::string baan;
    int positie = 0;
    int cyclus = 0;
    std::string rood="rood";
    std::string groen="groen";
    std::string kleur="rood";
    int laatsteTijd = 0;
    std::vector<Voertuig> voertuigenVoorLicht;
public:
    std::string baan1() const {
        return baan;
    }

    int positie1() const {
        return positie;
    }

    int cyclus1() const {
        return cyclus;
    }

    std::string rood1() const {
        return rood;
    }

    std::string groen1() const {
        return groen;
    }

    std::string kleur1() const {
        return kleur;
    }
    void set_kleur(std::string kleurstring) {
        kleur=kleurstring;
    }

    int laatste_tijd() const {
        return laatsteTijd;
    }
    void set_laatsteTijd(int laatstetijd) {
        laatsteTijd=laatstetijd;

    }

    std::vector<Voertuig> voertuigen_voor_licht() const {
        return voertuigenVoorLicht;
    }
    void voeg_voertuigvoorlicht(Voertuig &voertuig) {
        voertuigen_voor_licht().push_back(voertuig);
    }
};



#endif //VERKEERSVERKEERSLICHT_H
