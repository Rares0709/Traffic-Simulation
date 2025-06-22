//
// Created by jonas on 3/20/2025.
//

#ifndef TRAFFICSIMULATION_H
#define TRAFFICSIMULATION_H

#include <iostream>
#include <fstream>
// #include "structs.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Classes/Baan.h"
#include "Classes/Bushalte.h"
#include "Classes/Kruispunt.h"
#include "Classes/Verkeersverkeerslicht.h"
#include "Classes/Voertuig.h"
#include "Classes/VoertuigGen.h"

class TrafficSim {
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    double time = 0.0;
    double DeltaTime = 0.0166;
    std::vector<Voertuig> toDelete;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    bool testingMode = false;
public:
    /**
     * Deze functie simuleert de verkeerssituatie door alle voertuigen te verwerken en de tijd te verhogen.
     */
    /**
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void Simulate(int duration = -1);

    TrafficSim(const std::vector<Baan> &banen, const std::vector<Verkeersverkeerslicht> &verkeerslichten,
        const std::vector<Voertuig> &voertuigen, const std::vector<VoertuigGen> &voertuigengen, const std::vector<Bushalte> &bushaltes, const std::vector<Kruispunt> &kruispunten)
        : banen(banen),
          verkeerslichten(verkeerslichten),
          voertuigen(voertuigen),
          voertuigengen(voertuigengen),
          bushaltes(bushaltes),
          kruispunten(kruispunten){
    }
    /**
     * Deze functie berekent de versnelling van het voertuig.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Ilyas Sefiani
     *@author Rares Grama
     *@date /
     *@version
     */
    void berekenVersnelling(Voertuig& voertuig);
    /**
     * Deze functie berekent de snelheid van het voertuig.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Ilyas Sefiani
     *@author Rares Grama
     *@date /
     *@version
     */
    void berekenSnelheid(Voertuig& voertuig);
    /**
     * Deze functie berekent hoe het voertuig kan versnellen.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Ilyas Sefiani
     *@date /
     *@version
     */
    void versnellen(Voertuig& voertuig);
    /**
     * Deze functie berekent hoe het voertuig kan vertragen.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Rares Grama
     *@date /
     *@version
     */
    Voertuig vertragen(Voertuig& voertuig);
    /**
     * Deze functie bekijkt of het voertuig in zijn baan mag blijven.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Ilyas Sefiani
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void geldig(Voertuig& voertuig);
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
    void verkeerslichtSim(Verkeersverkeerslicht& verkeerslicht);
    /**
     *Deze functie zorgt ervoor wat de auto's doen op basis van de cyclus van het verkeerslicht en deze functie checkt of het voertuig een prioriteitsvoertuig is.
     */
    /**
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void checkverkeerslicht();
    /**
     *Deze functie genereert voertuigen.
     */
    /**
     *@author Rares Grama
     *@author Ilyas Sefiani
     *@date /
     *@version
     */
    void simVoertuiggenerator();

    std::vector<Baan> get_banen() const {
        return banen;
    }

    void setBanen(std::vector<Baan> &banen) {
        this->banen = banen;
    }
    /**
   * Deze functie verwijdert voertuigen.
   * @param voertuig is het voertuig.
   */
    /**
     *@author Jonas Saelens
     *@author Ilyas Sefiani
     *@date /
     *@version
     */
    void wagenToDelete(Voertuig &voertuig);

    void voegbaantoe(Baan &baan) {
        this->banen.push_back(baan);
    }
    int getPositie(Voertuig voertuig) {
       return voertuig.positie1();
    }
    int getSnelheid(Voertuig voertuig) {
        return voertuig.snelheid1();
    }
    void setDeltaTime(double dt) {
        DeltaTime = dt;
    }
    /**
     * Deze functie geeft de lengte van de baan weer waarop het voertuig rijdt.
     * @param baannaam is de naam van de baan.
     * @param banen is de verzameling van alle banen.
     */
    /**
    *@author Ilyas Sefiani
    *@date /
    *@version
    */
    int getBaanLengte(std::string & baannaam, std:: vector<Baan>&banen);
    /**
     * Deze functie verhoogt de tijd.
     */
    /**
    *@author Ilyas Sefiani
    *@date /
    *@version
    */
    void verhoogTijd();
    /**
    * Deze functie kijkt of er getest wordt met Gtest.
    */
    /**
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void TestingModeOn() {
        testingMode = true;
    }

    void setTime(double time) {
        this->time = time;
    }
    double& getTime() {
        return time;
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

    std::vector<Verkeersverkeerslicht> getVerkeerslichten() const {
        return verkeerslichten;
    }

    void setVerkeerslichten(const std::vector<Verkeersverkeerslicht> &verkeerslichten) {
        this->verkeerslichten = verkeerslichten;
    }

    void voegverkeerslichttoe(Verkeersverkeerslicht licht) {
        this->verkeerslichten.push_back(licht);
    }

    std::vector<Voertuig>& getVoertuigen() {
        return voertuigen;
    }

    std::vector<VoertuigGen> get_VoertuigGen() const {
        return voertuigengen;
    }

    void set_voertuigengen(const std::vector<VoertuigGen> &voertuigengen) {
        this->voertuigengen = voertuigengen;
    }

    void setVoertuigen(const std::vector<Voertuig> &voertuigen) {
        this->voertuigen = voertuigen;
    }

    std::vector<Bushalte> get_bushaltes() const {
        return bushaltes;
    }

    void set_bushaltes(const std::vector<Bushalte> &bushaltes) {
        this->bushaltes = bushaltes;
    }

    std::vector<Kruispunt> get_kruispunten() const {
        return kruispunten;
    }

    void set_kruispunten(const std::vector<Kruispunt> &kruispunten) {
        this->kruispunten = kruispunten;
    }

    void voegvoertuigtoe(Voertuig voertuig) {
        this->voertuigen.push_back(voertuig);
    }
    /**
     * Deze functie print uit wat er moet gedaan worden in 2.1
     */
    /**
    *@author Jonas Saelens
    *@date /
    *@version /
    */
    void print() const;
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
    void kruispuntSim(/*std::vector<Kruispunt> kruispunten, */Voertuig& voertuig/*, std::vector<Baan>& banen*/);


};



#endif //TRAFFICSIMULATION_H
