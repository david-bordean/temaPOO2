#include "InstrumentFinanciar.h"

InstrumentFinanciar::InstrumentFinanciar(const std::string& n, double pc, double pInit, int c)
    : nume(n), pretCurent(pc), pretCumparare(pInit), cantitate(c)
{
    if (pc <= 0)    throw ExceptieValoareInvalida("pretCurent", pc);
    if (pInit <= 0) throw ExceptieValoareInvalida("pretCumparare", pInit);
    if (c < 0)      throw ExceptieValoareInvalida("cantitate", (double)c);
}

void InstrumentFinanciar::afiseaza(std::ostream& out) const {
    out << tipInstrument() << ": " << nume
        << " | Pret curent: " << pretCurent
        << " | Cantitate: " << cantitate
        << " | Profit: " << calculeazaProfit();
    afisareExtra(out);
}

std::string InstrumentFinanciar::getNume() const { return nume; }
int InstrumentFinanciar::getCantitate() const { return cantitate; }
double InstrumentFinanciar::getPretCurent() const { return pretCurent; }
double InstrumentFinanciar::getPretCumparare() const { return pretCumparare; }

void InstrumentFinanciar::setPretCurent(double p) {
    if (p <= 0) throw ExceptieValoareInvalida("pretCurent", p);
    pretCurent = p;
}

void InstrumentFinanciar::modificaCantitate(int c) { cantitate += c; }
void InstrumentFinanciar::actualizeazaPret(double procent) { pretCurent *= procent; }
void InstrumentFinanciar::afisareExtra(std::ostream&) const {}

std::ostream& operator<<(std::ostream& out, const InstrumentFinanciar& i) {
    i.afiseaza(out);
    return out;
}
