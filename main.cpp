//
// Created by grama on 2/27/2025.
//

#include "main.h"
#include <cmath>
#include <vector>


struct Baan {
    std::string naam;
    int lengte;
};

struct Verkeerslicht {
    std::string baan;
    int positie = 0;
    int cyclus = 0;
};

struct Voertuig {
    std::string baan;
    int fmin = 4;
    int lengte = 4;
    double positie = 0;
    double Maxsnelheid = 16.6;
    double maxversnelling = 1.44;
    double snelheid = 0;
    double versnelling = 0;
    static int volgendeNummer;
    double vertraagfactor = 0.4;
    int vertraagafstand = 50;
    int stopafstand = 15;
    int voertuigNummer = 1;
    double maxremfactor = 4.61;
    double maxsnelheid = 16.6;
    Voertuig() : voertuigNummer(volgendeNummer++) {
    }
};
int Voertuig::volgendeNummer = 1;

struct VoertuigGen {
    //vermoedelijk voor later
    std::string baan;
    int freq = 0;
};

class TrafficSim {
public:
    TrafficSim(const std::vector<Baan> &banen, const std::vector<Verkeerslicht> &verkeerslichten,
        const std::vector<Voertuig> &voertuigen, const std::vector<VoertuigGen> &voertuigengen)
        : banen(banen),
          verkeerslichten(verkeerslichten),
          voertuigen(voertuigen),
          voertuigengen(voertuigengen) {
    }
    void berekenVersnelling(Voertuig& voertuig) {
        int indexLijst = voertuig.voertuigNummer - 1;
        if (indexLijst > 0) {
            int indexVoertuig2 = indexLijst - 1;
            Voertuig voertuig2 = voertuigen[indexVoertuig2];
            double volgafstand = voertuig2.positie - voertuig.positie - voertuig2.lengte;
            double snelheidsverschil = voertuig.snelheid - voertuig2.snelheid;
            double delta = voertuig.fmin + std::max(0.0, voertuig.snelheid + ( (voertuig.snelheid * snelheidsverschil) / (2 * std::sqrt(voertuig.maxversnelling * voertuig.maxremfactor)))) / volgafstand;
            double versnelling = voertuig.maxversnelling*(1-pow(voertuig.snelheid/voertuig.maxsnelheid,4) - pow(delta,2));
            voertuig.versnelling = versnelling;
        }
        else {
            double delta = 0;
            double versnelling = voertuig.maxversnelling*(1-pow(voertuig.snelheid/voertuig.maxsnelheid,4) - pow(delta,2));
            voertuig.versnelling = versnelling;
        }
    }
    void berekenSnelheid(Voertuig& voertuig) {
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

    void vertragenEnVersnellen(Voertuig& voertuig){
        double s=voertuig.vertraagfactor;
        int indexLijst = voertuig.voertuigNummer - 1;
        if (indexLijst==0) {
            voertuig.maxsnelheid=s*voertuig.Maxsnelheid;
        }
        else {
            int indexVoertuig2 = indexLijst - 1;
            if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
                Voertuig& voertuig2 = voertuigen[indexVoertuig2];
                voertuig.maxsnelheid = voertuig2.Maxsnelheid;
            }
        }
    }
    void stoppen(Voertuig& voertuig) {
        int indexLijst = voertuig.voertuigNummer - 1;

        if (indexLijst == 0) {
            voertuig.versnelling = - (voertuig.maxremfactor*voertuig.snelheid) / voertuig.maxsnelheid;
        } else {
            int indexVoertuig2 = indexLijst - 1;
            if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
                Voertuig& voertuig2 = voertuigen[indexVoertuig2];
                voertuig.versnelling = voertuig2.versnelling;
            }
        }
    }

    void geldig(const Voertuig voertuig, std::vector<Baan>& banen) {
        int indexLijst = voertuig.voertuigNummer - 1;
        std::string baannaam = voertuig.baan;
        int lengte = getBaanLengte(baannaam, banen);
        std::vector<Voertuig>& voertuigenvector = get_voertuigen();
        if (lengte < 0) {
            std::cout << "Bestaat niet." << std::endl;
        }
        else if (voertuig.positie > lengte) {
            voertuigenvector.erase(voertuigenvector.begin()+indexLijst);
            std::cout << "Voertuig weg van de baan" << std::endl;
            set_voertuigen(voertuigenvector);
        }
        else {
            std::cout << "er gebeurt niks" << std::endl;
        }
    }
    std::vector<Baan> get_banen() const {
        return banen;
    }

    void set_banen(const std::vector<Baan> &banen) {
        this->banen = banen;
    }


    void voegbaantoe(Baan baan) {
        this->banen.push_back(baan);
    }
    int getPositie(Voertuig voertuig) {
       return voertuig.positie;
    }
    int getSnelheid(Voertuig voertuig) {
        return voertuig.snelheid;
    }
    int getBaanLengte(std::string & baannaam, std:: vector<Baan>&banen) {
        for (Baan& b : banen) {
            if (b.naam == baannaam) {
                return b.lengte;
            }
        }
        return 0;
    }


    std::vector<Verkeerslicht> get_verkeerslichten() const {
        return verkeerslichten;
    }

    void set_verkeerslichten(const std::vector<Verkeerslicht> &verkeerslichten) {
        this->verkeerslichten = verkeerslichten;
    }

    void voegverkeerslichttoe(Verkeerslicht licht) {
        this->verkeerslichten.push_back(licht);
    }

    std::vector<Voertuig>& get_voertuigen() {
        return voertuigen;
    }
    void verhoogTijd() {
        time += 0.0166;
;
    }

    void set_voertuigen(const std::vector<Voertuig> &voertuigen) {
        this->voertuigen = voertuigen;
    }

    void voegvoertuigtoe(Voertuig voertuig) {
        this->voertuigen.push_back(voertuig);
    }
    void print() const {
        std::cout << "Tijd: " << time << std::endl;

        for (const auto& voertuig : voertuigen) {
            std::cout << "Voertuig " << voertuig.voertuigNummer << std::endl;
            std::cout << "-> baan: " << voertuig.baan << std::endl;
            std::cout << "-> positie: " << voertuig.positie << std::endl;
            std::cout << "-> snelheid: " << voertuig.snelheid << std::endl;  // Snelheid is placeholder
        }
    }

