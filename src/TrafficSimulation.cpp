//
// Created by jonas on 3/20/2025.
//

#include "TrafficSimulation.h"
#include "DesignByContract.h"
void TrafficSim::Simulate(int duration) {
    double& currentTime = this->getTime();
    while (duration == -1 ? !voertuigen.empty() : currentTime <= duration) {
        if (!voertuigen.empty() || (duration != -1 && currentTime >= duration)) {
            if (!testingMode) {
                print();
            }
            for (Verkeerslicht& verkeerslicht : verkeerslichten) {
                for (Voertuig& voertuig : voertuigen) {
                    if (voertuig.positie < verkeerslicht.positie) {
                        verkeerslicht.voertuigenVoorLicht.push_back(voertuig);
                    }
                }
            }
            for (auto& voertuig : voertuigen) {
                berekenSnelheid(voertuig);
                berekenVersnelling(voertuig);
                geldig(voertuig);
            }
            // int size = toDelete.size();
            for (Voertuig& voertuig: toDelete) {
                int voertuignummer = voertuig.voertuigNummer;
                voertuigen.erase(voertuigen.begin()+voertuig.voertuigNummer-1);
                for (auto& voertuig1 : voertuigen) {
                    if (voertuig1.voertuigNummer > voertuignummer) {
                        voertuig1.voertuigNummer -= 1;
                        voertuig1.lowerVolgendeNummer();
                    }
                }
                for (auto& voertuig1 : toDelete) {
                    if (voertuig1.voertuigNummer > voertuignummer) {
                        voertuig1.voertuigNummer -= 1;
                    }
                }
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
                 verkeerslicht.voertuigenVoorLicht.clear;
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
            voertuig.versnelling=-(voertuig.maxremfactor*voertuig.snelheid/voertuig.maxversnelling);
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
        double delta = 0;
        double versnelling = voertuig.maxversnelling*(1-pow(voertuig.snelheid/voertuig.maxsnelheid,4) - pow(delta,2));
        voertuig.versnelling = versnelling;
    }

}
void TrafficSim::berekenSnelheid(Voertuig &voertuig) {
    double snelheid = voertuig.snelheid;
    double versnelling = voertuig.versnelling;
    double formule = snelheid + (versnelling*DeltaTime);
    double positie = voertuig.positie;
    if (snelheid>voertuig.mMaxsnelheid) {
        snelheid=voertuig.mMaxsnelheid;
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        voertuig.positie = positie;
    } else {
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
    }
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
void TrafficSim::vertragen(Voertuig &voertuig) {
    double s=voertuig.vertraagfactor;
    voertuig.maxsnelheid=s*voertuig.mMaxsnelheid;
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
void TrafficSim::kruispuntSim(std::vector<Kruispunt> kruispunten, Voertuig voertuig, std::vector<Baan>& banen) {
    for (Kruispunt kruispunt: kruispunten) {
        int breedte = 0;
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
void TrafficSim::checkverkeerslicht(Voertuig& voertuig) {
    for (Verkeerslicht& verkeerslicht : verkeerslichten) {
        if (verkeerslicht.kleur == verkeerslicht.rood) {
            if (voertuig.positie<= verkeerslicht.positie - voertuig.vertraagafstand) {
                vertragen(voertuigen[0]);
            } else if (voertuig.positie <= (verkeerslicht.positie - voertuig.vertraagafstand) /2) {
                stoppen(voertuigen[0]);
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
            versnellen(eersteVoertuig);
            for (auto &voertuig: verkeerslicht.voertuigenVoorLicht) {
                voertuig.gestopt=false;
            }
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
                if (eersteVoertuig.positie < verkeerslicht.positie && eersteVoertuig.positie >= Vertraag) {
                    vertragen(eersteVoertuig);
                } else if (eersteVoertuig.positie < verkeerslicht.positie && eersteVoertuig.positie >= Stop) {
                    stoppen(eersteVoertuig);
                    for (auto &voertuig: verkeerslicht.voertuigenVoorLicht) {
                        voertuig.gestopt=true;
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











