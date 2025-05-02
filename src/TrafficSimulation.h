//
// Created by jonas on 3/20/2025.
//

#ifndef TRAFFICSIMULATION_H
#define TRAFFICSIMULATION_H

#include <iostream>
#include <fstream>
#include "structs.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

class TrafficSim {
public:
    /**
     * Deze functuie simuleert de verkeerssituatie door alle voertuigen te verwerken en de tijd te verhogen.
     */
    /**
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void Simulate(int duration = -1);

    TrafficSim(const std::vector<Baan> &banen, const std::vector<Verkeerslicht> &verkeerslichten,
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
     *@author Rares Grama
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
    void vertragen(Voertuig& voertuig);
    /**
     * Deze functie berekent hoe het voertuig kan stoppen.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Rares Grama
     *@author
     *@date /
     *@version
     */
    void stoppen(Voertuig& voertuig);
    /**
     * Deze functie bekijkt of het voertuig in zijn baan mag blijven..
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
     * Deze functie zorgt ervoor wat de auto's doen op basis van de cyclus van het verkeerslicht..
     * @param verkeerslicht is het voertuig.
     */
    /**
     *@author Rares Grama
     *@author Ilyas Sefiani
     *@date /
     *@version
     */
    void verkeerslichtSim(Verkeerslicht& verkeerslicht);
    /**
     * Deze functie genereert voertuigen.
     */
    /**
     *@author Rares Grama
     *@date /
     *@version
     */
    void checkverkeerslicht(Voertuig& voertuig);
    void simVoertuiggenerator();

    std::vector<Baan> get_banen() const {
        return banen;
    }

    void setBanen(const std::vector<Baan> &banen) {
        this->banen = banen;
    }

    void wagenToDelete(Voertuig &voertuig);

    void voegbaantoe(Baan baan) {
        this->banen.push_back(baan);
    }

    int getPositie(Voertuig voertuig) {
       return voertuig.positie;
    }
    int getSnelheid(Voertuig voertuig) {
        return voertuig.snelheid;
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

    void TestingModeOn() {
        testingMode = true;
    }

    void setTime(double time) {
        this->time = time;
    }
    double& getTime() {
        return time;
    }
    void simBushaltes(Voertuig &bus);

    std::vector<Verkeerslicht> getVerkeerslichten() const {
        return verkeerslichten;
    }

    void setVerkeerslichten(const std::vector<Verkeerslicht> &verkeerslichten) {
        this->verkeerslichten = verkeerslichten;
    }

    void voegverkeerslichttoe(Verkeerslicht licht) {
        this->verkeerslichten.push_back(licht);
    }

    std::vector<Voertuig>& getVoertuigen() {
        return voertuigen;
    }

    void setVoertuigen(const std::vector<Voertuig> &voertuigen) {
        this->voertuigen = voertuigen;
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

    void kruispuntSim(/*std::vector<Kruispunt> kruispunten, */Voertuig& voertuig/*, std::vector<Baan>& banen*/);

private:
    std::vector<Baan> banen;
    std::vector<Verkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    double time = 0.0;
    double DeltaTime = 0.0166;
    std::vector<Voertuig> toDelete;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;
    bool testingMode = false;
};



#endif //TRAFFICSIMULATION_H
