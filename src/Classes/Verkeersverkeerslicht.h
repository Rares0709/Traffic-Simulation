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
    Baan*baan=nullptr;
    int positie = 0;
    int cyclus = 0;
    std::string rood="rood";
    std::string groen="groen";
    std::string kleur="rood";
    double laatsteTijd = 0;
    std::vector<Voertuig> voertuigenVoorLicht;

public:
    void set_positie(int positie);

    void set_cyclus(int cyclus);

    void set_baan(Baan* baan);

    Baan* baan1() const;

    int positie1() const;

    int cyclus1() const;

    std::string rood1() const;

    std::string groen1() const;

    std::string kleur1() const;

    void set_kleur(std::string kleurstring);

    double laatste_tijd() const;

    void set_laatsteTijd(double laatstetijd);

    std::vector<Voertuig> voertuigen_voor_licht() const;

    void set_voertuigen_voor_licht(const std::vector<Voertuig> &voertuigen_voor_licht);

    void voeg_voertuigvoorlicht(Voertuig &voertuig);

    void clear_voertuigvoorlicht();

    /**
     * Deze functie zorgt ervoor wat de auto's doen op basis van de cyclus van het verkeerslicht en deze functie checkt of het voertuig een prioriteitsvoertuig is.
     * @param verkeerslicht is het verkeerslicht.
     */
    /**
     *@author Rares Grama
     *@author Ilyas Sefiani
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void verkeerslichtSim(Verkeersverkeerslicht& verkeerslicht, std::vector<Voertuig> voertuigen, double currTime, bool testingMode = false);
    /**
     *Deze functie zorgt ervoor wat de auto's doen op basis van de cyclus van het verkeerslicht en deze functie checkt of het voertuig een prioriteitsvoertuig is.
     */
    /**
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void checkverkeerslicht(std::vector<Voertuig>* voertuigen, bool testingMode=false);

};



#endif //VERKEERSVERKEERSLICHT_H
