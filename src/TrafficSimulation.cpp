//
// Created by jonas on 3/20/2025.
//
#include <algorithm>
#include "TrafficSimulation.h"
#include "DesignByContract.h"
void TrafficSim::Simulate(double duration) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(!this->get_banen().empty(), "Banen empty is niet goed geïnitialiseerd.");
    std::vector<std::vector<Verkeersverkeerslicht>> baanVerkeerslicht;
    Verkeersverkeerslicht vorigeVerkeerslicht;
    for (Baan baan : banen) {
        std::vector<Verkeersverkeerslicht> volgordeVerkeerslicht;
        for (const Verkeersverkeerslicht& verkeerslicht : verkeerslichten) {
            if (baan.naam1() == verkeerslicht.baan1()->naam1()) {
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
            for (Verkeersverkeerslicht verkeerslicht : verkeerslichten)
                verkeerslicht.checkverkeerslicht(&voertuigen);
            /*checkverkeerslicht();*/
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
                verkeerslicht.verkeerslichtSim(verkeerslicht, voertuigen, time, testingMode);
                //verkeerslichtSim(verkeerslicht);
        } else {
            if (!testingMode) {
                std::cout << "Geen verkeerslichten beschikbaar!" << std::endl;
            }
        }
        std::vector<Voertuig> empty;
        verhoogTijd();
        if (!voertuigengen.empty())
            for (VoertuigGen& gen : voertuigengen)
                gen.simVoertuiggenerator(&voertuigen, time);
            //simVoertuiggenerator();
        for (Verkeersverkeerslicht &verkeerslicht: verkeerslichten) {
             verkeerslicht.clear_voertuigvoorlicht();
        }
    }
    ENSURE(time >= 0, "De tijd moet positief zijn na simulatie.");
}
void TrafficSim::verhoogTijd() {
    REQUIRE(DeltaTime >= 0, "DeltaTime moet groter of gelijk zijn aan 0.");
    REQUIRE(time >= 0, "De tijd moet positief zijn vóór het verhogen.");
    double oldTime = this->time;
    double add = this->DeltaTime;
    setTime(this->time+add);
    if (!testingMode) {
        std::cout << "tijd verhoogd: " << oldTime << "->" << this->time << std::endl;
    }
    ENSURE(time == oldTime + DeltaTime, "De tijd is niet correct verhoogd.");
    ENSURE(time >= 0, "De tijd moet positief zijn na simulatie.");
}
void TrafficSim::print() const {
    REQUIRE(time >= 0, "De tijd moet positief zijn om af te drukken.");
    REQUIRE(!voertuigen.empty(), "Er moeten voertuigen zijn om af te drukken.");
    std::cout << "Tijd: " << time << std::endl;
    for (const auto& voertuig : voertuigen) {
        REQUIRE(voertuig.baan1() != nullptr, "Voertuig moet een geldige baan hebben.");
        std::cout << "Voertuig " << voertuig.voertuig_nummer() << std::endl;
        std::cout << "-> baan: " << voertuig.baan1()->naam1() << std::endl;
        std::cout << "-> positie: " << voertuig.positie1() << std::endl;
        std::cout << "-> snelheid: " << voertuig.snelheid1() << std::endl;  // Snelheid is placeholder
    }
    ENSURE(time >= 0, "De tijd moet positief blijven na het printen.");
    ENSURE(!voertuigen.empty(), "De voertuigenlijst mag niet leeg zijn na het printen.");
}











