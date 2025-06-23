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
void Bushalte::simBushaltes(Voertuig &bus) {
    REQUIRE(bus.type1() == "bus", "Het voertuig moet een bus zijn.");
    REQUIRE(this->positie1() >= 0, "De positie van de bushalte moet positief zijn.");
    REQUIRE(bus.positie1() >= 0, "De positie van de bus moet positief zijn.");
    REQUIRE(bus.stopafstand1() >= 0 && bus.vertraagafstand1() >= 0, "Stop- en vertraagafstand moeten positief zijn.");

    double Vertraag = this->positie1() - bus.vertraagafstand1();
    double Stop = this->positie1() - bus.stopafstand1();
    if (bus.gestopt1()) {
        bus.set_timestop(1);
    }
    if (bus.positie1() >= Vertraag && bus.positie1() <= Stop) {
        bus.vertragen();
    } else if(!bus.recent_gestopt() && bus.positie1() >= Stop && bus.positie1() <= this->positie1()) {
        bus.set_gestopt(true);
    } else if (bus.recent_gestopt() && bus.positie1() > this->positie1()){
        bus.set_recent_gestopt(false);
    }
    if (bus.timestop1() > this->wachttijd1()) {
        bus.versnellen();
        bus.set_gestopt(false);
        bus.set_timestop(0);
    }
    ENSURE(!(bus.gestopt1() && bus.versnelling1()>0), "Een bus mag niet tegelijkertijd stoppen en versnellen.");
    ENSURE(bus.timestop1() >= 0, "De tijd dat de bus gestopt is moet niet negatief zijn.");
    ENSURE(!bus.recent_gestopt() || bus.positie1() >= this->positie1(), "Als de bus recent gestopt is, moet hij voorbij de bushalte zijn.");
}