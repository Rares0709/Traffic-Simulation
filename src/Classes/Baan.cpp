//
// Created by grama on 5/13/2025.
//

#include "Baan.h"
int Baan::getBaanLengte(std::string &baannaam, std::vector<Baan> &banen) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    for (Baan& b : banen) {
        if (b.naam1() == baannaam) {
            return b.lengte1();
        }
    }
    return 0;
}