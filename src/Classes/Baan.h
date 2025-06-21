//
// Created by grama on 5/13/2025.
//

#ifndef BAAN_H
#define BAAN_H
#include <string>
#include <vector>
#include "DesignByContract.h"



class Baan {
    std::string naam;
    int lengte;
    int breedte = 180;
public:
    std::vector<Baan> get_banen() const {
        return banen;
    }
    void setBanen(const std::vector<Baan> &banen) {
        this->banen = banen;
    }

    void voegbaantoe(Baan baan) {
        this->banen.push_back(baan);
    }
    std::string naam1() const {
        return naam;
    }

    void set_naam(const std::string &naam) {
        this->naam = naam;
    }

    int lengte1() const {
        return lengte;
    }

    void set_lengte(int lengte) {
        this->lengte = lengte;
    }

    int breedte1() const {
        return breedte;
    }

    void set_breedte(int breedte) {
        this->breedte = breedte;
    }
    /**
     * Deze functie geeft de lengte van de baan weer waarop het voertuig rijdt.
     * @param baannaam is de naam van de baan.
     * @param banen is de verzameling van alle banen.
     */
    /**
    *@author Ilyas Sefiani
    *@date /
    *@version
    */
    int getBaanLengte(std::string & baannaam, std:: vector<Baan>&banen);
};



#endif //BAAN_H
