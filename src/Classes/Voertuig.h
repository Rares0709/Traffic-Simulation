//
// Created by grama on 5/13/2025.
//

#ifndef VOERTUIG_H
#define VOERTUIG_H



class Voertuig {
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
    bool gestopt = false;
    bool gedraait = false;
    int timestop = 0;
    bool recentGestopt= false;
    std::string type = "auto"; // default is auto

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

    void lowerVolgendeNummer();

    void setType(const std::string& nieuwType);
};



#endif //VOERTUIG_H
