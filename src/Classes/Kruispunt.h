//
// Created by grama on 5/13/2025.
//

#ifndef KRUISPUNT_H
#define KRUISPUNT_H
#include <string>
#include "Voertuig.h"
#include "Baan.h"
#include "DesignByContract.h"


class Kruispunt {
    Baan* fromBaan= nullptr;
    int fromPositie;
    Baan* toBaan= nullptr;
    int toPositie;
public:
    Baan* from_baan() const {
        return fromBaan;
    }

    void set_from_baan(Baan * from_baan) {
        fromBaan = from_baan;
    }

    int from_positie() const {
        return fromPositie;
    }

    void set_from_positie(int from_positie) {
        fromPositie = from_positie;
    }

    Baan* to_baan() const {
        return toBaan;
    }

    void set_to_baan(Baan*to_baan) {
        toBaan = to_baan;
    }

    int to_positie() const {
        return toPositie;
    }

    void set_to_positie(int to_positie) {
        toPositie = to_positie;
    }

    void kruispuntSim(Voertuig& voertuig, std::vector<Baan>& banen);
};



#endif //KRUISPUNT_H
