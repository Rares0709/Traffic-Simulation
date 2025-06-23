//
// Created by grama on 5/13/2025.
//

#include "Voertuig.h"
#include "DesignByContract.h"
#include "TrafficSimulation.h"
void Voertuig::lowerVolgendeNummer(){
    volgendeNummer--;
}
Baan* Voertuig::baan1() const {
    ENSURE(this->baan==baan,"De getter geeft de verkeerde baan mee.");
    return baan;
}

void Voertuig::set_baan(Baan *baan) {
    this->baan = baan;
    ENSURE(this->baan==baan,"De verkeerde baan werd geset.");
}

int Voertuig::fmin1() const {
    ENSURE(this->fmin==fmin,"De getter geeft de verkeerde fmin mee.");
    return fmin;
}

void Voertuig::set_fmin(int fmin) {
    REQUIRE(fmin >= 0, "fmin mag alleen 0 of groter zijn");
    this->fmin = fmin;
    ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
}

int Voertuig::lengte1() const {
    ENSURE(this->lengte==lengte,"De getter geeft de verkeerde lengte mee.");
    return lengte;
}

void Voertuig::set_lengte(int lengte) {
    REQUIRE(lengte >= 0, "lengte mag alleen 0 of groter zijn");
    this->lengte = lengte;
    ENSURE(this->lengte==lengte,"De verkeerde lengte werd geset.");
}

double Voertuig::positie1() const {
    ENSURE(this->positie==positie,"De getter geeft de verkeerde positie mee.");
    return positie;
}

void Voertuig::set_positie(double positie) {
    REQUIRE(positie >= 0, "positie mag alleen 0 of groter zijn");
    this->positie = positie;
    ENSURE(this->positie==positie,"De verkeerde positie werd geset.");
}

double Voertuig::m_Maxsnelheid() const {
    ENSURE(this->mMaxsnelheid==mMaxsnelheid,"De getter geeft de verkeerde mMaxsnelheid mee.");
    return mMaxsnelheid;
}

void Voertuig::set_m_Maxsnelheid(double m_maxsnelheid) {
    REQUIRE(m_maxsnelheid >= 0, "mMaxsnelheid mag alleen 0 of groter zijn");
    mMaxsnelheid = m_maxsnelheid;
    ENSURE(this->mMaxsnelheid==fmin,"De verkeerde mMaxsnelheid werd geset.");
}

double Voertuig::maxversnelling1() const {
    ENSURE(this->maxversnelling==maxversnelling,"De getter geeft de verkeerde maxversnelling mee.");
    return maxversnelling;
}

void Voertuig::set_maxversnelling(double maxversnelling) {
    REQUIRE(maxversnelling >= 0, "Maxversnelling mag alleen 0 of groter zijn");
    this->maxversnelling = maxversnelling;
    ENSURE(this->maxversnelling==maxversnelling,"De verkeerde maxversnelling werd geset.");
}

double Voertuig::snelheid1() const {
    ENSURE(this->snelheid==snelheid,"De getter geeft de verkeerde snelheid mee.");
    return snelheid;
}

void Voertuig::set_snelheid(double snelheid) {
    REQUIRE(snelheid >= 0, "Snelheid mag alleen 0 of groter zijn");
    this->snelheid = snelheid;
    ENSURE(this->snelheid==snelheid,"De verkeerde snelheid werd geset.");
}

double Voertuig::versnelling1() const {
    ENSURE(this->versnelling==versnelling,"De getter geeft de verkeerde versnelling mee.");
    return versnelling;
}

void Voertuig::set_versnelling(double versnelling) {
    REQUIRE(versnelling >= 0||versnelling <= 0, " mag kleiner dan 0 of groter dan 0 zijn of gelijk aan 0");
    this->versnelling = versnelling;
    ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
}

double Voertuig::vertraagfactor1() const {
    ENSURE(this->vertraagfactor==vertraagfactor,"De getter geeft de verkeerde vertraagfactor mee.");
    return vertraagfactor;
}

