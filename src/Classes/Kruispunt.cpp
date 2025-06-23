//
// Created by grama on 5/13/2025.
//

#include "Kruispunt.h"
Baan* Kruispunt::from_baan() const {
    ENSURE(this->fromBaan==fromBaan,"De getter geeft de verkeerde (from)baan mee.");
    return fromBaan;
}

void Kruispunt::set_from_baan(Baan * from_baan) {
    fromBaan = from_baan;
    ENSURE(this->fromBaan==from_baan,"De (from)baan is niet correct geset.");
}

int Kruispunt::from_positie() const {
    ENSURE(this->fromPositie==fromPositie,"De getter geeft de verkeerde (from)positie mee.");
    return fromPositie;
}

void Kruispunt::set_from_positie(int from_positie) {
    REQUIRE(from_positie >= 0, "De (from)positie kan alleen 0 of hoger zijn!");
    fromPositie = from_positie;
    ENSURE(this->fromPositie==from_positie,"De (from)positie is verkeerd geset.");
}

Baan* Kruispunt::to_baan() const {
    ENSURE(this->toBaan==toBaan,"De getter geeft de verkeerde (to)baan mee.");
    return toBaan;
}

void Kruispunt::set_to_baan(Baan*to_baan) {
    toBaan = to_baan;
    ENSURE(this->toBaan==to_baan,"De (to)baan is niet correct geset.");
}

int Kruispunt::to_positie() const {
    ENSURE(this->toPositie==toPositie,"De getter geeft de verkeerde (to)positie mee.");
    return toPositie;
}

void Kruispunt::set_to_positie(int to_positie) {
    REQUIRE(to_positie >= 0, "De (to)positie kan alleen 0 of hoger zijn!");
    toPositie = to_positie;
    ENSURE(this->toPositie==to_positie,"De (to)positie is verkeerd geset.");
}
void Kruispunt::kruispuntSim(Voertuig& voertuig, std::vector<Baan>& banen) {
    REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    REQUIRE(banen.size()>=2, "Er moeten minstens 2 banen aanwezig zijn.");
    REQUIRE(voertuig.baan1() != nullptr, "Voertuig moet een geldige baan hebben.");
    REQUIRE(this->from_baan() != nullptr, "Kruispunt heeft geen from_baan.");
    REQUIRE(this->to_baan() != nullptr, "Kruispunt heeft geen to_baan.");
    int breedte = 0;
    if (!voertuig.gedraait1()) {
        if (this->from_baan()->naam1() == voertuig.baan1()->naam1()) {
            //int breedte;
            for (const Baan& b : banen) {
                if (b.naam1() == this->from_baan()->naam1()) {
                    breedte = b.breedte1();
                    break;
                }
            }
            /*std::vector<std::string> baantje;
            baantje.push_back(kruispunt.fromBaan);
            baantje.push_back(kruispunt.toBaan);*/
            if (voertuig.positie1() >= this->from_positie() && voertuig.positie1() <= this->from_positie() + breedte) {
                std::srand(std::time(0));
                bool keuze = std::rand() % 2;
                // voertuig.baan = baantje[keuze];
                // voertuig.positie = baantje[]
                if (keuze) {
                    voertuig.set_baan(this->to_baan());
                    voertuig.set_positie(this->to_positie());
                    voertuig.set_gedraait(true);
                }
            }
        }
        else if (this->to_baan()->naam1() == voertuig.baan1()->naam1()) {
            for (const Baan& b : banen) {
                if (b.naam1() == this->to_baan()->naam1()) {
                    breedte = b.breedte1();
                    break;
                }
            }
            /*std::vector<std::string> baantje;
            baantje.push_back(kruispunt.fromBaan);
            baantje.push_back(kruispunt.toBaan);*/
            if (voertuig.positie1() >= this->to_positie() && voertuig.positie1() <= this->to_positie() + breedte) {
                std::srand(std::time(0));
                bool keuze = std::rand() % 2;
                // voertuig.baan = baantje[keuze];
                // voertuig.positie = baantje[]
                if (keuze) {
                    voertuig.set_baan(this->from_baan());
                    voertuig.set_positie(this->from_positie());
                    voertuig.set_gedraait(true);
                }
            }
        }
    }
    else if (voertuig.baan1()->naam1() == this->from_baan()->naam1()) {
        for (auto& baan : banen) {
            if (this->from_baan()->naam1() == baan.naam1()) {
                if (voertuig.positie1() > this->from_positie() + baan.breedte1()) {
                    voertuig.set_gedraait(false);
                }
            }
        }
    }
    else if (voertuig.baan1()->naam1() == this->to_baan()->naam1()) {
        for (auto& baan : banen) {
            if (this->to_baan()->naam1() == baan.naam1()) {
                if (voertuig.positie1() > this->to_positie() + baan.breedte1()) {
                    voertuig.set_gedraait(false);
                }
            }
        }
    }
    bool gevondenVoertuig = false;
    for (const Baan& baan : banen) {
        if (baan.naam1() == voertuig.baan1()->naam1()) {
            gevondenVoertuig = true;
            break;
        }
    }
    ENSURE(gevondenVoertuig,"Voertuig moet een geldige baan hebben die in de vector banen zit!");
}