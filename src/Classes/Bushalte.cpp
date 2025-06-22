//
// Created by grama on 5/13/2025.
//

#include "Bushalte.h"
#include "Voertuig.h"
void Bushalte::simBushaltes(Voertuig &bus) {
    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!bushaltes.empty(), "Er bevinden zich geen bushaltes op de baan.");
    // REQUIRE(std::any_of(voertuigen.begin(), voertuigen.end(), [](const Voertuig& v) { return v.type1() == "bus"; }),
        //"Er is geen bus aanwezig op de baan.");
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
}