//
// Created by grama on 5/13/2025.
//

#ifndef VERKEERSVERKEERSLICHT_H
#define VERKEERSVERKEERSLICHT_H



class Verkeersverkeerslicht {
    std::string baan;
    int positie = 0;
    int cyclus = 0;
    std::string rood="rood";
    std::string groen="groen";
    std::string kleur="rood";
    int laatsteTijd = 0;
    std::vector<Voertuig> voertuigenVoorLicht;

};



#endif //VERKEERSVERKEERSLICHT_H
