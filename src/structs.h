//
// Created by jonas on 3/20/2025.
//

#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>


struct Baan {
    std::string naam;
    int lengte;
};

struct Verkeerslicht {
    std::string baan;
    int positie = 0;
    int cyclus = 0;
    std::string rood="rood";
    std::string groen="groen";
    std::string kleur="rood";
};

struct Voertuig {
    Voertuig(const std::string &baan, int fmin, int lengte, double positie, double maxsnelheid, double maxversnelling,
        double snelheid, double versnelling, double vertraagfactor, int vertraagafstand, int stopafstand,
        int voertuig_nummer, double maxremfactor, double maxsnelheid1)
        : baan(baan),
          fmin(fmin),
          lengte(lengte),
          positie(positie),
          mMaxsnelheid(maxsnelheid),
          maxversnelling(maxversnelling),
          snelheid(snelheid),
          versnelling(versnelling),
          vertraagfactor(vertraagfactor),
          vertraagafstand(vertraagafstand),
          stopafstand(stopafstand),
          voertuigNummer(voertuig_nummer),
          maxremfactor(maxremfactor),
          maxsnelheid(maxsnelheid1) {
    }

    std::string baan;
    int fmin = 4;
    int lengte = 4;
    double positie = 0;
    double mMaxsnelheid = 16.6;
    double maxversnelling = 1.44;
    double snelheid = 0;
    double versnelling = 0;
    static int volgendeNummer;
    double vertraagfactor = 0.4;
    int vertraagafstand = 50;
    int stopafstand = 15;
    int voertuigNummer = 1;
    double maxremfactor = 4.61;
    double maxsnelheid = 16.6;
    Voertuig() : voertuigNummer(volgendeNummer++) {
    }
};


struct VoertuigGen {
    //vermoedelijk voor later
    std::string baan;
    int freq = 0;
    int laatsteTijd=0;
};



#endif //STRUCTS_H
