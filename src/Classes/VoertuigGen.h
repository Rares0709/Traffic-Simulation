//
// Created by grama on 5/13/2025.
//

#ifndef VOERTUIGGEN_H
#define VOERTUIGGEN_H



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
};



#endif //VOERTUIGGEN_H
