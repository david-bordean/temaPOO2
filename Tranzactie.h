#pragma once
#include <string>
#include <iostream>

class Tranzactie {
    std::string numeInstrument;
    char* tip;
    int cantitate;
    double pret;

    void copiazaTip(const char* t);
    void swap(Tranzactie& other) noexcept;

public:
    Tranzactie(const std::string& n, const char* t, int c, double p);
    Tranzactie(const Tranzactie& other);
    Tranzactie& operator=(Tranzactie other);
    ~Tranzactie();

    std::string getNume() const;
    std::string getTip() const;
    int getCantitate() const;
    double getPret() const;
    void setCantitate(int c);

    friend std::ostream& operator<<(std::ostream& out, const Tranzactie& t);
};
