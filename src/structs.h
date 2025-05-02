//
// Created by jonas on 3/20/2025.
//

#ifndef STRUCTS_H
#define STRUCTS_H
#include <iostream>


struct Baan {
    std::string naam;
    int lengte;
    int breedte = 180;
};

struct Verkeerslicht {
    std::string baan;
    int positie = 0;
    int cyclus = 0;
    std::string rood="rood";
    std::string groen="groen";
    std::string kleur="rood";
    int laatsteTijd = 0;
};

struct Voertuig {
    Voertuig(const std::string &baan, int fmin, int lengte, double positie, double mMaxsnelheid, double maxversnelling,
             double snelheid, double versnelling, double vertraagfactor, int vertraagafstand, int stopafstand,
             int voertuigNummer, double maxremfactor, double maxsnelheid1, const std::string& type)
        : baan(baan),
          fmin(fmin),
          lengte(lengte),
          positie(positie),
          mMaxsnelheid(mMaxsnelheid),
          maxversnelling(maxversnelling),
          snelheid(snelheid),
          versnelling(versnelling),
          vertraagfactor(vertraagfactor),
          vertraagafstand(vertraagafstand),
          stopafstand(stopafstand),
          voertuigNummer(voertuigNummer),
          maxremfactor(maxremfactor),
          maxsnelheid(maxsnelheid1),
          type(type) {
        // type wordt ingesteld bij constructie
    }

    Voertuig() : voertuigNummer(volgendeNummer++) {}

    void lowerVolgendeNummer(){
        volgendeNummer--;
    }

    void setType(const std::string& nieuwType) {
        type = nieuwType;
        if (type == "auto") {
            lengte = 4;
            mMaxsnelheid = maxsnelheid = 16.6;
            maxversnelling = 1.44;
            maxremfactor = 4.61;
            fmin = 4;
        } else if (type == "bus") {
            lengte = 12;
            mMaxsnelheid = maxsnelheid = 11.4;
            maxversnelling = 1.22;
            maxremfactor = 4.29;
            fmin = 12;
        } else if (type == "brandweerwagen") {
            lengte = 10;
            mMaxsnelheid = maxsnelheid = 14.6;
            maxversnelling = 1.33;
            maxremfactor = 4.56;
            fmin = 10;
            prioriteit = true;
        } else if (type == "ziekenwagen") {
            lengte = 8;
            mMaxsnelheid = maxsnelheid = 15.5;
            maxversnelling = 1.44;
            maxremfactor = 4.47;
            fmin = 8;
            prioriteit = true;
        } else if (type == "politiecombi") {
            lengte = 6;
            mMaxsnelheid = maxsnelheid = 17.2;
            maxversnelling = 1.55;
            maxremfactor = 4.92;
            fmin = 6;
            prioriteit = true;
        } else {
            exit(1);
        }
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
    bool prioriteit = false;
    int timestop = 0;
    std::string type = "auto"; // default is auto
};


struct VoertuigGen {
    //vermoedelijk voor later
    std::string baan;
    int freq = 0;
    int laatsteTijd=0;
};

struct Bushalte {
    std::string baan;
    int positie = 0;
    int wachttijd =0;
};

struct Kruispunt {
    std::string fromBaan;
    int fromPositie;
    std::string toBaan;
    int toPositie;
};



#endif //STRUCTS_H
