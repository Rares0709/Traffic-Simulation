//
// Created by grama on 5/13/2025.
//

#ifndef VOERTUIG_H
#define VOERTUIG_H
#include <string>
#include "DesignByContract.h"
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

class Voertuig {
    static int volgendeNummer;
    int voertuigNummer = 1;

    Baan*baan = nullptr;
    int fmin = 4;
    int lengte = 4;
    double positie = 0;
    double mMaxsnelheid = 16.6;
    double maxversnelling = 1.44;
    double snelheid = 0;
    double versnelling = 0;
    double vertraagfactor = 0.4;
    int vertraagafstand = 50;
    int stopafstand = 15;
    double maxremfactor = 4.61;
    double maxsnelheid = 16.6;
    bool prioriteit = false;
    bool gestopt = false;
    bool gedraait = false;
    int timestop = 0;
    bool recentGestopt= false;
    std::string type = "auto";
public:


    Voertuig() : voertuigNummer(volgendeNummer++) {}

    Voertuig(int lengte, double m_maxsnelheid, double maxversnelling, double maxremfactor, double maxsnelheid,
        bool prioriteit=false)
        : voertuigNummer(volgendeNummer++),
          lengte(lengte),
          mMaxsnelheid(m_maxsnelheid),
          maxversnelling(maxversnelling),
          maxremfactor(maxremfactor),
          maxsnelheid(maxsnelheid),
          prioriteit(prioriteit){
    }

    static void lowerVolgendeNummer();
    static void resetVolgendeNummer() {
        volgendeNummer = 1;
    }


    Baan* baan1() const {
        return baan;
    }

    void set_baan(Baan *baan) {
        this->baan = baan;
    }

    int fmin1() const {
        return fmin;
    }

    void set_fmin(int fmin) {
        this->fmin = fmin;
    }

    int lengte1() const {
        return lengte;
    }

    void set_lengte(int lengte) {
        this->lengte = lengte;
    }

    double positie1() const {
        return positie;
    }

    void set_positie(double positie) {
        this->positie = positie;
    }

    double m_Maxsnelheid() const {
        return mMaxsnelheid;
    }

    void set_m_Maxsnelheid(double m_maxsnelheid) {
        mMaxsnelheid = m_maxsnelheid;
    }

    double maxversnelling1() const {
        return maxversnelling;
    }

    void set_maxversnelling(double maxversnelling) {
        this->maxversnelling = maxversnelling;
    }

    double snelheid1() const {
        return snelheid;
    }

    void set_snelheid(double snelheid) {
        this->snelheid = snelheid;
    }

    double versnelling1() const {
        return versnelling;
    }

    void set_versnelling(double versnelling) {
        this->versnelling = versnelling;
    }

    double vertraagfactor1() const {
        return vertraagfactor;
    }

    void set_vertraagfactor(double vertraagfactor) {
        this->vertraagfactor = vertraagfactor;
    }

    int vertraagafstand1() const {
        return vertraagafstand;
    }

    void set_vertraagafstand(int vertraagafstand) {
        this->vertraagafstand = vertraagafstand;
    }

    int stopafstand1() const {
        return stopafstand;
    }

    void set_stopafstand(int stopafstand) {
        this->stopafstand = stopafstand;
    }

    int voertuig_nummer() const {
        return voertuigNummer;
    }

    void set_voertuig_nummer(int voertuig_nummer) {
        voertuigNummer = voertuig_nummer;
    }

    double maxremfactor1() const {
        return maxremfactor;
    }

    void set_maxremfactor(double maxremfactor) {
        this->maxremfactor = maxremfactor;
    }

    double maxsnelheid1() const {
        return maxsnelheid;
    }

    void set_maxsnelheid(double maxsnelheid) {
        this->maxsnelheid = maxsnelheid;
    }

    bool prioriteit1() const {
        return prioriteit;
    }

    void set_prioriteit(bool prioriteit) {
        this->prioriteit = prioriteit;
    }

    bool gestopt1() const {
        return gestopt;
    }

    void set_gestopt(bool gestopt) {
        this->gestopt = gestopt;
    }

    bool gedraait1() const {
        return gedraait;
    }

    void set_gedraait(bool gedraait) {
        this->gedraait = gedraait;
    }

    int timestop1() const {
        return timestop;
    }

    void set_timestop(int timestop) {
        this->timestop = timestop;
    }

    bool recent_gestopt() const {
        return recentGestopt;
    }

    void set_recent_gestopt(bool recent_gestopt) {
        recentGestopt = recent_gestopt;
    }

    std::string type1() const {
        return type;
    }

    void set_type(const std::string &type) {
        this->type = type;
    }
    /**
     * Deze functie berekent de versnelling van het voertuig.
     * @param voertuig2
     * @param voertuig is het voertuig.
     */
    /**
     *@author Ilyas Sefiani
     *@author Rares Grama
     *@date /
     *@version
     */
    void berekenVersnelling(Voertuig* voertuig2 = nullptr);
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
    void berekenSnelheid(double& DeltaTime);
    /**
     * Deze functie berekent hoe het voertuig kan versnellen.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Ilyas Sefiani
     *@date /
     *@version
     */
    void versnellen();
    /**
     * Deze functie berekent hoe het voertuig kan vertragen.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Rares Grama
     *@date /
     *@version
     */
    void vertragen();
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

    void geldig(std::vector<Baan>& banen,Voertuig& voertuigtodelete,std::vector<Voertuig>* toDelete);

    void wagenToDelete(Voertuig &voertuig,std::vector<Voertuig>* toDelete);

};
class Auto: public Voertuig {
public:
    Auto()
    : Voertuig(4, 16.6, 1.44, 4.61, 16.6, false) {
        set_type("auto");
    }
};
class Bus: public Voertuig {
public:
    Bus():Voertuig(12, 11.4, 1.22, 4.29, 11.4, false) {
        set_type("Bus");
    }
};
class Brandweerwagen: public Voertuig {
public:
    Brandweerwagen():Voertuig(10, 14.6, 1.33, 4.56, 14.6, true) {
        set_type("brandweerwagen");
    }
};
class Ziekenwagen: public Voertuig {
public:
    Ziekenwagen():Voertuig(8, 15.5, 1.44, 4.47, 15.5, true) {
        set_type("ziekenwagen");
    }
};
class Politiecombi: public Voertuig {
public:
    Politiecombi():Voertuig(6, 17.2, 1.55, 4.92, 17.2, true) {
        set_type("ziekenwagen");
    }

};



#endif //VOERTUIG_H