void Voertuig::set_vertraagfactor(double vertraagfactor) {
    REQUIRE(vertraagfactor >= 0, "vertraagfactor mag alleen 0 of groter zijn");
    this->vertraagfactor = vertraagfactor;
    ENSURE(this->vertraagfactor==vertraagfactor,"De verkeerde vertraagfactor werd geset.");
}

int Voertuig::vertraagafstand1() const {
    ENSURE(this->vertraagafstand==vertraagafstand,"De getter geeft de verkeerde vertraagafstand mee.");
    return vertraagafstand;
}

void Voertuig::set_vertraagafstand(int vertraagafstand) {
    REQUIRE(vertraagafstand >= 0, "Vertraagafstand mag alleen 0 of groter zijn");
    this->vertraagafstand = vertraagafstand;
    ENSURE(this->vertraagafstand==vertraagafstand,"De verkeerde vertraagafstand werd geset.");
}

int Voertuig::stopafstand1() const {
    ENSURE(this->stopafstand==stopafstand,"De getter geeft de verkeerde stopafstand mee.");
    return stopafstand;
}

void Voertuig::set_stopafstand(int stopafstand) {
    REQUIRE(stopafstand >= 0, "stopafstand mag alleen 0 of groter zijn");
    this->stopafstand = stopafstand;
    ENSURE(this->stopafstand==stopafstand,"De verkeerde stopafstand werd geset.");
}

int Voertuig::voertuig_nummer() const {
    ENSURE(this->voertuigNummer==voertuigNummer,"De getter geeft de verkeerde voertuignummer mee.");
    return voertuigNummer;
}

void Voertuig::set_voertuig_nummer(int voertuig_nummer) {
    REQUIRE(voertuig_nummer >= 1, "voertuignummer mag alleen 1 of groter zijn");
    voertuigNummer = voertuig_nummer;
    ENSURE(this->voertuigNummer==voertuig_nummer,"De verkeerde voertuignummer werd geset.");
}

double Voertuig::maxremfactor1() const {
    ENSURE(this->maxremfactor==maxremfactor,"De getter geeft de verkeerde maxremfactor mee.");
    return maxremfactor;
}

void Voertuig::set_maxremfactor(double maxremfactor) {
    REQUIRE(maxremfactor >= 0, "maxremfactor mag alleen 0 of groter zijn");
    this->maxremfactor = maxremfactor;
    ENSURE(this->maxremfactor==maxremfactor,"De verkeerde maxremfactor werd geset.");
}

double Voertuig::maxsnelheid1() const {
    ENSURE(this->maxsnelheid==maxsnelheid,"De getter geeft de verkeerde maxsnelheid mee.");
    return maxsnelheid;
}

void Voertuig::set_maxsnelheid(double maxsnelheid) {
    REQUIRE(maxsnelheid >= 0, "maxsnelheid mag alleen 0 of groter zijn");
    this->maxsnelheid = maxsnelheid;
    ENSURE(this->maxsnelheid==maxsnelheid,"De verkeerde fmin werd geset.");
}

bool Voertuig::prioriteit1() const {
    ENSURE(this->prioriteit==prioriteit,"De getter geeft de verkeerde bool mee.");
    return prioriteit;
}

void Voertuig::set_prioriteit(bool prioriteit) {
    REQUIRE(prioriteit == false || prioriteit == true, "prioriteit mag alleen een boolean zijn");
    this->prioriteit = prioriteit;
    ENSURE(this->prioriteit==prioriteit,"De verkeerde boolean werd geset.");
}

bool Voertuig::gestopt1() const {
    ENSURE(this->gestopt==gestopt,"De getter geeft de verkeerde bool mee.");
    return gestopt;
}

void Voertuig::set_gestopt(bool gestopt) {
    REQUIRE(gestopt == false || gestopt == true, "gestopt mag alleen een boolean zijn");
    this->gestopt = gestopt;
    ENSURE(this->gestopt==gestopt,"De verkeerde boolean werd geset.");
}

