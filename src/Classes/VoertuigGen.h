//
// Created by grama on 5/13/2025.
//

#ifndef VOERTUIGGEN_H
#define VOERTUIGGEN_H
#include <string>
#include "DesignByContract.h"

class VoertuigGen {
    std::string baan;
    int freq = 0;
    int laatsteTijd=0;
public:
    std::string baan1() const {
        return baan;
    }

    void set_baan(const std::string &baan) {
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
    void simVoertuiggenerator();

    std::vector<VoertuigGen> get_VoertuigGen() const {
        return voertuigengen;
    }

    void set_voertuigengen(const std::vector<VoertuigGen> &voertuigengen) {
        this->voertuigengen = voertuigengen;
    }
};



#endif //VOERTUIGGEN_H
