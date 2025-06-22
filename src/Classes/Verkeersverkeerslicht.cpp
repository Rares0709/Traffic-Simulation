//
// Created by grama on 5/13/2025.
//

#include "Verkeersverkeerslicht.h"
void Verkeersverkeerslicht::checkverkeerslicht(std::vector<Voertuig> voertuigen) {
    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!verkeerslichten.empty(), "Er bevinden zich geen verkeerslichten op de baan.");
    if (this->kleur1()==this->rood1()) {
        bool eersteGevonden = false;
        Voertuig eersteVoertuig;
        for (auto& voertuig : this->voertuigen_voor_licht()) {
            if (voertuig.positie1() < this->positie1() && (eersteGevonden != true || voertuig.positie1() >= eersteVoertuig.positie1() )) {
                if (!voertuig.prioriteit1()) {
                    eersteVoertuig = voertuig;
                    eersteGevonden = true;
                }
            }
        }
        if (!eersteVoertuig.prioriteit1() && eersteGevonden) {
            double Vertraag = this->positie1() - eersteVoertuig.vertraagafstand1();
            double Stop = this->positie1() - eersteVoertuig.stopafstand1();
            if (eersteVoertuig.positie1() < Stop && eersteVoertuig.positie1() >= Vertraag) {
                eersteVoertuig.vertragen();
                for (auto& voertuig : this->voertuigen_voor_licht()) {
                    if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                        voertuig = eersteVoertuig;
                    }
                }
                for (auto& voertuig : voertuigen) {
                    if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                        voertuig = eersteVoertuig;
                    }
                }
            } else if (eersteVoertuig.positie1() < this->positie1() && eersteVoertuig.positie1() >= Stop) {
                //stoppen(eersteVoertuig);
                for (auto& voertuig : this->voertuigen_voor_licht()) {
                    if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                        voertuig = eersteVoertuig;
                    }
                }
                for (auto& voertuig : voertuigen) {
                    if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                        voertuig = eersteVoertuig;
                    }
                }
            }
        }
    }
    // ENSURE(!verkeerslichten.empty(), "Verkeerslichten mogen niet leeg zijn na controle.");
}
void Verkeersverkeerslicht::verkeerslichtSim(Verkeersverkeerslicht& verkeerslicht, std::vector<Voertuig> voertuigen, double currTime) {
    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!verkeerslichten.empty(), "Er bevinden zich geen verkeerslichten op de baan.");
    if (!testingMode) {
        std::cout << "Verkeerslicht op " << verkeerslicht.positie1() << " heeft kleur: " << verkeerslicht.kleur1() << std::endl;
    }
    int tijd = currTime;
    if (!testingMode) {
        std::cout << tijd << std::endl;
    }
    int TimeForSwitch = ceil(currTime - verkeerslicht.laatste_tijd());
    int verkeerslichtCyclus = verkeerslicht.cyclus1();
    if (TimeForSwitch>verkeerslichtCyclus) {
        if (verkeerslicht.kleur1()==verkeerslicht.rood1()) {
            verkeerslicht.set_kleur("groen");
            if (!testingMode) {
                std::cout << "Aantal voertuigen: " << voertuigen.size() << std::endl;
            }
            bool eersteGevonden = false;
            Voertuig eersteVoertuig;
            for (auto& voertuig : verkeerslicht.voertuigen_voor_licht()) {
                if (voertuig.positie1() < verkeerslicht.positie1() && (eersteGevonden != true || voertuig.positie1() >= eersteVoertuig.positie1() )) {
                    eersteVoertuig = voertuig;
                    eersteGevonden = true;
                }
            }
            eersteVoertuig.set_gestopt(false);
            if (eersteGevonden)
                eersteVoertuig.versnellen();
        }
        else if (verkeerslicht.kleur1()==verkeerslicht.groen1()) {
            verkeerslicht.set_kleur("rood");
            if (!testingMode) {
                std::cout << "Aantal voertuigen: " << voertuigen.size() << std::endl;
            }
            bool eersteGevonden = false;
            Voertuig eersteVoertuig;
            for (auto& voertuig : verkeerslicht.voertuigen_voor_licht()) {
                if (voertuig.positie1() < verkeerslicht.positie1() && (eersteGevonden != true || voertuig.positie1() >= eersteVoertuig.positie1() )) {
                    eersteVoertuig = voertuig;
                    eersteGevonden = true;
                }
            }
            if (!eersteVoertuig.prioriteit1() && eersteGevonden) {
                double Vertraag = verkeerslicht.positie1() - eersteVoertuig.vertraagafstand1();
                double Stop = verkeerslicht.positie1() - eersteVoertuig.stopafstand1();
                if (eersteVoertuig.positie1() < Stop && eersteVoertuig.positie1() >= Vertraag) {
                    eersteVoertuig.vertragen();
                    for (auto& voertuig : verkeerslicht.voertuigen_voor_licht()) {
                        if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                            voertuig = eersteVoertuig;
                        }
                    }
                    for (auto& voertuig : voertuigen) {
                        if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                            voertuig = eersteVoertuig;
                        }
                    }
                } else if (eersteVoertuig.positie1() < verkeerslicht.positie1() && eersteVoertuig.positie1() >= Stop) {
                    //stoppen(eersteVoertuig);
                    eersteVoertuig.set_gestopt(true);
                    for (auto& voertuig : verkeerslicht.voertuigen_voor_licht()) {
                        if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                            voertuig = eersteVoertuig;
                        }
                    }
                    for (auto& voertuig : voertuigen) {
                        if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                            voertuig = eersteVoertuig;
                        }
                    }
                }
            }
        }

        verkeerslicht.set_laatsteTijd(currTime);
    }
    // ENSURE(verkeerslicht.kleur1() == verkeerslicht.rood1() || verkeerslicht.kleur1() == verkeerslicht.groen1(), "Kleur van verkeerslicht moet geldig zijn.");
    // ENSURE(verkeerslicht.laatste_tijd() <= time, "Laatste tijd van verkeerslicht mag niet in de toekomst liggen.");
    // std::cout << "kleur: --> " << verkeerslicht.kleur << std::endl;
}