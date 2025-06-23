//
// Created by grama on 5/13/2025.
//

#include "Bushalte.h"
#include "Voertuig.h"
Baan* Bushalte::baan1() const {
    ENSURE(baan != nullptr, "De baan mag niet null zijn.");
    return baan;
}

void Bushalte::set_baan(Baan* baan) {
    REQUIRE(baan != nullptr, "De baan mag niet null zijn.");
    this->baan = baan;
    ENSURE(this->baan == baan, "De baan moet correct zijn toegewezen.");
}

int Bushalte::positie1() const {
    ENSURE(positie >= 0, "De positie moet niet negatief zijn.");
    return positie;
}

void Bushalte::set_positie(int positie) {
    REQUIRE(positie >= 0, "De positie moet positief of nul zijn.");
    this->positie = positie;
    ENSURE(this->positie == positie, "De positie moet correct zijn toegewezen.");
}

int Bushalte::wachttijd1() const {
    ENSURE(wachttijd >= 0, "De wachttijd moet niet negatief zijn.");
    return wachttijd;
}
void Bushalte::set_wachttijd(int wachttijd) {
    REQUIRE(wachttijd >= 0, "De wachttijd moet positief of nul zijn.");
    this->wachttijd = wachttijd;
    ENSURE(this->wachttijd == wachttijd, "De wachttijd moet correct zijn toegewezen.");
}
void Bushalte::simBushaltes(Voertuig &bus, bool testingMode) {
    REQUIRE(bus.type1() == "bus", "Het voertuig moet een bus zijn.");
    REQUIRE(this->positie1() >= 0, "De positie van de bushalte moet positief zijn.");
    REQUIRE(bus.positie1() >= 0, "De positie van de bus moet positief zijn.");
    REQUIRE(bus.stopafstand1() >= 0 && bus.vertraagafstand1() >= 0, "Stop- en vertraagafstand moeten positief zijn.");

    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!bushaltes.empty(), "Er bevinden zich geen bushaltes op de baan.");
    // REQUIRE(std::any_of(voertuigen.begin(), voertuigen.end(), [](const Voertuig& v) { return v.type1() == "bus"; }),
        //"Er is geen bus aanwezig op de baan.");
    double Vertraag = this->positie1() - bus.vertraagafstand1();
    double Stop = this->positie1() - bus.stopafstand1();
    if (bus.gestopt1()) {
        int timeStop = bus.timestop1()+1;
        bus.set_timestop(timeStop);
    }
    if (bus.positie1() >= Vertraag && bus.positie1() <= Stop) {
        if (!testingMode) {
            std::cout<<"Bus "<<bus.voertuig_nummer()<<" gaat vertragen."<<std::endl;
        }
        bus.vertragen();
    } else if(!bus.recent_gestopt() && bus.positie1() >= Stop && bus.positie1() <= this->positie1()) {
        bus.set_gestopt(true);
        if (!testingMode) {
            std::cout<<"Bus "<<bus.voertuig_nummer()<<" gaat stoppen."<<std::endl;
        }
    } else if (bus.recent_gestopt() && bus.positie1() > this->positie1()){
        bus.set_recent_gestopt(false);
    }
    if (bus.timestop1() > this->wachttijd1()) {
        bus.versnellen();
        bus.set_gestopt(false);
        bus.set_timestop(0);
        bus.set_recent_gestopt(true);
        if (!testingMode) {
            std::cout<<"Bus "<<bus.voertuig_nummer()<<" gaat vertrekken."<<std::endl;
        }
    }
    ENSURE(bus.timestop1() >= 0, "De tijd dat de bus gestopt is moet niet negatief zijn.");
    //ENSURE(!bus.recent_gestopt() || bus.positie1() >= this->positie1(), "Als de bus recent gestopt is, moet hij voorbij de bushalte zijn.");

}