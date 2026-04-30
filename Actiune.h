#pragma once
#include "InstrumentFinanciar.h"
#include <vector>

class Actiune : public InstrumentFinanciar {
    static int numarActiuniCreate;
public:
    Actiune(const std::string& n, double pc, double pInit, int c);

    double calculeazaProfit() const override;
    double valoare() const override;
    InstrumentFinanciar* clone() const override;

    static int getNrActiuniCreate();
    static std::vector<Actiune> getCatalog();

protected:
    std::string tipInstrument() const override;
    void afisareExtra(std::ostream& out) const override;
};
