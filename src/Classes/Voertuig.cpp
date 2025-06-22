//
// Created by grama on 5/13/2025.
//

#include "Voertuig.h"
#include "DesignByContract.h"
#include "TrafficSimulation.h"
void Voertuig::lowerVolgendeNummer(){
    volgendeNummer--;
}

void Voertuig::setType(const std::string& nieuwType) {
    type = nieuwType;
    if (type == "auto") {
        lengte = 4;
        mMaxsnelheid = maxsnelheid = 16.6;
        maxversnelling = 1.44;
        maxremfactor = 4.61;
        fmin = 4;
    } else if (type == "bus") {
        lengte = 12;
        mMaxsnelheid = maxsnelheid = 11.4;
        maxversnelling = 1.22;
        maxremfactor = 4.29;
        fmin = 12;
    } else if (type == "brandweerwagen") {
        lengte = 10;
        mMaxsnelheid = maxsnelheid = 14.6;
        maxversnelling = 1.33;
        maxremfactor = 4.56;
        fmin = 10;
        prioriteit = true;
    } else if (type == "ziekenwagen") {
        lengte = 8;
        mMaxsnelheid = maxsnelheid = 15.5;
        maxversnelling = 1.44;
        maxremfactor = 4.47;
        fmin = 8;
        prioriteit = true;
    } else if (type == "politiecombi") {
        lengte = 6;
        mMaxsnelheid = maxsnelheid = 17.2;
        maxversnelling = 1.55;
        maxremfactor = 4.92;
        fmin = 6;
        prioriteit = true;
    } else {
        exit(1);
    }
}

void Voertuig::berekenVersnelling(Voertuig* voertuig2) {
    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    int indexLijst = this->voertuig_nummer() - 1;
    if (indexLijst > 0) {
        if (this->gestopt1()) {
            this->set_versnelling(-(this->maxremfactor1()*this->snelheid1()/this->maxversnelling1()));
        } else {
            double volgafstand = voertuig2->positie1() - this->positie1() - voertuig2->lengte1();
            double snelheidsverschil = this->snelheid1() - voertuig2->snelheid1();
            double delta = (this->fmin1() + std::max(0.0, this->snelheid1() + ( (this->snelheid1() * snelheidsverschil) / (2 * std::sqrt(this->maxversnelling1() * this->maxremfactor1())))))/ volgafstand;
            double versnelling = this->maxversnelling1()*(1-pow(this->snelheid1()/this->maxsnelheid1(),4) - pow(delta,2));
            this->set_versnelling(versnelling);
        }
    }
    else {
        if (this->gestopt1()) {
            this->set_versnelling(-(this->maxremfactor1()*this->snelheid1()/this->maxversnelling1()));
        } else {
            double delta = 0;
            double versnelling = this->maxversnelling1()*(1-pow(this->snelheid1()/this->maxsnelheid1(),4) - pow(delta,2));
            this->set_versnelling(versnelling);
        }
    }
    // ENSURE(std::isfinite(this->versnelling1()), "Versnelling moet een geldig getal zijn.");
}
void Voertuig::berekenSnelheid(double& DeltaTime) {
    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    double snelheid = this->snelheid1();
    double versnelling = this->versnelling1();
    double formule = snelheid + (versnelling*DeltaTime);
    double positie = this->positie1();
    /*if (snelheid>voertuig.mMaxsnelheid) {
        snelheid=voertuig.mMaxsnelheid;
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        voertuig.positie = positie;
    } else {*/
    if (formule < 0) {
        positie = positie - ((pow(snelheid, 2))/(2*versnelling));
        snelheid = 0;
        this->set_positie(positie);
    }
    else {
        snelheid = snelheid + (versnelling*DeltaTime);
        positie = positie + (snelheid*DeltaTime) + (versnelling)*((pow(DeltaTime,2))/2);
        this->set_positie(positie);
    }
    /*}*/
    this->set_snelheid(snelheid);
    // ENSURE(this->snelheid1() >= 0, "Snelheid mag niet negatief zijn.");
    // ENSURE(std::isfinite(this->positie1()), "Positie moet een geldig getal zijn.");

}
void Voertuig::versnellen() {
    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    this->set_maxsnelheid(this->m_Maxsnelheid());
    /*int indexLijst = voertuig.voertuigNummer - 1;
    if (indexLijst == 0) {
        size_t indexVoertuig2 = indexLijst - 1;
        if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
            Voertuig& voertuig2 = voertuigen[indexVoertuig2];
            voertuig.maxsnelheid = voertuig2.mMaxsnelheid;
        }
    }*/
    // ENSURE(this->maxsnelheid1() == this->m_Maxsnelheid(), "Voertuig moet zijn maximumsnelheid terug hebben.");
}
void Voertuig::vertragen() {
    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    double s=this->vertraagfactor1();
    this->set_maxsnelheid(s*this->m_Maxsnelheid());
    // ENSURE(this->maxsnelheid1() < this->m_Maxsnelheid(), "Na vertraging moet maxsnelheid lager zijn.");
}

void Voertuig::geldig(std::vector<Baan> &banen,Voertuig& voertuigtodelete,std::vector<Voertuig>* toDelete) {
    // REQUIRE(!banen.empty(), "Er zijn geen banen aanwezig.");
    // REQUIRE(!voertuigen.empty(), "Er bevindt zich geen voertuig op de baan.");
    //int indexLijst = this->voertuig_nummer() - 1;
    std::string baannaam = this->baan1();
    int lengte =0;
    for (Baan& b : banen) {
        if (b.naam1() == baannaam) {
            lengte = b.lengte1();
        }
    }
    if (lengte < 0) {
        /*std::cout << "Bestaat niet." << std::endl;*/
    }
    else if (this->positie1() > lengte) {
        // if (voertuigen.size() > 1){
        //     Voertuig& voertuig2 = voertuigen[indexLijst + 1];
        //     voertuig2.voertuigNummer = voertuig.voertuigNummer;
        // }
        //voertuigen.erase(voertuigen.begin()+indexLijst);
        wagenToDelete(voertuigtodelete,toDelete);
        /*std::cout << "Voertuig weg van de baan" << std::endl;*/
    }
    else {
        /*std::cout << "er gebeurt niks" << std::endl;*/
    }
    std::string baanNaam=this->baan1();
    // ENSURE(std::find_if(toDelete.begin(), toDelete.end(), [&](const Voertuig& v) { return v.voertuig_nummer() == voertuig.voertuig_nummer(); }) != toDelete.end() || voertuig.positie1() <= getBaanLengte(baanNaam, banen), "Voertuig is ongeldig verwijderd of buiten baan.");
}
void Voertuig::wagenToDelete(Voertuig &voertuig,std::vector<Voertuig>* toDelete) {
    toDelete->push_back(voertuig);
    // ENSURE(!toDelete.empty(), "Voertuig werd niet aan de deletelijst toegevoegd.");
    // ENSURE(toDelete.back().voertuig_nummer() == voertuig.voertuig_nummer(), "Laatste voertuig in deletelijst is niet het toegevoegde voertuig.");
}
