#include "Obligatiune.h"
#include <fstream>
#include <sstream>

std::vector<Obligatiune> Obligatiune::getCatalog() {
    std::vector<Obligatiune> catalog;
    std::ifstream f("obligatiuni.in");
    if (!f.is_open()) {
        std::cerr << "[Avertisment] Fisierul obligatiuni.in nu a fost gasit.\n";
        return catalog;
    }
    std::string linie;
    while (std::getline(f, linie)) {
        if (!linie.empty() && linie.back() == '\r') linie.pop_back();
        if (linie.empty() || linie[0] == '#') continue;
        std::istringstream ss(linie);
        std::string nume;
        double pret, rata;
        int ani;
        if (ss >> nume >> pret >> rata >> ani)
            catalog.emplace_back(nume, pret, pret, 0, rata, ani);
    }
    return catalog;
}

Obligatiune::Obligatiune(const std::string& n, double pc, double pInit, int c,
                         double rata, int ani)
    : InstrumentFinanciar(n, pc, pInit, c),
      rataDobanzi(rata), aniiPanaLaScadenta(ani)
{
    if (rata < 0)  throw ExceptieValoareInvalida("rataDobanzi", rata);
    if (ani <= 0)  throw ExceptieValoareInvalida("aniiPanaLaScadenta", (double)ani);
}

double Obligatiune::calculeazaProfit() const {
    double dobanziTotale = pretCumparare * (rataDobanzi / 100.0) * aniiPanaLaScadenta * cantitate;
    double diferentaPret = (pretCurent - pretCumparare) * cantitate;
    return dobanziTotale + diferentaPret;
}

double Obligatiune::valoare() const {
    return pretCurent * cantitate;
}

InstrumentFinanciar* Obligatiune::clone() const {
    return new Obligatiune(*this);
}

double Obligatiune::getRataDobanzi() const { return rataDobanzi; }
int Obligatiune::getAniiPanaLaScadenta() const { return aniiPanaLaScadenta; }

std::string Obligatiune::tipInstrument() const { return "Obligatiune"; }

void Obligatiune::afisareExtra(std::ostream& out) const {
    out << " | Rata dobanda: " << rataDobanzi << "% | Scadenta: "
        << aniiPanaLaScadenta << " ani";
}
