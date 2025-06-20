//
// Created by jonas on 3/20/2025.
//
#include "ParseFile.h"
#include "DesignByContract.h"
#include "tinyxml.h"
int Voertuig::volgendeNummer = 1;
TrafficSim parseFile(const std::string inputfile) {
    REQUIRE(!inputfile.empty(), "Inputbestand mag niet leeg zijn.");
    TiXmlDocument doc;
    std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;

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
                if (childName == "baan") voertuig.set_baan(text->Value());
                if (childName == "positie") voertuig.set_positie(std::stoi(text->Value()));
                if (childName == "type") voertuig.setType(text->Value());
            }
            //std::cout << voertuig.baan << " " << voertuig.positie << std::endl;
            voertuigen.push_back(voertuig);
        }
        else if (elemName == "BAAN") {
            Baan baan;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "naam") baan.set_naam(text->Value());
                if (childName == "lengte") baan.set_lengte(std::stoi(text->Value()));
            }
            //std::cout << baan.naam << " " << baan.lengte << std::endl;
            banen.push_back(baan);
        }
        else if (elemName == "VERKEERSLICHT") {
            Verkeersverkeerslicht verkeerslicht;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "baan") verkeerslicht.set_baan(text->Value());
                if (childName == "positie") verkeerslicht.set_positie(std::stoi(text->Value()));
                if (childName == "cyclus") verkeerslicht.set_cyclus(std::stoi(text->Value()));
            }
            //std::cout << verkeerslicht.baan << " " << verkeerslicht.positie << " " << verkeerslicht.cyclus << " verkeerslicht toegevoegd!" << std::endl;
            verkeerslichten.push_back(verkeerslicht);
        }
        else if (elemName == "VOERTUIGGENERATOR") {
            VoertuigGen voertuiggen;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "baan") voertuiggen.set_baan(text->Value());
                if (childName == "frequentie") voertuiggen.set_freq(std::stoi(text->Value()));
            }
            //std::cout << voertuiggen.baan << " " << voertuiggen.freq << std::endl;
            voertuigengen.push_back(voertuiggen);
        }
        else if (elemName == "BUSHALTE") {
            Bushalte bushalte;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "baan") bushalte.set_baan(text->Value());
                if (childName == "positie") bushalte.set_positie(std::stoi(text->Value()));
                if (childName == "wachttijd") bushalte.set_wachttijd(std::stoi(text->Value()));
            }
            bushaltes.push_back(bushalte);
        }
        else if (elemName == "KRUISPUNT") {
            std::vector<std::pair<std::string, int>> temp;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                if (std::string(child->Value()) == "baan") {
                    const char* positieAttr = child->Attribute("positie");
                    if (positieAttr == nullptr) {
                        std::cerr << "Fout: baan in kruispunt zonder positie attribuut" << std::endl;
                        continue;
                    }
                    int positie = std::stoi(positieAttr);
                    std::string baanNaam = child->GetText();
                    temp.push_back({baanNaam, positie});
                }
            }
            // Controle: moet precies 2 banen zijn
            if (temp.size() == 2) {
                Kruispunt kruispunt;
                kruispunt.set_from_baan(temp[0].first);
                kruispunt.set_from_positie(temp[0].second);
                kruispunt.set_to_baan(temp[1].first);
                kruispunt.set_to_positie(temp[1].second);
                kruispunten.push_back(kruispunt);
            }
            else {
                std::cerr << "Fout: kruispunt heeft niet exact 2 banen." << std::endl;
            }
        }
    }
    doc.Clear();
    TrafficSim sim(banen, verkeerslichten, voertuigen, voertuigengen, bushaltes, kruispunten);
    ENSURE(!banen.empty(), "De ingelezen verkeerssituatie moet minstens 1 baan bevatten");
    return sim;;
}
