//
// Created by grama on 5/13/2025.
//

#include "Verkeersverkeerslicht.h"
void Verkeersverkeerslicht::set_positie(int positie) {
    REQUIRE(positie >= 0, "De positie moet positief zijn.");
    this->positie = positie;
    ENSURE(this->positie == positie, "De positie is correct ingesteld.");
}

void Verkeersverkeerslicht::set_cyclus(int cyclus) {
    REQUIRE(cyclus >= 0, "De cyclusduur moet positief zijn.");
    this->cyclus = cyclus;
    ENSURE(this->cyclus == cyclus, "De cyclus is correct ingesteld.");
}

void Verkeersverkeerslicht::set_baan(Baan* baan) {
    REQUIRE(baan != nullptr, "Baan mag niet null zijn.");
    this->baan = baan;
    ENSURE(this->baan == baan, "De baan is correct ingesteld.");
}

Baan* Verkeersverkeerslicht::baan1() const {
    return baan;
}

int Verkeersverkeerslicht::positie1() const {
    return positie;
}

int Verkeersverkeerslicht::cyclus1() const {
    return cyclus;
}

std::string Verkeersverkeerslicht::rood1() const {
    return rood;
}

std::string Verkeersverkeerslicht::groen1() const {
    return groen;
}

std::string Verkeersverkeerslicht::kleur1() const {
    return kleur;
}

void Verkeersverkeerslicht::set_kleur(std::string kleurstring) {
    REQUIRE(!kleurstring.empty(), "Kleur mag niet leeg zijn.");
    kleur = kleurstring;
    ENSURE(kleur == kleurstring, "Kleur is correct ingesteld.");
}

double Verkeersverkeerslicht::laatste_tijd() const {
    return laatsteTijd;
}

void Verkeersverkeerslicht::set_laatsteTijd(double laatstetijd) {
    REQUIRE(laatstetijd >= 0.0, "Tijd moet positief zijn.");
    laatsteTijd = laatstetijd;
    ENSURE(laatsteTijd == laatstetijd, "Laatste tijd is correct ingesteld.");
}

std::vector<Voertuig> Verkeersverkeerslicht::voertuigen_voor_licht() const {
    return voertuigenVoorLicht;
}

void Verkeersverkeerslicht::set_voertuigen_voor_licht(const std::vector<Voertuig>& voertuigen_voor_licht) {
    this->voertuigenVoorLicht = voertuigen_voor_licht;
    ENSURE(this->voertuigenVoorLicht.size() == voertuigen_voor_licht.size(),
           "De lijst met voertuigen is correct ingesteld.");
}

void Verkeersverkeerslicht::voeg_voertuigvoorlicht(Voertuig& voertuig) {
    size_t oudeGrootte = voertuigenVoorLicht.size();
    voertuigenVoorLicht.push_back(voertuig);
    ENSURE(voertuigenVoorLicht.size() == oudeGrootte + 1, "Voertuig is succesvol toegevoegd.");
}

// Verwijder alle voertuigen vóór het verkeerslicht
void Verkeersverkeerslicht::clear_voertuigvoorlicht() {
    voertuigenVoorLicht.clear();
    ENSURE(voertuigenVoorLicht.empty(), "Alle voertuigen zijn succesvol verwijderd.");
}
void Verkeersverkeerslicht::checkverkeerslicht(std::vector<Voertuig>* voertuigen) {
    REQUIRE(voertuigen != nullptr, "De lijst met voertuigen mag niet null zijn.");
    REQUIRE(this->positie1() >= 0, "De positie van het verkeerslicht moet positief zijn.");
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
            REQUIRE(Vertraag <= this->positie1() && Stop <= this->positie1(), "Vertraag- en stopafstand moeten vóór het verkeerslicht liggen.");
            if (eersteVoertuig.positie1() < Stop && eersteVoertuig.positie1() >= Vertraag) {
                eersteVoertuig.vertragen();
                for (auto& voertuig : this->voertuigen_voor_licht()) {
                    if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                        voertuig = eersteVoertuig;
                    }
                }
                for (auto& voertuig : *voertuigen) {
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
                for (auto& voertuig : *voertuigen) {
                    if (voertuig.voertuig_nummer() == eersteVoertuig.voertuig_nummer()) {
                        voertuig = eersteVoertuig;
                    }
                }
            }
        }
    }
    ENSURE(voertuigen->size() >= 0, "De voertuigenlijst is niet ongeldig na afloop.");
}
void Verkeersverkeerslicht::verkeerslichtSim(Verkeersverkeerslicht& verkeerslicht, std::vector<Voertuig> voertuigen, double currTime, bool testingMode) {
    REQUIRE(currTime >= 0.0, "De huidige tijd moet positief zijn.");
    REQUIRE(verkeerslicht.positie1() >= 0, "De positie van het verkeerslicht moet positief zijn.");
    REQUIRE(verkeerslicht.cyclus1() >= 0, "De cyclusduur van het verkeerslicht moet positief zijn.");
    if (!testingMode) {
        std::cout << "Verkeerslicht op " << verkeerslicht.positie1() << " heeft kleur: " << verkeerslicht.kleur1() << std::endl;
    }
    double tijd = currTime;
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
                REQUIRE(voertuig.positie1() >= 0, "De positie van een voertuig moet positief zijn.");
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
                REQUIRE(Vertraag <= verkeerslicht.positie1() && Stop <= verkeerslicht.positie1(), "Stop- en vertraagafstand moeten vóór het verkeerslicht liggen.");
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
    ENSURE(verkeerslicht.laatste_tijd() == currTime || currTime - verkeerslicht.laatste_tijd() <= verkeerslicht.cyclus1(), "Laatste tijd is correct geüpdatet of update was nog niet nodig.");
}