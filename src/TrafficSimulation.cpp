//
// Created by jonas on 3/20/2025.
//
#include <algorithm>
#include "TrafficSimulation.h"
#include "DesignByContract.h"
void TrafficSim::Simulate(int duration) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!this->get_banen().empty(), "Banen empty is niet goed geïnitialiseerd.");
    std::vector<std::vector<Verkeerslicht>> baanVerkeerslicht;
    Verkeerslicht vorigeVerkeerslicht;
    for (Baan baan : banen) {
        std::vector<Verkeerslicht> volgordeVerkeerslicht;
        for (const Verkeerslicht& verkeerslicht : verkeerslichten) {
            if (baan.naam == verkeerslicht.baan) {
                if (volgordeVerkeerslicht.empty()) {
                    volgordeVerkeerslicht.push_back(verkeerslicht);
                    vorigeVerkeerslicht = verkeerslicht;
                }
                else if (vorigeVerkeerslicht.positie > verkeerslicht.positie) {
                    volgordeVerkeerslicht.insert(volgordeVerkeerslicht.begin() , verkeerslicht);
                }
                else if (vorigeVerkeerslicht.positie < verkeerslicht.positie) {
                    volgordeVerkeerslicht.push_back(verkeerslicht);
                }
            }
        }
        if (!volgordeVerkeerslicht.empty()) {
            baanVerkeerslicht.push_back(volgordeVerkeerslicht);
        }
    }
    std::vector<Verkeerslicht> fixedVerkeerslicht;
    for (auto& temp : baanVerkeerslicht) {
        for (const Verkeerslicht& verkeerslicht : temp) {
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
        for (Verkeerslicht& verkeerslicht : verkeerslichten) {
            for (Voertuig& voertuig : voertuigen) {
                if (voertuig.positie < verkeerslicht.positie) {
                    // Only add if not already in usedVoertuigen
                    auto it = std::find_if(usedVoertuigen.begin(), usedVoertuigen.end(), [&](const Voertuig& v) {
                        return v.voertuigNummer == voertuig.voertuigNummer;
                    });

                    if (it == usedVoertuigen.end()) {
                        if (voertuig.baan == verkeerslicht.baan) {
                            verkeerslicht.voertuigenVoorLicht.push_back(voertuig);
                            usedVoertuigen.push_back(voertuig);
                        }
                    }
                }
            }
        }
        if (!verkeerslichten.empty())
            checkverkeerslicht();
        for (auto& voertuig : voertuigen) {
            berekenSnelheid(voertuig);
            berekenVersnelling(voertuig);
            geldig(voertuig);
            if (!kruispunten.empty())
                kruispuntSim(voertuig);
            if (voertuig.type == "bus" && !bushaltes.empty())
                simBushaltes(voertuig);
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
            size_t idx = static_cast<size_t>(voertuig.voertuigNummer - 1);
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
            voertuigen[i].voertuigNummer = i + 1;
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
        verhoogTijd();
        if (!voertuigengen.empty())
            simVoertuiggenerator();
        for (Verkeerslicht &verkeerslicht: verkeerslichten) {
             verkeerslicht.voertuigenVoorLicht.clear();
        }
    }
    //ENSURE(!verkeerslichten.empty(), "Na simulatie mogen de verkeerslichten niet leeg zijn.");
    ENSURE(time >= 0, "De tijd moet positief zijn na simulatie.");
}
void TrafficSim::wagenToDelete(Voertuig &voertuig) {
    toDelete.push_back(voertuig);
    ENSURE(!toDelete.empty(), "Voertuig werd niet aan de deletelijst toegevoegd.");
    ENSURE(toDelete.back().voertuigNummer == voertuig.voertuigNummer, "Laatste voertuig in deletelijst is niet het toegevoegde voertuig.");

}
void TrafficSim::berekenVersnelling(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst > 0) {
        if (voertuig.gestopt) {
            voertuig.versnelling = -(voertuig.maxremfactor*voertuig.snelheid/voertuig.maxversnelling);
        } else {
            int indexVoertuig2 = indexLijst - 1;
            Voertuig voertuig2 = voertuigen[indexVoertuig2];
            double volgafstand = voertuig2.positie - voertuig.positie - voertuig2.lengte;
            double snelheidsverschil = voertuig.snelheid - voertuig2.snelheid;
            double delta = (voertuig.fmin + std::max(0.0, voertuig.snelheid + ( (voertuig.snelheid * snelheidsverschil) / (2 * std::sqrt(voertuig.maxversnelling * voertuig.maxremfactor)))))/ volgafstand;
            double versnelling = voertuig.maxversnelling*(1-pow(voertuig.snelheid/voertuig.maxsnelheid,4) - pow(delta,2));
            voertuig.versnelling = versnelling;
        }
    }
    else {
        if (voertuig.gestopt) {
            voertuig.versnelling = -(voertuig.maxremfactor*voertuig.snelheid/voertuig.maxversnelling);
        } else {
            double delta = 0;
            double versnelling = voertuig.maxversnelling*(1-pow(voertuig.snelheid/voertuig.maxsnelheid,4) - pow(delta,2));
            voertuig.versnelling = versnelling;
        }
    }
    ENSURE(std::isfinite(voertuig.versnelling), "Versnelling moet een geldig getal zijn.");
}
void TrafficSim::berekenSnelheid(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    double snelheid = voertuig.snelheid;
    double versnelling = voertuig.versnelling;
    double formule = snelheid + (versnelling*DeltaTime);
    double positie = voertuig.positie;
    /*if (snelheid>voertuig.mMaxsnelheid) {
        snelheid=voertuig.mMaxsnelheid;
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        voertuig.positie = positie;
    } else {*/
    if (formule < 0) {
        positie = positie - ((pow(snelheid, 2))/(2*versnelling));
        snelheid = 0;
        voertuig.positie = positie;
    }
    else {
        snelheid = snelheid + (versnelling*DeltaTime);
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        voertuig.positie = positie;
    }
    /*}*/
    voertuig.snelheid = snelheid;
    ENSURE(voertuig.snelheid >= 0, "Snelheid mag niet negatief zijn.");
    ENSURE(std::isfinite(voertuig.positie), "Positie moet een geldig getal zijn.");

}
void TrafficSim::versnellen(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    voertuig.maxsnelheid = voertuig.mMaxsnelheid;
    /*int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst == 0) {
        size_t indexVoertuig2 = indexLijst - 1;
        if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
            Voertuig& voertuig2 = voertuigen[indexVoertuig2];
            voertuig.maxsnelheid = voertuig2.mMaxsnelheid;
        }
    }*/
    ENSURE(voertuig.maxsnelheid == voertuig.mMaxsnelheid, "Voertuig moet zijn maximumsnelheid terug hebben.");
}
Voertuig TrafficSim::vertragen(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    double s=voertuig.vertraagfactor;
    voertuig.maxsnelheid=s*voertuig.mMaxsnelheid;
    return voertuig;
    ENSURE(voertuig.maxsnelheid < voertuig.mMaxsnelheid, "Na vertraging moet maxsnelheid lager zijn.");
}
void TrafficSim::kruispuntSim(/*std::vector<Kruispunt> kruispunten, */Voertuig& voertuig/*, std::vector<Baan>& banen*/) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!kruispunten.empty(), "Er bevindt zich geen kruispunt op de baan.");
    REQUIRE(banen.size()>=2, "Er moeten minstens 2 banen aanwezig zijn.");
    for (Kruispunt kruispunt: kruispunten) {
        int breedte = 0;
        if (!voertuig.gedraait) {
            if (kruispunt.fromBaan == voertuig.baan) {
                //int breedte;
                for (const Baan& b : banen) {
                    if (b.naam == kruispunt.fromBaan) {
                        breedte = b.breedte;
                        break;
                    }
                }
                /*std::vector<std::string> baantje;
                baantje.push_back(kruispunt.fromBaan);
                baantje.push_back(kruispunt.toBaan);*/
                if (voertuig.positie >= kruispunt.fromPositie && voertuig.positie <= kruispunt.fromPositie + breedte) {
                    std::srand(std::time(0));
                    bool keuze = std::rand() % 2;
                    // voertuig.baan = baantje[keuze];
                    // voertuig.positie = baantje[]
                    if (keuze) {
                        voertuig.baan = kruispunt.toBaan;
                        voertuig.positie = kruispunt.toPositie;
                        voertuig.gedraait = true;
                    }
                }
            }
            else if (kruispunt.toBaan == voertuig.baan) {
                for (const Baan& b : banen) {
                    if (b.naam == kruispunt.toBaan) {
                        breedte = b.breedte;
                        break;
                    }
                }
                /*std::vector<std::string> baantje;
                baantje.push_back(kruispunt.fromBaan);
                baantje.push_back(kruispunt.toBaan);*/
                if (voertuig.positie >= kruispunt.toPositie && voertuig.positie <= kruispunt.toPositie + breedte) {
                    std::srand(std::time(0));
                    bool keuze = std::rand() % 2;
                    // voertuig.baan = baantje[keuze];
                    // voertuig.positie = baantje[]
                    if (keuze) {
                        voertuig.baan = kruispunt.fromBaan;
                        voertuig.positie = kruispunt.fromPositie;
                        voertuig.gedraait = true;
                    }
                }
            }
        }
        else if (voertuig.baan == kruispunt.fromBaan) {
            for (auto& baan : banen) {
                if (kruispunt.fromBaan == baan.naam) {
                    if (voertuig.positie > kruispunt.fromPositie + baan.breedte) {
                        voertuig.gedraait = false;
                    }
                }
            }
        }
        else if (voertuig.baan == kruispunt.toBaan) {
            for (auto& baan : banen) {
                if (kruispunt.toBaan == baan.naam) {
                    if (voertuig.positie > kruispunt.toPositie + baan.breedte) {
                        voertuig.gedraait = false;
                    }
                }
            }
        }
    }
    ENSURE(std::find_if(banen.begin(), banen.end(), [&](const Baan& b) { return b.naam == voertuig.baan; }) != banen.end(), "Voertuig moet op een bestaande baan blijven.");
}
void TrafficSim::geldig(Voertuig &voertuig) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    int indexLijst = voertuig.voertuigNummer - 1;

    std::string baannaam = voertuig.baan;
    int lengte = getBaanLengte(baannaam, banen);
    if (lengte < 0) {
        /*std::cout << "Bestaat niet." << std::endl;*/
    }
    else if (voertuig.positie > lengte) {
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
    ENSURE(std::find_if(toDelete.begin(), toDelete.end(), [&](const Voertuig& v) { return v.voertuigNummer == voertuig.voertuigNummer; }) != toDelete.end() || voertuig.positie <= getBaanLengte(voertuig.baan, banen), "Voertuig is ongeldig verwijderd of buiten baan.");
}
void TrafficSim::checkverkeerslicht() {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!verkeerslichten.empty(), "Er bevinden zich geen verkeerslichten op de baan.");
    for (Verkeerslicht& verkeerslicht : verkeerslichten) {
        if (verkeerslicht.kleur==verkeerslicht.rood) {
            if (!testingMode) {
                std::cout << "Aantal voertuigen: " << voertuigen.size() << std::endl;
            }
            bool eersteGevonden = false;
            Voertuig eersteVoertuig;
            for (auto& voertuig : verkeerslicht.voertuigenVoorLicht) {
                if (voertuig.positie < verkeerslicht.positie && (eersteGevonden != true || voertuig.positie >= eersteVoertuig.positie )) {
                    if (!voertuig.prioriteit) {
                        eersteVoertuig = voertuig;
                        eersteGevonden = true;
                    }
                }
            }
            if (!eersteVoertuig.prioriteit && eersteGevonden) {
                double Vertraag = verkeerslicht.positie - eersteVoertuig.vertraagafstand;
                double Stop = verkeerslicht.positie - eersteVoertuig.stopafstand;
                if (eersteVoertuig.positie < Stop && eersteVoertuig.positie >= Vertraag) {
                    eersteVoertuig = vertragen(eersteVoertuig);
                    for (auto& voertuig : verkeerslicht.voertuigenVoorLicht) {
                        if (voertuig.voertuigNummer == eersteVoertuig.voertuigNummer) {
                            voertuig = eersteVoertuig;
                        }
                    }
                    for (auto& voertuig : voertuigen) {
                        if (voertuig.voertuigNummer == eersteVoertuig.voertuigNummer) {
                            voertuig = eersteVoertuig;
                        }
                    }
                } else if (eersteVoertuig.positie < verkeerslicht.positie && eersteVoertuig.positie >= Stop) {
                    //stoppen(eersteVoertuig);
                    for (auto& voertuig : verkeerslicht.voertuigenVoorLicht) {
                        if (voertuig.voertuigNummer == eersteVoertuig.voertuigNummer) {
                            voertuig = eersteVoertuig;
                        }
                    }
                    for (auto& voertuig : voertuigen) {
                        if (voertuig.voertuigNummer == eersteVoertuig.voertuigNummer) {
                            voertuig = eersteVoertuig;
                        }
                    }
                }
            }
        }
    }
    ENSURE(!verkeerslichten.empty(), "Verkeerslichten mogen niet leeg zijn na controle.");
}
void TrafficSim::verkeerslichtSim(Verkeerslicht& verkeerslicht) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!verkeerslichten.empty(), "Er bevinden zich geen verkeerslichten op de baan.");
    if (!testingMode) {
        std::cout << "Verkeerslicht op " << verkeerslicht.positie << " heeft kleur: " << verkeerslicht.kleur << std::endl;
    }
    int tijd = this->time;
    if (!testingMode) {
        std::cout << tijd << std::endl;
    }
    int TimeForSwitch = ceil(time - verkeerslicht.laatsteTijd);
    int verkeerslichtCyclus = verkeerslicht.cyclus;
    if (TimeForSwitch>verkeerslichtCyclus) {
        if (verkeerslicht.kleur==verkeerslicht.rood) {
            verkeerslicht.kleur="groen";
            if (!testingMode) {
                std::cout << "Aantal voertuigen: " << voertuigen.size() << std::endl;
            }
            bool eersteGevonden = false;
            Voertuig eersteVoertuig;
            for (auto& voertuig : verkeerslicht.voertuigenVoorLicht) {
                if (voertuig.positie < verkeerslicht.positie && (eersteGevonden != true || voertuig.positie >= eersteVoertuig.positie )) {
                    eersteVoertuig = voertuig;
                    eersteGevonden = true;
                }
            }
            eersteVoertuig.gestopt = false;
            if (eersteGevonden)
                versnellen(eersteVoertuig);
        }
        else if (verkeerslicht.kleur==verkeerslicht.groen) {
            verkeerslicht.kleur="rood";
            if (!testingMode) {
                std::cout << "Aantal voertuigen: " << voertuigen.size() << std::endl;
            }
            bool eersteGevonden = false;
            Voertuig eersteVoertuig;
            for (auto& voertuig : verkeerslicht.voertuigenVoorLicht) {
                if (voertuig.positie < verkeerslicht.positie && (eersteGevonden != true || voertuig.positie >= eersteVoertuig.positie )) {
                    eersteVoertuig = voertuig;
                    eersteGevonden = true;
                }
            }
            if (!eersteVoertuig.prioriteit && eersteGevonden) {
                double Vertraag = verkeerslicht.positie - eersteVoertuig.vertraagafstand;
                double Stop = verkeerslicht.positie - eersteVoertuig.stopafstand;
                if (eersteVoertuig.positie < Stop && eersteVoertuig.positie >= Vertraag) {
                    eersteVoertuig = vertragen(eersteVoertuig);
                    for (auto& voertuig : verkeerslicht.voertuigenVoorLicht) {
                        if (voertuig.voertuigNummer == eersteVoertuig.voertuigNummer) {
                            voertuig = eersteVoertuig;
                        }
                    }
                    for (auto& voertuig : voertuigen) {
                        if (voertuig.voertuigNummer == eersteVoertuig.voertuigNummer) {
                            voertuig = eersteVoertuig;
                        }
                    }
                } else if (eersteVoertuig.positie < verkeerslicht.positie && eersteVoertuig.positie >= Stop) {
                    //stoppen(eersteVoertuig);
                    eersteVoertuig.gestopt=true;
                    for (auto& voertuig : verkeerslicht.voertuigenVoorLicht) {
                        if (voertuig.voertuigNummer == eersteVoertuig.voertuigNummer) {
                            voertuig = eersteVoertuig;
                        }
                    }
                    for (auto& voertuig : voertuigen) {
                        if (voertuig.voertuigNummer == eersteVoertuig.voertuigNummer) {
                            voertuig = eersteVoertuig;
                        }
                    }
                }
            }
        }
        verkeerslicht.laatsteTijd=time;
    }
    ENSURE(verkeerslicht.kleur == verkeerslicht.rood || verkeerslicht.kleur == verkeerslicht.groen, "Kleur van verkeerslicht moet geldig zijn.");
    ENSURE(verkeerslicht.laatsteTijd <= time, "Laatste tijd van verkeerslicht mag niet in de toekomst liggen.");
    // std::cout << "kleur: --> " << verkeerslicht.kleur << std::endl;
}

