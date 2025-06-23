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
    Baan* baan1() const;

    void set_baan(Baan*baan);

    int freq1() const;

    void set_freq(int freq);

    int laatste_tijd() const;

    void set_laatste_tijd(int laatste_tijd);
    /**
     *Deze functie genereert voertuigen.
     */
    /**
     *@author Rares Grama
     *@author Ilyas Sefiani
     *@date /
     *@version
     */
    void simVoertuiggenerator(std::vector<Voertuig>* voertuigen, double currTime, bool testingMode=false);

};



#endif //VOERTUIGGEN_H
