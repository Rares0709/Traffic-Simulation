//
// Created by grama on 5/13/2025.
//

#ifndef KRUISPUNT_H
#define KRUISPUNT_H
#include <string>
#include "DesignByContract.h"


class Kruispunt {
    std::string fromBaan;
    int fromPositie;
    std::string toBaan;
    int toPositie;
public:
    std::string from_baan() const {
        return fromBaan;
    }

    void set_from_baan(const std::string &from_baan) {
        fromBaan = from_baan;
    }

    int from_positie() const {
        return fromPositie;
    }

    void set_from_positie(int from_positie) {
        fromPositie = from_positie;
    }

    std::string to_baan() const {
        return toBaan;
    }

    void set_to_baan(const std::string &to_baan) {
        toBaan = to_baan;
    }

    int to_positie() const {
        return toPositie;
    }

    void set_to_positie(int to_positie) {
        toPositie = to_positie;
    }

    void kruispuntSim(/*std::vector<Kruispunt> kruispunten, */Voertuig& voertuig/*, std::vector<Baan>& banen*/);
};



#endif //KRUISPUNT_H