void TrafficSim::simBushaltes(Voertuig &bus) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!bushaltes.empty(), "Er bevinden zich geen bushaltes op de baan.");
    REQUIRE(std::any_of(voertuigen.begin(), voertuigen.end(), [](const Voertuig& v) { return v.type == "bus"; }),
        "Er is geen bus aanwezig op de baan.");

    for (Bushalte bushalte : bushaltes) {
        double Vertraag = bushalte.positie - bus.vertraagafstand;
        double Stop = bushalte.positie - bus.stopafstand;
        if (bus.gestopt) {
            bus.timestop+=1;
        }
        if (bus.positie >= Vertraag && bus.positie <= Stop) {
            vertragen(bus);
        } else if(!bus.recentGestopt && bus.positie >= Stop && bus.positie <= bushalte.positie) {
            bus.gestopt = true;
        } else if (bus.recentGestopt && bus.positie > bushalte.positie){
            bus.recentGestopt=false;
        }
        if (bus.timestop > bushalte.wachttijd) {
            versnellen(bus);
            bus.gestopt = false;
            bus.timestop = 0;
        }
    }
}
void TrafficSim::simVoertuiggenerator() {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!voertuigengen.empty(), "Er is geen voertuiggenerator aanwezig.");
    for (auto& generator : voertuigengen) {
        int laatsteTijd = ceil(time - generator.laatsteTijd);
        if (laatsteTijd > generator.freq) {
            bool vrij = true;
            for (const auto& voertuig : voertuigen) {
                if (voertuig.baan == generator.baan && 0 <= voertuig.positie && voertuig.positie <= 2 * voertuig.lengte) {
                    vrij = false;
                    break;
                }
            }
            if (vrij){
                Voertuig nieuwVoertuig;
                nieuwVoertuig.baan = generator.baan;
                nieuwVoertuig.positie = 0;
                voertuigen.push_back(nieuwVoertuig);
                generator.laatsteTijd = time;
            }
        }
    }
}
int TrafficSim::getBaanLengte(std::string &baannaam, std::vector<Baan> &banen) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    for (Baan& b : banen) {
        if (b.naam == baannaam) {
            return b.lengte;
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
        std::cout << "Voertuig " << voertuig.voertuigNummer << std::endl;
        std::cout << "-> baan: " << voertuig.baan << std::endl;
        std::cout << "-> positie: " << voertuig.positie << std::endl;
        std::cout << "-> snelheid: " << voertuig.snelheid << std::endl;  // Snelheid is placeholder
    }
}











