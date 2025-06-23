//
// Created by grama on 5/13/2025.
//

#ifndef BUSHALTE_H
#define BUSHALTE_H
#include <string>

#include "Baan.h"

class Voertuig;


class Bushalte {
    Baan*baan=nullptr;
    int positie = 0;
    int wachttijd =0;
public:
    Baan *baan1() const;

    void set_baan(Baan *baan);

    int positie1() const;

    void set_positie(int positie);

    int wachttijd1() const;

    void set_wachttijd(int wachttijd);
    /**
    * Deze functie checkt of een bus moet stoppen aan een bushalte.
    * @param bus is het voertuig.
    */
    /**
     *@author Rares Grama
     *@date /
     *@version
     */
    void simBushaltes(Voertuig& bus, bool testingMode=false);

};



#endif //BUSHALTE_H
