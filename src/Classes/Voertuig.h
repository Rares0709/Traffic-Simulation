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
        ENSURE(this->baan==baan,"De getter geeft de verkeerde baan mee.");
        return baan;
    }

    void set_baan(Baan *baan) {
        this->baan = baan;
        ENSURE(this->baan==baan,"De verkeerde baan werd geset.");
    }

    int fmin1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return fmin;
    }

    void set_fmin(int fmin) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->fmin = fmin;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    int lengte1() const {
        ENSURE(this->lengte==lengte,"De getter geeft de verkeerde lengte mee.");
        return lengte;
    }

    void set_lengte(int lengte) {
        REQUIRE(lengte >= 0, "lengte mag alleen 0 of groter zijn");
        this->lengte = lengte;
        ENSURE(this->lengte==lengte,"De verkeerde lengte werd geset.");
    }

    double positie1() const {
        ENSURE(this->positie==positie,"De getter geeft de verkeerde positie mee.");
        return positie;
    }

    void set_positie(double positie) {
        REQUIRE(positie >= 0, "positie mag alleen 0 of groter zijn");
        this->positie = positie;
        ENSURE(this->positie==positie,"De verkeerde positie werd geset.");
    }

    double m_Maxsnelheid() const {
        ENSURE(this->mMaxsnelheid==mMaxsnelheid,"De getter geeft de verkeerde mMaxsnelheid mee.");
        return mMaxsnelheid;
    }

    void set_m_Maxsnelheid(double m_maxsnelheid) {
        REQUIRE(m_maxsnelheid >= 0, "mMaxsnelheid mag alleen 0 of groter zijn");
        mMaxsnelheid = m_maxsnelheid;
        ENSURE(this->mMaxsnelheid==fmin,"De verkeerde mMaxsnelheid werd geset.");
    }

    double maxversnelling1() const {
        ENSURE(this->maxversnelling==maxversnelling,"De getter geeft de verkeerde maxversnelling mee.");
        return maxversnelling;
    }

    void set_maxversnelling(double maxversnelling) {
        REQUIRE(maxversnelling >= 0, "Maxversnelling mag alleen 0 of groter zijn");
        this->maxversnelling = maxversnelling;
        ENSURE(this->maxversnelling==maxversnelling,"De verkeerde maxversnelling werd geset.");
    }

    double snelheid1() const {
        ENSURE(this->snelheid==snelheid,"De getter geeft de verkeerde snelheid mee.");
        return snelheid;
    }

    void set_snelheid(double snelheid) {
        REQUIRE(snelheid >= 0, "Snelheid mag alleen 0 of groter zijn");
        this->snelheid = snelheid;
        ENSURE(this->snelheid==snelheid,"De verkeerde snelheid werd geset.");
    }

    double versnelling1() const {
        ENSURE(this->versnelling==versnelling,"De getter geeft de verkeerde versnelling mee.");
        return versnelling;
    }

    void set_versnelling(double versnelling) {
        REQUIRE(versnelling >= 0||versnelling <= 0, " mag kleiner dan 0 of groter dan 0 zijn of gelijk aan 0");
        this->versnelling = versnelling;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    double vertraagfactor1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return vertraagfactor;
    }

    void set_vertraagfactor(double vertraagfactor) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->vertraagfactor = vertraagfactor;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    int vertraagafstand1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return vertraagafstand;
    }

    void set_vertraagafstand(int vertraagafstand) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->vertraagafstand = vertraagafstand;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    int stopafstand1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return stopafstand;
    }

    void set_stopafstand(int stopafstand) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->stopafstand = stopafstand;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    int voertuig_nummer() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return voertuigNummer;
    }

    void set_voertuig_nummer(int voertuig_nummer) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        voertuigNummer = voertuig_nummer;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    double maxremfactor1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return maxremfactor;
    }

    void set_maxremfactor(double maxremfactor) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->maxremfactor = maxremfactor;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    double maxsnelheid1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return maxsnelheid;
    }

    void set_maxsnelheid(double maxsnelheid) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->maxsnelheid = maxsnelheid;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    bool prioriteit1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return prioriteit;
    }

    void set_prioriteit(bool prioriteit) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->prioriteit = prioriteit;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    bool gestopt1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return gestopt;
    }

    void set_gestopt(bool gestopt) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->gestopt = gestopt;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    bool gedraait1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return gedraait;
    }

    void set_gedraait(bool gedraait) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->gedraait = gedraait;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    int timestop1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return timestop;
    }

    void set_timestop(int timestop) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->timestop = timestop;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    bool recent_gestopt() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return recentGestopt;
    }

    void set_recent_gestopt(bool recent_gestopt) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        recentGestopt = recent_gestopt;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
    }

    std::string type1() const {
        ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
        return type;
    }

    void set_type(const std::string &type) {
        REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
        this->type = type;
        ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
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
        set_type("bus");
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
        set_type("politiecombi");
    }

};



#endif //VOERTUIG_H
