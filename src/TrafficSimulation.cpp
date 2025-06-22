//
// Created by jonas on 3/20/2025.
//
#include <algorithm>
#include "TrafficSimulation.h"
#include "DesignByContract.h"
void TrafficSim::Simulate(int duration) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!this->get_banen().empty(), "Banen empty is niet goed geïnitialiseerd.");
    std::vector<std::vector<Verkeersverkeerslicht>> baanVerkeerslicht;
    Verkeersverkeerslicht vorigeVerkeerslicht;
    for (Baan baan : banen) {
        std::vector<Verkeersverkeerslicht> volgordeVerkeerslicht;
        for (const Verkeersverkeerslicht& verkeerslicht : verkeerslichten) {
            if (baan.naam1() == verkeerslicht.baan1()) {
                if (volgordeVerkeerslicht.empty()) {
                    volgordeVerkeerslicht.push_back(verkeerslicht);
                    vorigeVerkeerslicht = verkeerslicht;
                }
                else if (vorigeVerkeerslicht.positie1() > verkeerslicht.positie1()) {
                    volgordeVerkeerslicht.insert(volgordeVerkeerslicht.begin() , verkeerslicht);
                }
                else if (vorigeVerkeerslicht.positie1() < verkeerslicht.positie1()) {
                    volgordeVerkeerslicht.push_back(verkeerslicht);
                }
            }
        }
        if (!volgordeVerkeerslicht.empty()) {
            baanVerkeerslicht.push_back(volgordeVerkeerslicht);
        }
    }
    std::vector<Verkeersverkeerslicht> fixedVerkeerslicht;
    for (auto& temp : baanVerkeerslicht) {
        for (const Verkeersverkeerslicht& verkeerslicht : temp) {
            fixedVerkeerslicht.push_back(verkeerslicht);
        }
    }
    verkeerslichten = fixedVerkeerslicht;
    double& currentTime = this->getTime();
    while (duration == -1 || currentTime <= duration) {
        if (!testingMode) {
            print();
        }
        std::vector<Voertuig> usedVoertuigen;
        for (Verkeersverkeerslicht& verkeerslicht : verkeerslichten) {
            for (Voertuig& voertuig : voertuigen) {
                if (voertuig.positie1() < verkeerslicht.positie1()) {
                    // Only add if not already in usedVoertuigen
                    auto it = std::find_if(usedVoertuigen.begin(), usedVoertuigen.end(), [&](const Voertuig& v) {
                        return v.voertuig_nummer() == voertuig.voertuig_nummer();
                    });

                    if (it == usedVoertuigen.end()) {
                        if (voertuig.baan1() == verkeerslicht.baan1()) {
                            verkeerslicht.voeg_voertuigvoorlicht(voertuig);
                            usedVoertuigen.push_back(voertuig);
                        }
                    }
                }
            }
        }
        if (!verkeerslichten.empty())
            checkverkeerslicht();
        for (auto& voertuig : voertuigen) {
            voertuig.berekenSnelheid(DeltaTime);
            //berekenSnelheid(voertuig);
            if (voertuig.voertuig_nummer()-1 > 0) {
                Voertuig voertuig2 = voertuigen[voertuig.voertuig_nummer()-2];
                voertuig.berekenVersnelling(&voertuig2);
            }
            else
                voertuig.berekenVersnelling();
            //berekenVersnelling(voertuig);
            voertuig.geldig(banen, voertuig, &toDelete);
            //geldig(voertuig);
            if (!kruispunten.empty())
                for (Kruispunt& kruispunt : kruispunten) {
                    kruispunt.kruispuntSim(voertuig,banen);
                }
                //kruispuntSim(voertuig);
            if (voertuig.type1() == "bus" && !bushaltes.empty())
                for (Bushalte& bushalte : bushaltes) {
                    bushalte.simBushaltes(voertuig);
                }
                //simBushaltes(voertuig);
        }
        // int size = toDelete.size();
        // for (Voertuig& voertuig: toDelete) {
        //     int voertuignummer = voertuig.voertuigNummer;
        //     voertuigen.erase(voertuigen.begin()+voertuig.voertuigNummer-1);
        //     for (auto& voertuig1 : voertuigen) {
        //         if (voertuig1.voertuigNummer > voertuignummer) {
        //             voertuig1.voertuigNummer -= 1;
        //             voertuig1.lowerVolgendeNummer();
        //         }
        //     }
        //     for (auto& voertuig1 : toDelete) {
        //         if (voertuig1.voertuigNummer > voertuignummer) {
        //             voertuig1.voertuigNummer -= 1;
        //         }
        //     }
        // }
        std::vector<int> indexen;
        for (Voertuig& voertuig : toDelete) {
            size_t idx = static_cast<size_t>(voertuig.voertuig_nummer() - 1);
            if (idx < voertuigen.size()) {
                indexen.push_back(static_cast<int>(idx));  // of sla ze als size_t op, dan moet je alles aanpassen
            }
        }
        std::sort(indexen.rbegin(), indexen.rend());  // sorteer van hoog naar laag
        for (int idx : indexen) {
            voertuigen.erase(voertuigen.begin() + idx);
        }

        // (Optioneel) hernummer voertuigen opnieuw na verwijderen
        for (size_t i = 0; i < voertuigen.size(); ++i) {
            voertuigen[i].set_voertuig_nummer(i + 1);
            voertuigen[i].lowerVolgendeNummer();
        }
        toDelete.clear();
        if (!verkeerslichten.empty()) {
            if (!testingMode) {
                std::cout << verkeerslichten.size() << std::endl;
            }
            for (auto& verkeerslicht : verkeerslichten)
                verkeerslichtSim(verkeerslicht);
        } else {
            if (!testingMode) {
                std::cout << "Geen verkeerslichten beschikbaar!" << std::endl;
            }
        }
        std::vector<Voertuig> empty;
        verhoogTijd();
        if (!voertuigengen.empty())
            simVoertuiggenerator();
        for (Verkeersverkeerslicht &verkeerslicht: verkeerslichten) {
             verkeerslicht.set_voertuigen_voor_licht(empty);
        }
    }
    //ENSURE(!verkeerslichten.empty(), "Na simulatie mogen de verkeerslichten niet leeg zijn.");
    ENSURE(time >= 0, "De tijd moet positief zijn na simulatie.");
}
void TrafficSim::wagenToDelete(Voertuig &voertuig) {
    toDelete.push_back(voertuig);
    ENSURE(!toDelete.empty(), "Voertuig werd niet aan de deletelijst toegevoegd.");
    ENSURE(toDelete.back().voertuig_nummer() == voertuig.voertuig_nummer(), "Laatste voertuig in deletelijst is niet het toegevoegde voertuig.");

}
void TrafficSim::berekenVersnelling(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    int indexLijst = voertuig.voertuig_nummer() - 1;
    if (indexLijst > 0) {
        if (voertuig.gestopt1()) {
            voertuig.set_versnelling(-(voertuig.maxremfactor1()*voertuig.snelheid1()/voertuig.maxversnelling1()));
        } else {
            int indexVoertuig2 = indexLijst - 1;
            Voertuig voertuig2 = voertuigen[indexVoertuig2];
            double volgafstand = voertuig2.positie1() - voertuig.positie1() - voertuig2.lengte1();
            double snelheidsverschil = voertuig.snelheid1() - voertuig2.snelheid1();
            double delta = (voertuig.fmin1() + std::max(0.0, voertuig.snelheid1() + ( (voertuig.snelheid1() * snelheidsverschil) / (2 * std::sqrt(voertuig.maxversnelling1() * voertuig.maxremfactor1())))))/ volgafstand;
            double versnelling = voertuig.maxversnelling1()*(1-pow(voertuig.snelheid1()/voertuig.maxsnelheid1(),4) - pow(delta,2));
            voertuig.set_versnelling(versnelling);
        }
    }
    else {
        if (voertuig.gestopt1()) {
            voertuig.set_versnelling(-(voertuig.maxremfactor1()*voertuig.snelheid1()/voertuig.maxversnelling1()));
        } else {
            double delta = 0;
            double versnelling = voertuig.maxversnelling1()*(1-pow(voertuig.snelheid1()/voertuig.maxsnelheid1(),4) - pow(delta,2));
            voertuig.set_versnelling(versnelling);
        }
    }
    ENSURE(std::isfinite(voertuig.versnelling1()), "Versnelling moet een geldig getal zijn.");
}
void TrafficSim::berekenSnelheid(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    double snelheid = voertuig.snelheid1();
    double versnelling = voertuig.versnelling1();
    double formule = snelheid + (versnelling*DeltaTime);
    double positie = voertuig.positie1();
    /*if (snelheid>voertuig.mMaxsnelheid) {
        snelheid=voertuig.mMaxsnelheid;
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        voertuig.positie = positie;
    } else {*/
    if (formule < 0) {
        positie = positie - ((pow(snelheid, 2))/(2*versnelling));
        snelheid = 0;
        voertuig.set_positie(positie);
    }
    else {
        snelheid = snelheid + (versnelling*DeltaTime);
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        voertuig.set_positie(positie);
    }
    /*}*/
    voertuig.set_snelheid(snelheid);
    ENSURE(voertuig.snelheid1() >= 0, "Snelheid mag niet negatief zijn.");
    ENSURE(std::isfinite(voertuig.positie1()), "Positie moet een geldig getal zijn.");

}
void TrafficSim::versnellen(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    voertuig.set_maxsnelheid(voertuig.m_Maxsnelheid());
    /*int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst == 0) {
        size_t indexVoertuig2 = indexLijst - 1;
        if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
            Voertuig& voertuig2 = voertuigen[indexVoertuig2];
            voertuig.maxsnelheid = voertuig2.mMaxsnelheid;
        }
    }*/
    ENSURE(voertuig.maxsnelheid1() == voertuig.m_Maxsnelheid(), "Voertuig moet zijn maximumsnelheid terug hebben.");
}
Voertuig TrafficSim::vertragen(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    double s=voertuig.vertraagfactor1();
    voertuig.set_maxsnelheid(s*voertuig.m_Maxsnelheid());
    return voertuig;
    ENSURE(voertuig.maxsnelheid1() < voertuig.m_Maxsnelheid(), "Na vertraging moet maxsnelheid lager zijn.");
}
void TrafficSim::kruispuntSim(/*std::vector<Kruispunt> kruispunten, */Voertuig& voertuig/*, std::vector<Baan>& banen*/) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!kruispunten.empty(), "Er bevindt zich geen kruispunt op de baan.");
    REQUIRE(banen.size()>=2, "Er moeten minstens 2 banen aanwezig zijn.");
    for (Kruispunt kruispunt: kruispunten) {
        int breedte = 0;
        if (!voertuig.gedraait1()) {
            if (kruispunt.from_baan() == voertuig.baan1()) {
                //int breedte;
                for (const Baan& b : banen) {
                    if (b.naam1() == kruispunt.from_baan()) {
                        breedte = b.breedte1();
                        break;
                    }
                }
                /*std::vector<std::string> baantje;
                baantje.push_back(kruispunt.fromBaan);
                baantje.push_back(kruispunt.toBaan);*/
                if (voertuig.positie1() >= kruispunt.from_positie() && voertuig.positie1() <= kruispunt.from_positie() + breedte) {
                    std::srand(std::time(0));
                    bool keuze = std::rand() % 2;
                    // voertuig.baan = baantje[keuze];
                    // voertuig.positie = baantje[]
                    if (keuze) {
                        voertuig.set_baan(kruispunt.to_baan());
                        voertuig.set_positie(kruispunt.to_positie());
                        voertuig.set_gedraait(true);
                    }
                }
            }
            else if (kruispunt.to_baan() == voertuig.baan1()) {
                for (const Baan& b : banen) {
                    if (b.naam1() == kruispunt.to_baan()) {
                        breedte = b.breedte1();
                        break;
                    }
                }
                /*std::vector<std::string> baantje;
                baantje.push_back(kruispunt.fromBaan);
                baantje.push_back(kruispunt.toBaan);*/
                if (voertuig.positie1() >= kruispunt.to_positie() && voertuig.positie1() <= kruispunt.to_positie() + breedte) {
                    std::srand(std::time(0));
                    bool keuze = std::rand() % 2;
                    // voertuig.baan = baantje[keuze];
                    // voertuig.positie = baantje[]
                    if (keuze) {
                        voertuig.set_baan(kruispunt.from_baan());
                        voertuig.set_positie(kruispunt.from_positie());
                        voertuig.set_gedraait(true);
                    }
                }
            }
        }
        else if (voertuig.baan1() == kruispunt.from_baan()) {
            for (auto& baan : banen) {
                if (kruispunt.from_baan() == baan.naam1()) {
                    if (voertuig.positie1() > kruispunt.from_positie() + baan.breedte1()) {
                        voertuig.set_gedraait(false);
                    }
                }
            }
        }
        else if (voertuig.baan1() == kruispunt.to_baan()) {
            for (auto& baan : banen) {
                if (kruispunt.to_baan() == baan.naam1()) {
                    if (voertuig.positie1() > kruispunt.to_positie() + baan.breedte1()) {
                        voertuig.set_gedraait(false);
                    }
                }
            }
        }
    }
    ENSURE(std::find_if(banen.begin(), banen.end(), [&](const Baan& b) { return b.naam1() == voertuig.baan1(); }) != banen.end(), "Voertuig moet op een bestaande baan blijven.");
}
void TrafficSim::geldig(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    int indexLijst = voertuig.voertuig_nummer() - 1;

    std::string baannaam = voertuig.baan1();
    int lengte = getBaanLengte(baannaam, banen);
    if (lengte < 0) {
        /*std::cout << "Bestaat niet." << std::endl;*/
    }
    else if (voertuig.positie1() > lengte) {
        // if (voertuigen.size() > 1){
        //     Voertuig& voertuig2 = voertuigen[indexLijst + 1];
        //     voertuig2.voertuigNummer = voertuig.voertuigNummer;
        // }
        Voertuig &voertuigtodelete = voertuigen[indexLijst];
        //voertuigen.erase(voertuigen.begin()+indexLijst);
        wagenToDelete(voertuigtodelete);
        /*std::cout << "Voertuig weg van de baan" << std::endl;*/
    }
    else {
        /*std::cout << "er gebeurt niks" << std::endl;*/
    }
    std::string baanNaam=voertuig.baan1();
    ENSURE(std::find_if(toDelete.begin(), toDelete.end(), [&](const Voertuig& v) { return v.voertuig_nummer() == voertuig.voertuig_nummer(); }) != toDelete.end() || voertuig.positie1() <= getBaanLengte(baanNaam, banen), "Voertuig is ongeldig verwijderd of buiten baan.");
}
void TrafficSim::checkverkeerslicht() {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!verkeerslichten.empty(), "Er bevinden zich geen verkeerslichten op de baan.");
    for (Verkeersverkeerslicht& verkeerslicht : verkeerslichten) {
        if (verkeerslicht.kleur1()==verkeerslicht.rood1()) {
            if (!testingMode) {
                std::cout << "Aantal voertuigen: " << voertuigen.size() << std::endl;
            }
            bool eersteGevonden = false;
            Voertuig eersteVoertuig;
            for (auto& voertuig : verkeerslicht.voertuigen_voor_licht()) {
                if (voertuig.positie1() < verkeerslicht.positie1() && (eersteGevonden != true || voertuig.positie1() >= eersteVoertuig.positie1() )) {
                    if (!voertuig.prioriteit1()) {
                        eersteVoertuig = voertuig;
                        eersteGevonden = true;
                    }
                }
            }
            if (!eersteVoertuig.prioriteit1() && eersteGevonden) {
                double Vertraag = verkeerslicht.positie1() - eersteVoertuig.vertraagafstand1();
                double Stop = verkeerslicht.positie1() - eersteVoertuig.stopafstand1();
                if (eersteVoertuig.positie1() < Stop && eersteVoertuig.positie1() >= Vertraag) {
                    eersteVoertuig = vertragen(eersteVoertuig);
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
    }
    ENSURE(!verkeerslichten.empty(), "Verkeerslichten mogen niet leeg zijn na controle.");
}
void TrafficSim::verkeerslichtSim(Verkeersverkeerslicht& verkeerslicht) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!verkeerslichten.empty(), "Er bevinden zich geen verkeerslichten op de baan.");
    if (!testingMode) {
        std::cout << "Verkeerslicht op " << verkeerslicht.positie1() << " heeft kleur: " << verkeerslicht.kleur1() << std::endl;
    }
    int tijd = this->time;
    if (!testingMode) {
        std::cout << tijd << std::endl;
    }
    int TimeForSwitch = ceil(time - verkeerslicht.laatste_tijd());
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
                versnellen(eersteVoertuig);
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
                    eersteVoertuig = vertragen(eersteVoertuig);
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

        verkeerslicht.set_laatsteTijd(time);
    }
    ENSURE(verkeerslicht.kleur1() == verkeerslicht.rood1() || verkeerslicht.kleur1() == verkeerslicht.groen1(), "Kleur van verkeerslicht moet geldig zijn.");
    ENSURE(verkeerslicht.laatste_tijd() <= time, "Laatste tijd van verkeerslicht mag niet in de toekomst liggen.");
    // std::cout << "kleur: --> " << verkeerslicht.kleur << std::endl;
}

