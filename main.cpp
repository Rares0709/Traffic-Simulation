//
// Created by grama on 2/27/2025.
//

#include "main.h"

#include <vector>

struct Baan {
    std::string naam;
    int lengte;
};

struct Verkeerslicht {
    Baan baan;
    int positie;
    int cyclus;
};

struct Voertuig {
    Baan baan;
    int positie;
};

struct VoertuigGen {
    //vermoedelijk voor later
    Baan baan;
    int freq;
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

private:
    std::vector<Baan> banen;
    std::vector<Verkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
};

TrafficSim readFile(const std::string inputfile) {
    TiXmlDocument doc;

    if (!doc.LoadFile(inputfile.c_str())) {
        std::cerr << "Fout bij laden van XML: " << doc.ErrorDesc() << std::endl;
        exit(1);
    }

    TiXmlElement* root = doc.FirstChildElement();
    if(root == NULL) {
        std::cerr << "Failed to load file: No root element." << std::endl;
        doc.Clear();
        exit(1);
    }

    for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();
        if (elemName == "VOERTUIG") {

        }
        else if (elemName == "BAAN") {

        }
        else if (elemName == "VERKEERSLICHT") {

        }
    }

}