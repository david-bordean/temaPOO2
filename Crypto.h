#pragma once
#include "InstrumentFinanciar.h"
#include <vector>

class Crypto : public InstrumentFinanciar {
    std::string simbol;
    static int numarCryptoCreate;
public:
    Crypto(const std::string& n, const std::string& sim,
           double pc, double pInit, int c);

    double calculeazaProfit() const override;
    double valoare()          const override;
    InstrumentFinanciar* clone() const override;

    std::string getSimbol() const;
    static int getNrCryptoCreate();
    static std::vector<Crypto> getCatalog();

protected:
    std::string tipInstrument() const override;
    void afisareExtra(std::ostream& out) const override;
};
