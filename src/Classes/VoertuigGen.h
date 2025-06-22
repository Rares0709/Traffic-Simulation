//
// Created by grama on 5/13/2025.
//

#ifndef VOERTUIGGEN_H
#define VOERTUIGGEN_H
#include <string>
#include "DesignByContract.h"
#include <cmath>
#include "Voertuig.h"
class VoertuigGen {
    Baan*baan= nullptr;
    int freq = 0;
    int laatsteTijd=0;
public:
    Baan* baan1() const {
        return baan;
    }

    void set_baan(Baan*baan) {
        this->baan = baan;
    }

    int freq1() const {
        return freq;
    }

    void set_freq(int freq) {
        this->freq = freq;
    }

    int laatste_tijd() const {
        return laatsteTijd;
    }

    void set_laatste_tijd(int laatste_tijd) {
        laatsteTijd = laatste_tijd;
    }
    /**
     *Deze functie genereert voertuigen.
     */
    /**
     *@author Rares Grama
     *@author Ilyas Sefiani
     *@date /
     *@version
     */
    void simVoertuiggenerator(std::vector<Voertuig>* voertuigen, double currTime);

};



#endif //VOERTUIGGEN_H
