#include "Crypto.h"
#include <fstream>
#include <sstream>

int Crypto::numarCryptoCreate = 0;

Crypto::Crypto(const std::string& n, const std::string& sim,
               double pc, double pInit, int c)
    : InstrumentFinanciar(n, pc, pInit, c), simbol(sim)
{
    numarCryptoCreate++;
}

double Crypto::calculeazaProfit() const {
    return (pretCurent - pretCumparare) * cantitate;
}

double Crypto::valoare() const {
    return pretCurent * cantitate;
}

InstrumentFinanciar* Crypto::clone() const {
    return new Crypto(*this);
}

std::string Crypto::getSimbol() const { return simbol; }
int Crypto::getNrCryptoCreate() { return numarCryptoCreate; }

std::vector<Crypto> Crypto::getCatalog() {
    std::vector<Crypto> catalog;
    std::ifstream f("crypto.in");
    if (!f.is_open()) {
        std::cerr << "[Avertisment] Fisierul crypto.in nu a fost gasit.\n";
        return catalog;
    }
    std::string linie;
    while (std::getline(f, linie)) {
        if (!linie.empty() && linie.back() == '\r') linie.pop_back();
        if (linie.empty() || linie[0] == '#') continue;
        std::istringstream ss(linie);
        std::string nume, simbol;
        double pret;
        if (ss >> nume >> simbol >> pret)
            catalog.emplace_back(nume, simbol, pret, pret, 0);
    }
    return catalog;
}

std::string Crypto::tipInstrument() const { return "Crypto"; }

void Crypto::afisareExtra(std::ostream& out) const {
    out << " | Simbol: " << simbol
        << " | Pret cumparare: " << pretCumparare;
}
