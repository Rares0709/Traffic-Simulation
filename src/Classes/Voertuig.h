//
// Created by grama on 5/13/2025.
//

#ifndef VOERTUIG_H
#define VOERTUIG_H
#include <string>


class Voertuig {
    std::string baan;
    int fmin = 4;
    int lengte = 4;
    double positie = 0;
    double mMaxsnelheid = 16.6;
    double maxversnelling = 1.44;
    double snelheid = 0;
    double versnelling = 0;
    static int volgendeNummer;
    double vertraagfactor = 0.4;
    int vertraagafstand = 50;
    int stopafstand = 15;
    int voertuigNummer = 1;
    double maxremfactor = 4.61;
    double maxsnelheid = 16.6;
    bool prioriteit = false;
    bool gestopt = false;
    bool gedraait = false;
    int timestop = 0;
    bool recentGestopt= false;
    std::string type = "auto"; // default is auto
public:

        Voertuig(const std::string &baan, int fmin, int lengte, double positie, double mMaxsnelheid, double maxversnelling,
             double snelheid, double versnelling, double vertraagfactor, int vertraagafstand, int stopafstand,
             int voertuigNummer, double maxremfactor, double maxsnelheid1, const std::string& type)
        : baan(baan),
          fmin(fmin),
          lengte(lengte),
          positie(positie),
          mMaxsnelheid(mMaxsnelheid),
          maxversnelling(maxversnelling),
          snelheid(snelheid),
          versnelling(versnelling),
          vertraagfactor(vertraagfactor),
          vertraagafstand(vertraagafstand),
          stopafstand(stopafstand),
          voertuigNummer(voertuigNummer),
          maxremfactor(maxremfactor),
          maxsnelheid(maxsnelheid1),
          type(type) {
        // type wordt ingesteld bij constructie
    }

    Voertuig() : voertuigNummer(volgendeNummer++) {}

    static void lowerVolgendeNummer();

    void setType(const std::string& nieuwType);

    std::string baan1() const {
        return baan;
    }

    void set_baan(const std::string &baan) {
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

    double m_maxsnelheid() const {
        return mMaxsnelheid;
    }

    void set_m_maxsnelheid(double m_maxsnelheid) {
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
};



#endif //VOERTUIG_H
