//
// Created by jonas on 3/20/2025.
//
#include <algorithm>
#include "TrafficSimulation.h"
#include "DesignByContract.h"
void TrafficSim::Simulate(int duration) {
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
    while (duration == -1 ? !voertuigen.empty() : currentTime <= duration) {
        if (!voertuigen.empty() || (duration != -1 && currentTime >= duration)) {
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
            checkverkeerslicht();
            for (auto& voertuig : voertuigen) {
                berekenSnelheid(voertuig);
                berekenVersnelling(voertuig);
                geldig(voertuig);
                kruispuntSim(voertuig);
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
            simVoertuiggenerator();
            for (Verkeerslicht &verkeerslicht: verkeerslichten) {
                 verkeerslicht.voertuigenVoorLicht.clear();
            }
        }
        else {
            break;
        }
    }
}
void TrafficSim::wagenToDelete(Voertuig &voertuig) {
    toDelete.push_back(voertuig);
}
void TrafficSim::berekenVersnelling(Voertuig &voertuig) {
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

}
void TrafficSim::berekenSnelheid(Voertuig &voertuig) {
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

}
void TrafficSim::versnellen(Voertuig &voertuig) {
    voertuig.maxsnelheid = voertuig.mMaxsnelheid;
    /*int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst == 0) {
        size_t indexVoertuig2 = indexLijst - 1;
        if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
            Voertuig& voertuig2 = voertuigen[indexVoertuig2];
            voertuig.maxsnelheid = voertuig2.mMaxsnelheid;
        }
    }*/
}
Voertuig TrafficSim::vertragen(Voertuig &voertuig) {
    double s=voertuig.vertraagfactor;
    voertuig.maxsnelheid=s*voertuig.mMaxsnelheid;
    return voertuig;
}
void TrafficSim::stoppen(Voertuig &voertuig) {


    // int indexLijst = voertuig.voertuigNummer - 1;
    // if (indexLijst == 0) {
    //     voertuig.versnelling = - (voertuig.maxremfactor*voertuig.snelheid) / voertuig.maxsnelheid;
    // } else {
    //     size_t indexVoertuig2 = indexLijst - 1;
    //     if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
    //         Voertuig& voertuig2 = voertuigen[indexVoertuig2];
    //         voertuig.versnelling = voertuig2.versnelling;
    //     }
    // }
}
void TrafficSim::kruispuntSim(/*std::vector<Kruispunt> kruispunten, */Voertuig& voertuig/*, std::vector<Baan>& banen*/) {
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
}
void TrafficSim::geldig(Voertuig &voertuig) {
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
}
void TrafficSim::checkverkeerslicht() {
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
            if (!eersteVoertuig.prioriteit) {
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
    }
}
void TrafficSim::verkeerslichtSim(Verkeerslicht& verkeerslicht) {
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
            if (!eersteVoertuig.prioriteit) {
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
    // std::cout << "kleur: --> " << verkeerslicht.kleur << std::endl;
}

void TrafficSim::simBushaltes(Voertuig &bus) {
    for (Bushalte bushalte : bushaltes) {
        if (bus.positie == bushalte.positie+bus.vertraagafstand) {
            vertragen(bus);
        } else if(bus.positie == bushalte.positie+bus.stopafstand) {
            stoppen(bus);
        } if (bus.timestop > bushalte.wachttijd) {
            versnellen(bus);
        } if (bus.snelheid == 0) {
            bus.timestop+=1;
        }
    }
}
void TrafficSim::simVoertuiggenerator() {
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











