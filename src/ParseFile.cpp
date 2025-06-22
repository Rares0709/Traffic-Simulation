//
// Created by jonas on 3/20/2025.
//
#include "ParseFile.h"
#include "DesignByContract.h"
#include "tinyxml.h"
int Voertuig::volgendeNummer = 1;
void parseFile(const std::string inputfile,std::vector<Baan>* banen,std::vector<Verkeersverkeerslicht>* verkeerslichten,std::vector<Voertuig>* voertuigen,std::vector<VoertuigGen> *voertuigengen,std::vector<Bushalte> *bushaltes,std::vector<Kruispunt> *kruispunten) {
    REQUIRE(!inputfile.empty(), "Inputbestand mag niet leeg zijn.");
    TiXmlDocument doc;
    /*std::vector<Baan> banen;
    std::vector<Verkeersverkeerslicht> verkeerslichten;
    std::vector<Voertuig> voertuigen;
    std::vector<VoertuigGen> voertuigengen;
    std::vector<Bushalte> bushaltes;
    std::vector<Kruispunt> kruispunten;*/

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
                if (childName == "baan") {
                    bool isGevonden = false;
                    Baan* gevondenBaan;
                    std::string baannaam= text->Value();
                    for (Baan& baan: *banen) {
                        if (baan.naam1() == baannaam) {
                            gevondenBaan = &baan;
                            isGevonden = true;
                        }
                    }
                    if (isGevonden) {
                        voertuig.set_baan(gevondenBaan);
                    }
                }
                if (childName == "positie") voertuig.set_positie(std::stoi(text->Value()));
                if (childName == "type") {
                    std::string type = text->Value();
                    if (type == "auto") {
                        Auto a;
                        a.set_baan(voertuig.baan1());
                        a.set_positie(voertuig.positie1());
                        voertuigen->push_back(a);
                    } else if (type == "bus") {
                        Bus b;
                        b.set_baan(voertuig.baan1());
                        b.set_positie(voertuig.positie1());
                        voertuigen->push_back(b);
                    } else if (type == "brandweerwagen") {
                        Brandweerwagen bw;
                        bw.set_baan(voertuig.baan1());
                        bw.set_positie(voertuig.positie1());
                        voertuigen->push_back(bw);
                    } else if (type == "ziekenwagen") {
                        Ziekenwagen z;
                        z.set_baan(voertuig.baan1());
                        z.set_positie(voertuig.positie1());
                        voertuigen->push_back(z);
                    } else if (type == "politiecombi") {
                        Politiecombi p;
                        p.set_baan(voertuig.baan1());
                        p.set_positie(voertuig.positie1());
                        voertuigen->push_back(p);
                    }
                }
            }
            //std::cout << voertuig.baan << " " << voertuig.positie << std::endl;
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
            banen->push_back(baan);
        }
        else if (elemName == "VERKEERSLICHT") {
            Verkeersverkeerslicht verkeerslicht;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "baan") {
                    bool isGevonden = false;
                    Baan *gevondenBaan = nullptr;
                    std::string baannaam= text->Value();
                    for (Baan& baan: *banen) {
                        if (baan.naam1() == baannaam) {
                            gevondenBaan = &baan;
                            isGevonden = true;
                        }
                    }
                    if (isGevonden) {
                        verkeerslicht.set_baan(gevondenBaan);
                    }
                }
                if (childName == "positie") verkeerslicht.set_positie(std::stoi(text->Value()));
                if (childName == "cyclus") verkeerslicht.set_cyclus(std::stoi(text->Value()));
            }
            //std::cout << verkeerslicht.baan << " " << verkeerslicht.positie << " " << verkeerslicht.cyclus << " verkeerslicht toegevoegd!" << std::endl;
            verkeerslichten->push_back(verkeerslicht);
        }
        else if (elemName == "VOERTUIGGENERATOR") {
            VoertuigGen voertuiggen;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "baan") {
                    bool isGevonden = false;
                    Baan *gevondenBaan;
                    std::string baannaam= text->Value();
                    for (Baan& baan: *banen) {
                        if (baan.naam1() == baannaam) {
                            gevondenBaan = &baan;
                            isGevonden = true;
                        }
                    }
                    if (isGevonden) {
                        voertuiggen.set_baan(gevondenBaan);
                    }
                }
                if (childName == "frequentie") voertuiggen.set_freq(std::stoi(text->Value()));
            }
            //std::cout << voertuiggen.baan << " " << voertuiggen.freq << std::endl;
            voertuigengen->push_back(voertuiggen);
        }
        else if (elemName == "BUSHALTE") {
            Bushalte bushalte;
            for (TiXmlElement* child = elem->FirstChildElement(); child != NULL; child = child->NextSiblingElement()) {
                TiXmlText* text = child->FirstChild()->ToText();
                std::string childName = child->Value();
                if (childName == "baan") {
                    bool isGevonden = false;
                    Baan *gevondenBaan;
                    std::string baannaam= text->Value();
                    for (Baan& baan: *banen) {
                        if (baan.naam1() == baannaam) {
                            gevondenBaan = &baan;
                            isGevonden = true;
                        }
                    }
                    if (isGevonden) {
                        bushalte.set_baan(gevondenBaan);
                    }
                }
                if (childName == "positie") bushalte.set_positie(std::stoi(text->Value()));
                if (childName == "wachttijd") bushalte.set_wachttijd(std::stoi(text->Value()));
            }
            bushaltes->push_back(bushalte);
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
                bool isGevonden1 = false;
                Baan *gevondenBaan1;
                std::string baannaam1= temp[0].first;
                for (Baan& baan: *banen) {
                    if (baan.naam1() == baannaam1) {
                        gevondenBaan1 = &baan;
                        isGevonden1 = true;
                    }
                }
                if (isGevonden1) {
                    kruispunt.set_from_baan(gevondenBaan1);
                }
                bool isGevonden2 = false;
                Baan* gevondenBaan2;
                std::string baannaam= temp[1].first;
                for (Baan& baan: *banen) {
                    if (baan.naam1() == baannaam) {
                        gevondenBaan2 = &baan;
                        isGevonden2 = true;
                    }
                }
                if (isGevonden2) {
                    kruispunt.set_to_baan(gevondenBaan2);
                }
                kruispunt.set_from_positie(temp[0].second);
                kruispunt.set_to_positie(temp[1].second);
                kruispunten->push_back(kruispunt);
            }
            else {
                std::cerr << "Fout: kruispunt heeft niet exact 2 banen." << std::endl;
            }
        }
    }
    doc.Clear();
    ENSURE(!banen->empty(), "De ingelezen verkeerssituatie moet minstens 1 baan bevatten");
}