void TrafficSim::simBushaltes(Voertuig &bus) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!bushaltes.empty(), "Er bevinden zich geen bushaltes op de baan.");
    REQUIRE(std::any_of(voertuigen.begin(), voertuigen.end(), [](const Voertuig& v) { return v.type1() == "bus"; }),
        "Er is geen bus aanwezig op de baan.");

    for (Bushalte bushalte : bushaltes) {
        double Vertraag = bushalte.positie1() - bus.vertraagafstand1();
        double Stop = bushalte.positie1() - bus.stopafstand1();
        if (bus.gestopt1()) {
            bus.set_timestop(1);
        }
        if (bus.positie1() >= Vertraag && bus.positie1() <= Stop) {
            vertragen(bus);
        } else if(!bus.recent_gestopt() && bus.positie1() >= Stop && bus.positie1() <= bushalte.positie1()) {
            bus.set_gestopt(true);
        } else if (bus.recent_gestopt() && bus.positie1() > bushalte.positie1()){
            bus.set_recent_gestopt(false);
        }
        if (bus.timestop1() > bushalte.wachttijd1()) {
            versnellen(bus);
            bus.set_gestopt(false);
            bus.set_timestop(0);
        }
    }
}
void TrafficSim::simVoertuiggenerator() {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigengen.empty(), "Er is geen voertuiggenerator aanwezig.");
    for (auto& generator : voertuigengen) {
        int laatsteTijd = ceil(time - generator.laatste_tijd());
        if (laatsteTijd > generator.freq1()) {
            bool vrij = true;
            for (const auto& voertuig : voertuigen) {
                if (voertuig.baan1() == generator.baan1() && 0 <= voertuig.positie1() && voertuig.positie1() <= 2 * voertuig.lengte1()) {
                    vrij = false;
                    break;
                }
            }
            if (vrij){
                Voertuig nieuwVoertuig;
                nieuwVoertuig.set_baan(generator.baan1());
                nieuwVoertuig.set_positie(0);
                voertuigen.push_back(nieuwVoertuig);
                generator.set_laatste_tijd(time);
            }
        }
    }
}
int TrafficSim::getBaanLengte(std::string &baannaam, std::vector<Baan> &banen) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    for (Baan& b : banen) {
        if (b.naam1() == baannaam) {
            return b.lengte1();
        }
    }
    return 0;
}
void TrafficSim::verhoogTijd() {
    double oldTime = this->time;
    double add = this->DeltaTime;
    setTime(this->time+add);
    if (!testingMode) {
        std::cout << "tijd verhoogd: " << oldTime << "->" << this->time << std::endl;
    }
}
void TrafficSim::print() const {
    std::cout << "Tijd: " << time << std::endl;
    for (const auto& voertuig : voertuigen) {
        std::cout << "Voertuig " << voertuig.voertuig_nummer() << std::endl;
        std::cout << "-> baan: " << voertuig.baan1() << std::endl;
        std::cout << "-> positie: " << voertuig.positie1() << std::endl;
        std::cout << "-> snelheid: " << voertuig.snelheid1() << std::endl;  // Snelheid is placeholder
    }
}











