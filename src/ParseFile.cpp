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
            std::cout << verkeerslicht.baan << " " << verkeerslicht.positie << " " << verkeerslicht.cyclus << " verkeerslicht toegevoegd!" << std::endl;
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
    TrafficSim sim(banen, verkeerslichten, voertuigen, voertuigengen);
    ENSURE(!banen.empty() || !voertuigen.empty() || !verkeerslichten.empty() || !voertuigengen.empty(),
           "De ingelezen verkeerssituatie moet minstens één element bevatten");
    return sim;;
}
