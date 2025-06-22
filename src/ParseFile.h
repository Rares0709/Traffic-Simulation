//
// Created by jonas on 3/20/2025.
//

#ifndef PARSEFILE_H
#define PARSEFILE_H

#include "main.h"
#include <cmath>
#include <vector>
#include "TrafficSimulation.h"

    /**
     * Deze functie print uit wat er moet gedaan worden in 2.1
     * @param inputfile is de XML die wordt ingelezen om alle variabelen te verkrijgen
     * waarmee we gaan werken.
     */
   /**
    *@author Jonas Saelens
    *@date /
    *@version
    */
void parseFile(const std::string inputfile,std::vector<Baan>* banen,std::vector<Verkeersverkeerslicht>* verkeerslichten,std::vector<Voertuig>* voertuigen,std::vector<VoertuigGen> *voertuigengen,std::vector<Bushalte> *bushaltes,std::vector<Kruispunt> *kruispunten);

    /**
     * Dit is de main. Hier roepen we de functie aan die alles op gang zet.
     */
    /**
     *@author allemaal
     *@date /
     *@version /
     */


#endif //PARSEFILE_H