bool Voertuig::gedraait1() const {
    ENSURE(this->gedraait==gedraait,"De getter geeft de verkeerde bool mee.");
    return gedraait;
}

void Voertuig::set_gedraait(bool gedraait) {
    REQUIRE(gedraait == false || gedraait == true, "gedraait mag alleen een boolean zijn");
    this->gedraait = gedraait;
    ENSURE(this->gedraait==gedraait,"De verkeerde boolean werd geset.");
}

int Voertuig::timestop1() const {
    ENSURE(this->timestop==timestop,"De getter geeft de verkeerde timestop mee.");
    return timestop;
}

void Voertuig::set_timestop(int timestop) {
    REQUIRE(timestop >= 0, "timestop mag alleen 0 of groter zijn");
    this->timestop = timestop;
    ENSURE(this->timestop==timestop,"De verkeerde timestop werd geset.");
}

bool Voertuig::recent_gestopt() const {
    ENSURE(this->recentGestopt==recentGestopt,"De getter geeft de verkeerde bool mee.");
    return recentGestopt;
}

void Voertuig::set_recent_gestopt(bool recent_gestopt) {
    REQUIRE(recentGestopt == false || recentGestopt == true, "recent_gestopt mag alleen een boolean zijn");
    recentGestopt = recent_gestopt;
    ENSURE(this->recentGestopt==recent_gestopt,"De verkeerde boolean werd geset.");
}

std::string Voertuig::type1() const {
    ENSURE(this->type==type,"De getter geeft de verkeerde type mee.");
    return type;
}

void Voertuig::set_type(const std::string &type) {
    REQUIRE(type != "","Er is geen (Voertuig)type meegegeven.");
    this->type = type;
    ENSURE(this->fmin==fmin,"De verkeerde fmin werd geset.");
}
void Voertuig::berekenVersnelling(Voertuig* voertuig2) {
    REQUIRE(voertuig2 != nullptr,"voertuig2 mag geen nullptr zijn");
    int indexLijst = this->voertuig_nummer() - 1;
    if (indexLijst > 0) {
        if (this->gestopt1()) {
            this->set_versnelling(-(this->maxremfactor1()*this->snelheid1()/this->maxversnelling1()));
        } else {
            double volgafstand = voertuig2->positie1() - this->positie1() - voertuig2->lengte1();
            double snelheidsverschil = this->snelheid1() - voertuig2->snelheid1();
            double delta = (this->fmin1() + std::max(0.0, this->snelheid1() + ( (this->snelheid1() * snelheidsverschil) / (2 * std::sqrt(this->maxversnelling1() * this->maxremfactor1())))))/ volgafstand;
            double versnelling = this->maxversnelling1()*(1-pow(this->snelheid1()/this->maxsnelheid1(),4) - pow(delta,2));
            this->set_versnelling(versnelling);
        }
    }
    else {
        if (this->gestopt1()) {
            this->set_versnelling(-(this->maxremfactor1()*this->snelheid1()/this->maxversnelling1()));
        } else {
            double delta = 0;
            double versnelling = this->maxversnelling1()*(1-pow(this->snelheid1()/this->maxsnelheid1(),4) - pow(delta,2));
            this->set_versnelling(versnelling);
        }
    }
    ENSURE(std::isfinite(this->versnelling1()), "Versnelling moet een geldig getal zijn.");
}
void Voertuig::berekenSnelheid(double& DeltaTime) {
    REQUIRE(DeltaTime >=0 , "DeltaTime moet positief of 0 zijn.");
    double snelheid = this->snelheid1();
    double versnelling = this->versnelling1();
    double formule = snelheid + (versnelling*DeltaTime);
    double positie = this->positie1();
    /*if (snelheid>voertuig.mMaxsnelheid) {
        snelheid=voertuig.mMaxsnelheid;
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        voertuig.positie = positie;
    } else {*/
    if (formule < 0) {
        positie = positie - ((pow(snelheid, 2))/(2*versnelling));
        snelheid = 0;
        this->set_positie(positie);
    }
    else {
        snelheid = snelheid + (versnelling*DeltaTime);
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        this->set_positie(positie);
    }
    /*}*/
    this->set_snelheid(snelheid);
    ENSURE(this->snelheid1() >= 0, "Snelheid mag niet negatief zijn.");
    ENSURE(std::isfinite(this->positie1()), "Positie moet een geldig getal zijn.");

}
void Voertuig::versnellen() {
    REQUIRE(this->m_Maxsnelheid() >=0, "mMaxsnelheid moet positief zijn of 0.");
    this->set_maxsnelheid(this->m_Maxsnelheid());
    /*int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst == 0) {
        size_t indexVoertuig2 = indexLijst - 1;
        if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
            Voertuig& voertuig2 = voertuigen[indexVoertuig2];
            voertuig.maxsnelheid = voertuig2.mMaxsnelheid;
        }
    }*/
    ENSURE(this->maxsnelheid1() == this->m_Maxsnelheid(), "Voertuig moet zijn maximumsnelheid terug hebben.");
}
void Voertuig::vertragen() {
    REQUIRE(this->vertraagfactor1() > 0 && this->vertraagfactor1() < 1, "Vertraagfactor moet tussen 0 en 1 zijn.");
    REQUIRE(this->m_Maxsnelheid() >= 0, "mMaxsnelheid moet positief zijn of 0.");
    double s=this->vertraagfactor1();
    this->set_maxsnelheid(s*this->m_Maxsnelheid());
    ENSURE(this->maxsnelheid1() < this->m_Maxsnelheid(), "Na vertraging moet maxsnelheid lager zijn.");
}

