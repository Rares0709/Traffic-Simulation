//
// Created by jonas on 3/20/2025.
//

#include "TrafficSimulation.h"
void TrafficSim::Simulate() {
    while (!voertuigen.empty()) {
        print();
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
            std::cout << verkeerslichten.size() << std::endl;
            for (auto& verkeerslicht : verkeerslichten)
                verkeerslichtSim(verkeerslicht);
        } else {
            std::cout << "Geen verkeerslichten beschikbaar!" << std::endl;
        }
        verhoogTijd();
        simVoertuiggenerator();
    }
}
void TrafficSim::wagenToDelete(Voertuig &voertuig) {
    toDelete.push_back(voertuig);
}
void TrafficSim::berekenVersnelling(Voertuig &voertuig) {
    int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst > 0) {
        int indexVoertuig2 = indexLijst - 1;
        Voertuig voertuig2 = voertuigen[indexVoertuig2];
        double volgafstand = voertuig2.positie - voertuig.positie - voertuig2.lengte;
        double snelheidsverschil = voertuig.snelheid - voertuig2.snelheid;
        double delta = (voertuig.fmin + std::max(0.0, voertuig.snelheid + ( (voertuig.snelheid * snelheidsverschil) / (2 * std::sqrt(voertuig.maxversnelling * voertuig.maxremfactor)))))/ volgafstand;
        double versnelling = voertuig.maxversnelling*(1-pow(voertuig.snelheid/voertuig.maxsnelheid,4) - pow(delta,2));
        voertuig.versnelling = versnelling;
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
    double formule = snelheid + (versnelling*time);
    double positie = voertuig.positie;
    if (formule < 0) {
        positie = positie - ((pow(snelheid, 2))/(2*versnelling));
        snelheid = 0;
        voertuig.positie = positie;
    }
    else {
        snelheid = snelheid + (versnelling*time);
        positie = positie + (snelheid*time) + (versnelling)*((pow(time,2))/2);
        voertuig.positie = positie;
    }
    voertuig.snelheid = snelheid;
}
void TrafficSim::versnellen(Voertuig &voertuig) {
    int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst == 0) {
        size_t indexVoertuig2 = indexLijst - 1;
        if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
            Voertuig& voertuig2 = voertuigen[indexVoertuig2];
            voertuig.maxsnelheid = voertuig2.mMaxsnelheid;
        }
    }
}
void TrafficSim::vertragen(Voertuig &voertuig) {
    double s=voertuig.vertraagfactor;
    int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst==0) {
        voertuig.maxsnelheid=s*voertuig.mMaxsnelheid;
    }
}
void TrafficSim::stoppen(Voertuig &voertuig) {
    int indexLijst = voertuig.voertuigNummer - 1;

    if (indexLijst == 0) {
        voertuig.versnelling = - (voertuig.maxremfactor*voertuig.snelheid) / voertuig.maxsnelheid;
    } else {
        size_t indexVoertuig2 = indexLijst - 1;
        if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
            Voertuig& voertuig2 = voertuigen[indexVoertuig2];
            voertuig.versnelling = voertuig2.versnelling;
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
void TrafficSim::verkeerslichtSim(Verkeerslicht&verkeerslicht) {
    std::cout << "Verkeerslicht op " << verkeerslicht.positie << " heeft kleur: " << verkeerslicht.kleur << std::endl;
    int tijd = this->time;
    std::cout << tijd << std::endl;
    if (tijd>verkeerslicht.cyclus) {
        if (verkeerslicht.kleur==verkeerslicht.rood) {
            verkeerslicht.kleur="groen";
            if (verkeerslicht.kleur==verkeerslicht.groen) {
                for (auto& voertuig : voertuigen) {
                    versnellen( voertuig);
                }
            }
        }
        else if (verkeerslicht.kleur==verkeerslicht.groen) {
            verkeerslicht.kleur="rood";
            if (verkeerslicht.kleur==verkeerslicht.rood) {
                if (voertuigen[0].positie<=voertuigen[0].vertraagafstand ) {
                    vertragen(voertuigen[0]);
                } else if (voertuigen[0].positie<=voertuigen[0].vertraagafstand/2) {
                    stoppen(voertuigen[0]);
                }
            }
        }
    }
    // std::cout << "kleur: --> " << verkeerslicht.kleur << std::endl;
}
void TrafficSim::simVoertuiggenerator() {
    for (auto& generator : voertuigengen) {
        int laatsteTijd = time - generator.laatsteTijd;
        if (laatsteTijd > generator.freq) {
            bool vrij = true;
            for (const auto& voertuig : voertuigen) {
                if (voertuig.baan == generator.baan && 0 <= voertuig.positie  && voertuig.positie <= 2 * voertuig.lengte) {
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
    double add = 1;
    setTime(this->time+add);
    std::cout << "tijd verhoogd: " << oldTime << "->" << this->time << std::endl;
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











