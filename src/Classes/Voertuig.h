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


    Baan* baan1() const;

    void set_baan(Baan *baan);

    int fmin1() const;

    void set_fmin(int fmin);

    int lengte1() const;

    void set_lengte(int lengte);

    double positie1() const;

    void set_positie(double positie);

    double m_Maxsnelheid() const;

    void set_m_Maxsnelheid(double m_maxsnelheid);

    double maxversnelling1() const;

    void set_maxversnelling(double maxversnelling);

    double snelheid1() const;

    void set_snelheid(double snelheid);

    double versnelling1() const;

    void set_versnelling(double versnelling);

    double vertraagfactor1() const;

    void set_vertraagfactor(double vertraagfactor);

    int vertraagafstand1() const;

    void set_vertraagafstand(int vertraagafstand);

    int stopafstand1() const;

    void set_stopafstand(int stopafstand);

    int voertuig_nummer() const;

    void set_voertuig_nummer(int voertuig_nummer);

    double maxremfactor1() const;

    void set_maxremfactor(double maxremfactor);

    double maxsnelheid1() const;

    void set_maxsnelheid(double maxsnelheid);

    bool prioriteit1() const;

    void set_prioriteit(bool prioriteit);

    bool gestopt1() const;

    void set_gestopt(bool gestopt);

    bool gedraait1() const;

    void set_gedraait(bool gedraait);

    int timestop1() const;

    void set_timestop(int timestop);

    bool recent_gestopt() const;

    void set_recent_gestopt(bool recent_gestopt);

    std::string type1() const;

    void set_type(const std::string &type);
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
