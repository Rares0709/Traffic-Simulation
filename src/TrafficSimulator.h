//
// Created by jonas on 3/20/2025.
//

#include <cmath>
#include <vector>
#include <iostream>


struct Baan {
    std::string naam;
    int lengte;
};

struct Verkeerslicht {
    std::string baan;
    int positie = 0;
    int cyclus = 0;
    std::string rood="rood";
    std::string groen="groen";
    std::string kleur;
};

struct Voertuig {
    Voertuig(const std::string &baan, int fmin, int lengte, double positie, double maxsnelheid, double maxversnelling,
        double snelheid, double versnelling, double vertraagfactor, int vertraagafstand, int stopafstand,
        int voertuig_nummer, double maxremfactor, double maxsnelheid1)
        : baan(baan),
          fmin(fmin),
          lengte(lengte),
          positie(positie),
          mMaxsnelheid(maxsnelheid),
          maxversnelling(maxversnelling),
          snelheid(snelheid),
          versnelling(versnelling),
          vertraagfactor(vertraagfactor),
          vertraagafstand(vertraagafstand),
          stopafstand(stopafstand),
          voertuigNummer(voertuig_nummer),
          maxremfactor(maxremfactor),
          maxsnelheid(maxsnelheid1) {
    }

    std::string baan;
    int fmin = 4;
    int lengte = 4;
    double positie = 0;
    double mMaxsnelheid = 16.6;
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
    /**
     * Deze functuie simuleert de verkeerssituatie door alle voertuigen te verwerken en de tijd te verhogen.
     */
    /**
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void Simulate() {
        print();
        while (!voertuigen.empty()) {
            for (auto& voertuig : voertuigen) {
                berekenSnelheid(voertuig);
                berekenVersnelling(voertuig);
                geldig(voertuig);
            }
            verhoogTijd();
            for (auto& verkeerslicht : verkeerslichten)
                verkeerslichtSim(verkeerslicht);
        }
        void simVoertuiggenerator();

    }
    TrafficSim(const std::vector<Baan> &banen, const std::vector<Verkeerslicht> &verkeerslichten,
        const std::vector<Voertuig> &voertuigen, const std::vector<VoertuigGen> &voertuigengen)
        : banen(banen),
          verkeerslichten(verkeerslichten),
          voertuigen(voertuigen),
          voertuigengen(voertuigengen) {
    }
    /**
     * Deze functie berekent de versnelling van het voertuig.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Ilyas Sefiani
     *@author Rares Grama
     *@date /
     *@version
     */
    void berekenVersnelling(Voertuig& voertuig) {
        int indexLijst = voertuig.voertuigNummer - 1;
        if (indexLijst > 0) {
            int indexVoertuig2 = indexLijst - 1;
            Voertuig voertuig2 = voertuigen[indexVoertuig2];
            double volgafstand = voertuig2.positie - voertuig.positie - voertuig2.lengte;
            double snelheidsverschil = voertuig.snelheid - voertuig2.snelheid;
            double delta = (voertuig.fmin + std::max(0.0, voertuig.snelheid + ( (voertuig.snelheid * snelheidsverschil) / (2 * std::sqrt(voertuig.maxversnelling * voertuig.maxremfactor)))))/ volgafstand;
            double versnelling = voertuig.maxversnelling*(1-pow(voertuig.snelheid/voertuig.maxsnelheid,4) - pow(delta,2));
            voertuig.versnelling = versnelling;
        }
        else {
            double delta = 0;
            double versnelling = voertuig.maxversnelling*(1-pow(voertuig.snelheid/voertuig.maxsnelheid,4) - pow(delta,2));
            voertuig.versnelling = versnelling;
        }
    }
    /**
     * Deze functie berekent de snelheid van het voertuig.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Ilyas Sefiani
     *@author Rares Grama
     *@date /
     *@version
     */
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
    /**
     * Deze functie berekent hoe het voertuig kan versnellen.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Rares Grama
     *@date /
     *@version
     */
    void versnellen(Voertuig& voertuig){
        int indexLijst = voertuig.voertuigNummer - 1;
        if (indexLijst == 0) {
            size_t indexVoertuig2 = indexLijst - 1;
            if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
                Voertuig& voertuig2 = voertuigen[indexVoertuig2];
                voertuig.maxsnelheid = voertuig2.mMaxsnelheid;
            }
        }
    }
    /**
     * Deze functie berekent hoe het voertuig kan vertragen.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Rares Grama
     *@date /
     *@version
     */
    void vertragen(Voertuig& voertuig){
        double s=voertuig.vertraagfactor;
        int indexLijst = voertuig.voertuigNummer - 1;
        if (indexLijst==0) {
            voertuig.maxsnelheid=s*voertuig.mMaxsnelheid;
        }
    }
    /**
     * Deze functie berekent hoe het voertuig kan stoppen.
     * @param voertuig is het voertuig.
     */
    /**
     *@author Rares Grama
     *@author
     *@date /
     *@version
     */
    void stoppen(Voertuig& voertuig) {
        int indexLijst = voertuig.voertuigNummer - 1;

        if (indexLijst == 0) {
            voertuig.versnelling = - (voertuig.maxremfactor*voertuig.snelheid) / voertuig.maxsnelheid;
        } else {
            size_t indexVoertuig2 = indexLijst - 1;
            if (indexVoertuig2 >= 0 && indexVoertuig2 < voertuigen.size()) {
                Voertuig& voertuig2 = voertuigen[indexVoertuig2];
                voertuig.versnelling = voertuig2.versnelling;
            }
        }
    }
    /**
     * Deze functie bekijkt of het voertuig in zijn baan mag blijven..
     * @param voertuig is het voertuig.
     */
    /**
     *@author Ilyas Sefiani
     *@author Jonas Saelens
     *@date /
     *@version
     */
    void geldig(Voertuig& voertuig) {
        int indexLijst = voertuig.voertuigNummer - 1;

        std::string baannaam = voertuig.baan;
        int lengte = getBaanLengte(baannaam, banen);
        if (lengte < 0) {
            std::cout << "Bestaat niet." << std::endl;
        }
        else if (voertuig.positie > lengte) {
            if (voertuigen.size() > 1){
                Voertuig& voertuig2 = voertuigen[indexLijst + 1];
                voertuig2.voertuigNummer = voertuig.voertuigNummer;
            }
            voertuigen.erase(voertuigen.begin()+indexLijst);
            std::cout << "Voertuig weg van de baan" << std::endl;
        }
        else {
            std::cout << "er gebeurt niks" << std::endl;
        }
    }
    /**
     * Deze functie zorgt ervoor wat de auto's doen op basis van de cyclus van het verkeerslicht..
     * @param verkeerslicht is het voertuig.
     */
    /**
     *@author Rares Grama
     *@author Ilyas Sefiani
     *@date /
     *@version
     */
    void verkeerslichtSim(Verkeerslicht verkeerslicht) {
        if (time>verkeerslicht.cyclus) {
            if (verkeerslicht.kleur==verkeerslicht.rood) {
                verkeerslicht.kleur=verkeerslicht.groen;
                if (verkeerslicht.kleur==verkeerslicht.groen) {
                    for (auto& voertuig : voertuigen) {
                        versnellen( voertuig);
                    }
                }
            }
            if (verkeerslicht.kleur==verkeerslicht.groen) {
                verkeerslicht.kleur=verkeerslicht.rood;
                if (verkeerslicht.kleur==verkeerslicht.rood) {
                    if (voertuigen[0].positie<=voertuigen[0].vertraagafstand ) {
                        vertragen(voertuigen[0]);
                    } else if (voertuigen[0].positie<=voertuigen[0].vertraagafstand/2) {
                        stoppen(voertuigen[0]);

                    }
                }
            }
        }
    }
    /**
     * Deze functie genereert voertuigen.
     */
    /**
     *@author Rares Grama
     *@date /
     *@version
     */
    void simVoertuiggenerator(){
        for (auto& generator : voertuigengen) {
            if (time  > generator.freq) {
                // bool vrij = true;
                for (const auto& voertuig : voertuigen) {
                    if (voertuig.baan == generator.baan && voertuig.positie <= 2 * voertuig.lengte) {
                        // vrij = false;
                        break;
                    }
                    Voertuig nieuwVoertuig;
                    nieuwVoertuig.baan = generator.baan;
                    nieuwVoertuig.positie = 0;
                    voertuigen.push_back(nieuwVoertuig);
                    std::cout << "Nieuw voertuig toegevoegd op baan " << generator.baan << std::endl;

                }
            }
    }
}
    std::vector<Baan> get_banen() const {
        return banen;
    }

    void setBanen(const std::vector<Baan> &banen) {
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
    int getBaanLengte(std::string & baannaam, std:: vector<Baan>&banen) {
        for (Baan& b : banen) {
            if (b.naam == baannaam) {
                return b.lengte;
            }
        }
        return 0;
    }
    /**
     * Deze functie verhoogt de tijd.
     */
    /**
    *@author Ilyas Sefiani
    *@date /
    *@version
    */
    void verhoogTijd() {
        double oldTime = this->time;
        double add = 0.0166;
        setTime(this->time+add);
        std::cout << "tijd verhoogd: " << oldTime << "->" << this->time << std::endl;
    }

    void setTime(double time) {
        this->time = time;
    }

    std::vector<Verkeerslicht> getVerkeerslichten() const {
        return verkeerslichten;
    }

    void setVerkeerslichten(const std::vector<Verkeerslicht> &verkeerslichten) {
        this->verkeerslichten = verkeerslichten;
    }

    void voegverkeerslichttoe(Verkeerslicht licht) {
        this->verkeerslichten.push_back(licht);
    }

    std::vector<Voertuig>& getVoertuigen() {
        return voertuigen;
    }

    void setVoertuigen(const std::vector<Voertuig> &voertuigen) {
        this->voertuigen = voertuigen;
    }

    void voegvoertuigtoe(Voertuig voertuig) {
        this->voertuigen.push_back(voertuig);
    }
    /**
     * Deze functie print uit wat er moet gedaan worden in 2.1
     */
    /**
    *@author Jonas Saelens
    *@date /
    *@version /
    */
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
    double time = 0.0;
};