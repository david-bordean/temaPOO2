#include "Tranzactie.h"
#include <cstring>

void Tranzactie::copiazaTip(const char* t) {
    if (t) {
        tip = new char[strlen(t) + 1];
        strcpy(tip, t);
    } else {
        tip = nullptr;
    }
}

void Tranzactie::swap(Tranzactie& other) noexcept {
    numeInstrument.swap(other.numeInstrument);
    char* tmp = tip; tip = other.tip; other.tip = tmp;
    int   tc  = cantitate; cantitate = other.cantitate; other.cantitate = tc;
    double tp = pret;      pret      = other.pret;      other.pret      = tp;
}

Tranzactie::Tranzactie(const std::string& n, const char* t, int c, double p)
    : numeInstrument(n), tip(nullptr), cantitate(c), pret(p)
{
    copiazaTip(t);
}

Tranzactie::Tranzactie(const Tranzactie& other)
    : numeInstrument(other.numeInstrument), tip(nullptr),
      cantitate(other.cantitate), pret(other.pret)
{
    copiazaTip(other.tip);
}

Tranzactie& Tranzactie::operator=(Tranzactie other) {
    swap(other);
    return *this;
}

Tranzactie::~Tranzactie() { delete[] tip; }

std::string Tranzactie::getNume() const { return numeInstrument; }
std::string Tranzactie::getTip()  const { return tip ? std::string(tip) : ""; }
int    Tranzactie::getCantitate() const { return cantitate; }
double Tranzactie::getPret()      const { return pret; }
void   Tranzactie::setCantitate(int c)  { cantitate = c; }

std::ostream& operator<<(std::ostream& out, const Tranzactie& t) {
    out << "Tranzactie: " << (t.tip ? t.tip : "?")
        << " " << t.cantitate << " unitati " << t.numeInstrument
        << " la pret " << t.pret;
    return out;
}
