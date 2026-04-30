#pragma once
#include "InstrumentFinanciar.h"
#include <vector>

class Obligatiune : public InstrumentFinanciar {
    double rataDobanzi;
    int aniiPanaLaScadenta;
public:
    Obligatiune(const std::string& n, double pc, double pInit, int c,
                double rata, int ani);

    double calculeazaProfit() const override;
    double valoare() const override;
    InstrumentFinanciar* clone() const override;

    double getRataDobanzi() const;
    int getAniiPanaLaScadenta() const;
    static std::vector<Obligatiune> getCatalog();

protected:
    std::string tipInstrument() const override;
    void afisareExtra(std::ostream& out) const override;
};
