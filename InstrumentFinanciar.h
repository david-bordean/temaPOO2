#pragma once
#include <string>
#include <iostream>
#include "Exceptii.h"

class InstrumentFinanciar {
protected:
    std::string nume;
    double pretCurent;
    double pretCumparare;
    int cantitate;

    InstrumentFinanciar(const std::string& n, double pc, double pInit, int c);

public:
    virtual ~InstrumentFinanciar() = default;

    virtual double calculeazaProfit() const = 0;
    virtual double valoare() const = 0;
    virtual InstrumentFinanciar* clone() const = 0;

    void afiseaza(std::ostream& out) const;

    std::string getNume() const;
    int getCantitate() const;
    double getPretCurent() const;
    double getPretCumparare() const;
    void setPretCurent(double p);
    void modificaCantitate(int c);
    void actualizeazaPret(double procent);

    friend std::ostream& operator<<(std::ostream& out, const InstrumentFinanciar& i);

protected:
    virtual std::string tipInstrument() const = 0;
    virtual void afisareExtra(std::ostream& out) const;
};
