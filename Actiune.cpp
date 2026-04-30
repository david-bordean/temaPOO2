#include "Actiune.h"
#include <fstream>
#include <sstream>

int Actiune::numarActiuniCreate = 0;

std::vector<Actiune> Actiune::getCatalog() {
    std::vector<Actiune> catalog;
    std::ifstream f("actiuni.in");
    if (!f.is_open()) {
        std::cerr << "[Avertisment] Fisierul actiuni.in nu a fost gasit.\n";
        return catalog;
    }
    std::string linie;
    while (std::getline(f, linie)) {
        if (!linie.empty() && linie.back() == '\r') linie.pop_back();
        if (linie.empty() || linie[0] == '#') continue;
        std::istringstream ss(linie);
        std::string nume;
        double pret;
        if (ss >> nume >> pret)
            catalog.emplace_back(nume, pret, pret, 0);
    }
    return catalog;
}

Actiune::Actiune(const std::string& n, double pc, double pInit, int c)
    : InstrumentFinanciar(n, pc, pInit, c)
{
    numarActiuniCreate++;
}

double Actiune::calculeazaProfit() const {
    return (pretCurent - pretCumparare) * cantitate;
}

double Actiune::valoare() const {
    return pretCurent * cantitate;
}

InstrumentFinanciar* Actiune::clone() const {
    return new Actiune(*this);
}

int Actiune::getNrActiuniCreate() { return numarActiuniCreate; }

std::string Actiune::tipInstrument() const { return "Actiune"; }

void Actiune::afisareExtra(std::ostream& out) const {
    out << " | Pret cumparare: " << pretCumparare
        << " | In profit: " << (calculeazaProfit() > 0 ? "DA" : "NU");
}