void Voertuig::geldig(std::vector<Baan>& banen,Voertuig& voertuigtodelete,std::vector<Voertuig>* toDelete) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(toDelete != nullptr, "De toDelete mag niet null zijn.");
    //int indexLijst = this->voertuig_nummer() - 1;
    std::string baannaam = this->baan1()->naam1();
    int lengte =0;
    for (Baan&b : banen) {
        if (b.naam1() == baannaam) {
            lengte = b.lengte1();
        }
    }
    if (lengte < 0) {
        /*std::cout << "Bestaat niet." << std::endl;*/
    }
    else if (this->positie1() > lengte) {
        // if (voertuigen.size() > 1){
        //     Voertuig& voertuig2 = voertuigen[indexLijst + 1];
        //     voertuig2.voertuigNummer = voertuig.voertuigNummer;
        // }
        //voertuigen.erase(voertuigen.begin()+indexLijst);
        wagenToDelete(voertuigtodelete,toDelete);
        /*std::cout << "Voertuig weg van de baan" << std::endl;*/
    }
    else {
        /*std::cout << "er gebeurt niks" << std::endl;*/
    }
    std::string baanNaam=this->baan1()->naam1();
    ENSURE(this->positie1() <= lengte || toDelete->back().voertuig_nummer() == voertuigtodelete.voertuig_nummer(), "Voertuig moet op baan blijven of correct worden verwijderd.");
}
void Voertuig::wagenToDelete(Voertuig &voertuig,std::vector<Voertuig>* toDelete) {
    REQUIRE(toDelete != nullptr, "De toDelete mag niet null zijn.");
    toDelete->push_back(voertuig);
    bool gevondenVoertuig = false;
    for (const Voertuig& Voertuig : *toDelete) {
        if (&Voertuig == &voertuig) {
            gevondenVoertuig = true;
            break;
        }
    }
    ENSURE(gevondenVoertuig, "Voertuig werd niet aan de deletelijst toegevoegd.");
    ENSURE(toDelete->back().voertuig_nummer() == voertuig.voertuig_nummer(), "Laatste voertuig in deletelijst is niet het toegevoegde voertuig.");
}
