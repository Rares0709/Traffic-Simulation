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