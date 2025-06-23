//
// Created by grama on 5/13/2025.
//

#include "Baan.h"
std::string Baan::naam1() const {
    ENSURE(this->naam == naam, "Getter geeft niet de juiste naam mee!");
    return naam;
}

void Baan::set_naam(const std::string &naam) {
    this->naam = naam;
    ENSURE(this->naam==naam, "De doorgegeven naam werd niet correct geset.");
}

int Baan::lengte1() const {
    ENSURE(this->lengte == lengte, "Getter geeft niet de juiste lengte mee!");
    return lengte;
}

void Baan::set_lengte(int lengte) {
    REQUIRE(lengte >= 0, "Lengte moet positief zijn of 0");
    this->lengte = lengte;
    ENSURE(this->lengte==lengte, "De doorgegeven lengte werd niet correct geset.");
}

int Baan::breedte1() const {
    ENSURE(this->breedte==breedte, "Getter geeft niet de juiste breedte mee!");
    return breedte;
}

void Baan::set_breedte(int breedte) {
    REQUIRE(breedte >= 0, "Breedte moet positief zijn of 0");
    this->breedte = breedte;
    ENSURE(this->breedte==breedte, "De doorgegeven Breedte werd niet correct geset.");
}