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
    Baan* from_baan() const;

    void set_from_baan(Baan * from_baan);

    int from_positie() const;

    void set_from_positie(int from_positie);

    Baan* to_baan() const;

    void set_to_baan(Baan*to_baan);

    int to_positie() const;

    void set_to_positie(int to_positie);
    /**
    * Deze functie simuleert kruispunten.
    * @param voertuig is het voertuig.
    */
    /**
     *@author Jonas Saelens
     *@author Ilyas Sefiani
     *@date /
     *@version
     */
    void kruispuntSim(Voertuig& voertuig, std::vector<Baan>& banen, bool testingMode=false);
};



#endif //KRUISPUNT_H
