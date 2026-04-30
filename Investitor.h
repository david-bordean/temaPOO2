#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "InstrumentFinanciar.h"
#include "Tranzactie.h"

class Piata;

class Investitor {
    std::string nume;
    std::vector<InstrumentFinanciar*> portofoliu;
    std::vector<Tranzactie> istoricTranzactii;
    double soldLiber;

    void elibereaza();
    void copiazaDin(const Investitor& other);
    void swap(Investitor& other) noexcept;
    int numarInstrumente() const;
    void stergeInstrument(const std::string& n);

public:
    explicit Investitor(const std::string& n, double soldInitial = 10000.0);
    Investitor(const Investitor& other);
    Investitor& operator=(Investitor other);
    ~Investitor();

    void adaugaInstrument(const InstrumentFinanciar& instr);
    Investitor& operator+=(const InstrumentFinanciar& instr);

    void cumpara(const InstrumentFinanciar& instr, int cantitate);
    void vinde(const std::string& numeInstr, int cantitate);
    void executaTranzactie(const Tranzactie& t);

    void cautaInstrument(const std::string& n) const;

    double valoareTotala() const;
    double profitTotal() const;
    double getSoldLiber() const;
    double getBalantaTotala() const;
    void setSoldLiber(double s);
    void adaugaFonduri(double suma);
    void retrageFonduri(double suma);

    void afiseazaCrypto() const;
    void afiseazaIstoricTranzactii() const;
    void actualizeazaPreturiPortofoliu(const Piata& piata);

    bool areInstrument(const std::string& n) const;
    int getCantitateInstrument(const std::string& n) const;

    std::string getNume() const;
    void setNume(const std::string& n);

    friend std::ostream& operator<<(std::ostream& out, const Investitor& inv);
};
