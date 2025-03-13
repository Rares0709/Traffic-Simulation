//
// Created by grama on 2/27/2025.
//

#include "main.h"

#include <vector>

class weg {

};
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
    int positie = 0;
};

struct VoertuigGen {
    //vermoedelijk voor later
    Baan baan;
    int freq = 0;
};

class TrafficSim {
//Dit gaat verplaatst worden naar zijn eigen cpp bestand
public:
    TrafficSim(const std::vector<Baan> &banen, const std::vector<Verkeerslicht> &verkeerslichten,
               const std::vector<Voertuig> &voertuigen)
        : banen(banen),
          verkeerslichten(verkeerslichten),
          voertuigen(voertuigen) {
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

    std::vector<Verkeerslicht> get_verkeerslichten() const {
        return verkeerslichten;
    }

    void set_verkeerslichten(const std::vector<Verkeerslicht> &verkeerslichten) {
        this->verkeerslichten = verkeerslichten;
    }

    void voegverkeerslichttoe(Verkeerslicht licht) {
        this->verkeerslichten.push_back(licht);
    }

    std::vector<Voertuig> get_voertuigen() const {
        return voertuigen;
    }

    void set_voertuigen(const std::vector<Voertuig> &voertuigen) {
        this->voertuigen = voertuigen;
    }

    void voegvoertuigtoe(Voertuig voertuig) {
        this->voertuigen.push_back(voertuig);
    }

    void print() const {
        std::cout << "Tijd: " << time << std::endl;

        int voertuigNummer = 1;
        for (const auto& voertuig : voertuigen) {
            std::cout << "Voertuig " << voertuigNummer++ << std::endl;
            std::cout << "-> baan: " << voertuig.baan << std::endl;
            std::cout << "-> positie: " << voertuig.positie << std::endl;
            std::cout << "-> snelheid: " << "tbm" << std::endl;  // Snelheid is placeholder
        }
    }

private:
    std::vector<Baan> banen;
    std::vector<Verkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    int time = 0;
};

TrafficSim readFile(const std::string inputfile) {
    TiXmlDocument doc;

    std::vector<Baan> banen;
    std::vector<Verkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;

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
    }
    doc.Clear();
    return TrafficSim(banen, verkeerslichten, voertuigen);
}
int main() {
    TrafficSim traffic = readFile("test1.xml");
    traffic.print();
    return 0;
}