private:
    std::vector<Baan> banen;
    std::vector<Verkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    double time = 0.0166;
};

TrafficSim readFile(const std::string inputfile) {
    TiXmlDocument doc;

    std::vector<Baan> banen;
    std::vector<Verkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;

    if (!doc.LoadFile(inputfile.c_str())) {
        std::cerr << "Fout bij laden van XML: " << doc.ErrorDesc() << std::endl;
        exit(1);
    }

    for (TiXmlElement* elem = doc.FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();
        if (elemName == "VOERTUIG") {
            Voertuig voertuig;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "baan") voertuig.baan = text->Value();
                if (childName == "positie") voertuig.positie = std::stoi(text->Value());
            }
            //std::cout << voertuig.baan << " " << voertuig.positie << std::endl;
            voertuigen.push_back(voertuig);
        }
        else if (elemName == "BAAN") {
            Baan baan;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "naam") baan.naam = text->Value();
                if (childName == "lengte") baan.lengte = std::stoi(text->Value());
            }
            //std::cout << baan.naam << " " << baan.lengte << std::endl;
            banen.push_back(baan);
        }
        else if (elemName == "VERKEERSLICHT") {
            Verkeerslicht verkeerslicht;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "baan") verkeerslicht.baan = text->Value();
                if (childName == "positie") verkeerslicht.positie = std::stoi(text->Value());
                if (childName == "cyclus") verkeerslicht.cyclus = std::stoi(text->Value());
            }
            //std::cout << verkeerslicht.baan << " " << verkeerslicht.positie << " " << verkeerslicht.cyclus << std::endl;
            verkeerslichten.push_back(verkeerslicht);
        }
        if (elemName == "VOERTUIGGENERATOR") {
            VoertuigGen voertuiggen;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "baan") voertuiggen.baan = text->Value();
                if (childName == "frequentie") voertuiggen.freq = std::stoi(text->Value());
            }
            //std::cout << voertuiggen.baan << " " << voertuiggen.freq << std::endl;
            voertuigengen.push_back(voertuiggen);
        }
    }
    doc.Clear();
    return TrafficSim(banen, verkeerslichten, voertuigen, voertuigengen);
}
int main() {
    TrafficSim traffic = readFile("test1.xml");
    traffic.geldig(traffic.get_voertuigen()[0],traffic.get_banen());
    // traffic.berekenVersnelling(traffic.get_voertuigen()[0]);
    // traffic.berekenSnelheid(traffic.get_voertuigen()[0]);
    // traffic.berekenVersnelling(traffic.get_voertuigen()[1]);
    // traffic.berekenSnelheid(traffic.get_voertuigen()[1]);
    // traffic.print();
    return 0;
}
