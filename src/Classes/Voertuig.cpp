//
// Created by grama on 5/13/2025.
//

#include "Voertuig.h"

void Voertuig::lowerVolgendeNummer(){
    volgendeNummer--;
}

void Voertuig::setType(const std::string& nieuwType) {
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

void Voertuig::berekenVersnelling(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    int indexLijst = voertuig.voertuig_nummer() - 1;
    if (indexLijst > 0) {
        if (voertuig.gestopt1()) {
            voertuig.set_versnelling(-(voertuig.maxremfactor1()*voertuig.snelheid1()/voertuig.maxversnelling1()));
        } else {
            int indexVoertuig2 = indexLijst - 1;
            Voertuig voertuig2 = voertuigen[indexVoertuig2];
            double volgafstand = voertuig2.positie1() - voertuig.positie1() - voertuig2.lengte1();
            double snelheidsverschil = voertuig.snelheid1() - voertuig2.snelheid1();
            double delta = (voertuig.fmin1() + std::max(0.0, voertuig.snelheid1() + ( (voertuig.snelheid1() * snelheidsverschil) / (2 * std::sqrt(voertuig.maxversnelling1() * voertuig.maxremfactor1())))))/ volgafstand;
            double versnelling = voertuig.maxversnelling1()*(1-pow(voertuig.snelheid1()/voertuig.maxsnelheid1(),4) - pow(delta,2));
            voertuig.set_versnelling(versnelling);
        }
    }
    else {
        if (voertuig.gestopt1()) {
            voertuig.set_versnelling(-(voertuig.maxremfactor1()*voertuig.snelheid1()/voertuig.maxversnelling1()));
        } else {
            double delta = 0;
            double versnelling = voertuig.maxversnelling1()*(1-pow(voertuig.snelheid1()/voertuig.maxsnelheid1(),4) - pow(delta,2));
            voertuig.set_versnelling(versnelling);
        }
    }
    ENSURE(std::isfinite(voertuig.versnelling1()), "Versnelling moet een geldig getal zijn.");
}
void Voertuig::berekenSnelheid(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    double snelheid = voertuig.snelheid1();
    double versnelling = voertuig.versnelling1();
    double formule = snelheid + (versnelling*DeltaTime);
    double positie = voertuig.positie1();
    /*if (snelheid>voertuig.mMaxsnelheid) {
        snelheid=voertuig.mMaxsnelheid;
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        voertuig.positie = positie;
    } else {*/
    if (formule < 0) {
        positie = positie - ((pow(snelheid, 2))/(2*versnelling));
        snelheid = 0;
        voertuig.set_positie(positie);
    }
    else {
        snelheid = snelheid + (versnelling*DeltaTime);
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        voertuig.set_positie(positie);
    }
    /*}*/
    voertuig.set_snelheid(snelheid);
    ENSURE(voertuig.snelheid1() >= 0, "Snelheid mag niet negatief zijn.");
    ENSURE(std::isfinite(voertuig.positie1()), "Positie moet een geldig getal zijn.");

}
void Voertuig::versnellen(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    voertuig.set_maxsnelheid(voertuig.m_Maxsnelheid());
    /*int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst == 0) {
        size_t indexVoertuig2 = indexLijst - 1;
        if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
            Voertuig& voertuig2 = voertuigen[indexVoertuig2];
            voertuig.maxsnelheid = voertuig2.mMaxsnelheid;
        }
    }*/
    ENSURE(voertuig.maxsnelheid1() == voertuig.m_Maxsnelheid(), "Voertuig moet zijn maximumsnelheid terug hebben.");
}
Voertuig Voertuig::vertragen(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    double s=voertuig.vertraagfactor1();
    voertuig.set_maxsnelheid(s*voertuig.m_Maxsnelheid());
    return voertuig;
    ENSURE(voertuig.maxsnelheid1() < voertuig.m_Maxsnelheid(), "Na vertraging moet maxsnelheid lager zijn.");
}