//
// Created by grama on 5/13/2025.
//

#ifndef BUSHALTE_H
#define BUSHALTE_H
#include <string>
#include "Voertuig.h"


class Bushalte {
    std::string baan;
    int positie = 0;
    int wachttijd =0;
public:
    std::string baan1() const {
        return baan;
    }

    void set_baan(const std::string &baan) {
        this->baan = baan;
    }

    int positie1() const {
        return positie;
    }

    void set_positie(int positie) {
        this->positie = positie;
    }

    int wachttijd1() const {
        return wachttijd;
    }

    void set_wachttijd(int wachttijd) {
        this->wachttijd = wachttijd;
    }
    /**
    * Deze functie checkt of een bus moet stoppen aan een bushalte.
    * @param bus is het voertuig.
    */
    /**
     *@author Rares Grama
     *@date /
     *@version
     */
    void simBushaltes(Voertuig &bus);

};



#endif //BUSHALTE_H
