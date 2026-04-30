#pragma once
#include <vector>
#include <iostream>
#include "Actiune.h"
#include "Crypto.h"
#include "Obligatiune.h"

class Piata {
    std::vector<Actiune>     actiuni;
    std::vector<Crypto>      cryptos;
    std::vector<Obligatiune> obligatiuni;

public:
    Piata();

    void actualizeazaPreturi();
    double getPret(const std::string& n) const;
    void cauta(const std::string& n) const;
    void afiseazaCatalogNumerot() const;
    void afiseazaActiuni(std::ostream& out) const;
    void afiseazaCrypto(std::ostream& out) const;
    void afiseazaObligatiuni(std::ostream& out) const;
    const InstrumentFinanciar& getInstrument(int idx) const;
    int numarInstrumente() const;

    friend std::ostream& operator<<(std::ostream& out, const Piata& p);
};
