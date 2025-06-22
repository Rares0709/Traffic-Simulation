//
// Created by grama on 5/13/2025.
//

#ifndef VERKEERSVERKEERSLICHT_H
#define VERKEERSVERKEERSLICHT_H

// #include "Classes/Voertuig.h"
#include <vector>
#include "Voertuig.h"
#include "DesignByContract.h"
#include <iostream>


class Verkeersverkeerslicht {
    std::string baan;
    int positie = 0;
    int cyclus = 0;
    std::string rood="rood";
    std::string groen="groen";
    std::string kleur="rood";
    int laatsteTijd = 0;
    std::vector<Voertuig> voertuigenVoorLicht;
    bool testingMode = false;

public:
    void set_positie(int positie) {
        this->positie = positie;
    }

    void set_cyclus(int cyclus) {
        this->cyclus = cyclus;
    }
    void set_baan(const std::string &baan) {
        this->baan = baan;
    }
    std::string baan1() const {
        return baan;
    }

    int positie1() const {
        return positie;
    }

    int cyclus1() const {
        return cyclus;
    }

    std::string rood1() const {
        return rood;
    }

    std::string groen1() const {
        return groen;
    }

    std::string kleur1() const {
        return kleur;
    }
    void set_kleur(std::string kleurstring) {
        kleur=kleurstring;
    }

    int laatste_tijd() const {
        return laatsteTijd;
    }
    void set_laatsteTijd(int laatstetijd) {
        laatsteTijd=laatstetijd;

    }

    std::vector<Voertuig> voertuigen_voor_licht() const {
        return voertuigenVoorLicht;
    }

    void set_voertuigen_voor_licht(const std::vector<Voertuig> &voertuigen_voor_licht) {
        voertuigenVoorLicht = voertuigen_voor_licht;
    }

    void voeg_voertuigvoorlicht(Voertuig &voertuig) {
        voertuigenVoorLicht.push_back(voertuig);
    }
    void clear_voertuigvoorlicht() {
        voertuigen_voor_licht().clear();
    }
    void verkeerslichtSim(Verkeersverkeerslicht& verkeerslicht, std::vector<Voertuig> voertuigen, double currTime, bool testingMode = false);
    /**
     *Deze functie zorgt ervoor wat de auto's doen op basis van de cyclus van het verkeerslicht en deze functie checkt of het voertuig een prioriteitsvoertuig is.
     */
    /**
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void checkverkeerslicht(std::vector<Voertuig>* voertuigen);
    void TestingModeOn() {
        testingMode = true;
    }

};



#endif //VERKEERSVERKEERSLICHT_H
