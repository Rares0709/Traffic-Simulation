//
// Created by grama on 5/13/2025.
//

#ifndef BAAN_H
#define BAAN_H
#include <string>
#include <vector>
#include "DesignByContract.h"



class Baan {
    std::string naam;
    int lengte;
    int breedte = 180;
public:
    std::string naam1() const;

    void set_naam(const std::string &naam);

    int lengte1() const;

    void set_lengte(int lengte);

    int breedte1() const;

    void set_breedte(int breedte);
};



#endif //BAAN_H
