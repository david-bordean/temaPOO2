#include "Investitor.h"
#include "Piata.h"
#include "Crypto.h"
#include "Exceptii.h"
#include <iomanip>

void Investitor::elibereaza() {
    for (auto* p : portofoliu) delete p;
    portofoliu.clear();
}

void Investitor::copiazaDin(const Investitor& other) {
    soldLiber = other.soldLiber;
    istoricTranzactii = other.istoricTranzactii;
    for (auto* p : other.portofoliu)
        portofoliu.push_back(p->clone());
}

void Investitor::swap(Investitor& other) noexcept {
    nume.swap(other.nume);
    portofoliu.swap(other.portofoliu);
    istoricTranzactii.swap(other.istoricTranzactii);
    std::swap(soldLiber, other.soldLiber);
}

int Investitor::numarInstrumente() const { return (int)portofoliu.size(); }

void Investitor::stergeInstrument(const std::string& n) {
    for (int i = 0; i < (int)portofoliu.size(); i++) {
        if (portofoliu[i]->getNume() == n) {
            delete portofoliu[i];
            portofoliu.erase(portofoliu.begin() + i);
            return;
        }
    }
    throw ExceptieInstrumentNegasit(n);
}

Investitor::Investitor(const std::string& n, double soldInitial)
    : nume(n), soldLiber(soldInitial) {}

Investitor::Investitor(const Investitor& other) : nume(other.nume), soldLiber(0) {
    copiazaDin(other);
}

Investitor& Investitor::operator=(Investitor other) {
    swap(other);
    return *this;
}

Investitor::~Investitor() { elibereaza(); }

void Investitor::adaugaInstrument(const InstrumentFinanciar& instr) {
    portofoliu.push_back(instr.clone());
}

Investitor& Investitor::operator+=(const InstrumentFinanciar& instr) {
    adaugaInstrument(instr);
    return *this;
}

void Investitor::cumpara(const InstrumentFinanciar& instr, int cantitate) {
    if (cantitate <= 0)
        throw ExceptieValoareInvalida("cantitate", (double)cantitate);
    double cost = instr.getPretCurent() * cantitate;
    if (cost > soldLiber)
        throw ExceptieFonduriInsuficiente(soldLiber, cost);

    for (auto* p : portofoliu) {
        if (p->getNume() == instr.getNume()) {
            p->modificaCantitate(cantitate);
            soldLiber -= cost;
            istoricTranzactii.emplace_back(instr.getNume(), "cumparare", cantitate, instr.getPretCurent());
            return;
        }
    }

    InstrumentFinanciar* nou = instr.clone();
    nou->modificaCantitate(cantitate);
    portofoliu.push_back(nou);
    soldLiber -= cost;
    istoricTranzactii.emplace_back(instr.getNume(), "cumparare", cantitate, instr.getPretCurent());
}

void Investitor::vinde(const std::string& numeInstr, int cantitate) {
    if (cantitate <= 0)
        throw ExceptieValoareInvalida("cantitate", (double)cantitate);
    for (int i = 0; i < (int)portofoliu.size(); i++) {
        if (portofoliu[i]->getNume() == numeInstr) {
            if (portofoliu[i]->getCantitate() < cantitate)
                throw ExceptieCantitateInsuficienta(
                    numeInstr, portofoliu[i]->getCantitate(), cantitate);
            double incasari = portofoliu[i]->getPretCurent() * cantitate;
            portofoliu[i]->modificaCantitate(-cantitate);
            soldLiber += incasari;
            istoricTranzactii.emplace_back(numeInstr, "vanzare", cantitate, incasari / cantitate);
            if (portofoliu[i]->getCantitate() == 0) {
                delete portofoliu[i];
                portofoliu.erase(portofoliu.begin() + i);
                std::cout << "[Portofoliu] Instrumentul '" << numeInstr
                          << "' eliminat automat (cantitate 0).\n";
            }
            return;
        }
    }
    throw ExceptieInstrumentNegasit(numeInstr);
}

void Investitor::executaTranzactie(const Tranzactie& t) {
    for (int i = 0; i < (int)portofoliu.size(); i++) {
        if (portofoliu[i]->getNume() == t.getNume()) {
            if (t.getTip() == "cumparare") {
                portofoliu[i]->modificaCantitate(t.getCantitate());
                soldLiber -= t.getPret() * t.getCantitate();
            } else if (t.getTip() == "vanzare") {
                if (portofoliu[i]->getCantitate() < t.getCantitate())
                    throw ExceptieCantitateInsuficienta(
                        t.getNume(), portofoliu[i]->getCantitate(), t.getCantitate());
                portofoliu[i]->modificaCantitate(-t.getCantitate());
                soldLiber += t.getPret() * t.getCantitate();
                if (portofoliu[i]->getCantitate() == 0) {
                    delete portofoliu[i];
                    portofoliu.erase(portofoliu.begin() + i);
                    std::cout << "[Portofoliu] Instrumentul '" << t.getNume()
                              << "' eliminat automat (cantitate 0).\n";
                }
            } else {
                throw ExceptiePortofoliu("Tip tranzactie necunoscut: " + t.getTip());
            }
            return;
        }
    }
    throw ExceptieInstrumentNegasit(t.getNume());
}

void Investitor::cautaInstrument(const std::string& n) const {
    for (auto* p : portofoliu) {
        if (p->getNume() == n) {
            p->afiseaza(std::cout);
            std::cout << "\n";
            return;
        }
    }
    throw ExceptieInstrumentNegasit(n);
}

double Investitor::valoareTotala() const {
    double suma = 0;
    for (auto* p : portofoliu) suma += p->valoare();
    return suma;
}

double Investitor::profitTotal() const {
    double suma = 0;
    for (auto* p : portofoliu) suma += p->calculeazaProfit();
    return suma;
}

double Investitor::getSoldLiber() const { return soldLiber; }

double Investitor::getBalantaTotala() const {
    return soldLiber + valoareTotala();
}

void Investitor::setSoldLiber(double s) { soldLiber = s; }

void Investitor::adaugaFonduri(double suma) {
    if (suma <= 0)
        throw ExceptieValoareInvalida("suma", suma);
    soldLiber += suma;
}

void Investitor::retrageFonduri(double suma) {
    if (suma <= 0)
        throw ExceptieValoareInvalida("suma", suma);
    if (suma > soldLiber)
        throw ExceptieFonduriInsuficiente(soldLiber, suma);
    soldLiber -= suma;
}

void Investitor::afiseazaIstoricTranzactii() const {
    if (istoricTranzactii.empty()) {
        std::cout << "Nicio tranzactie efectuata.\n";
        return;
    }
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& t : istoricTranzactii)
        std::cout << t << "\n";
}

void Investitor::actualizeazaPreturiPortofoliu(const Piata& piata) {
    for (auto* p : portofoliu) {
        double pretNou = piata.getPret(p->getNume());
        if (pretNou > 0)
            p->setPretCurent(pretNou);
    }
}

void Investitor::afiseazaCrypto() const {
    bool gasit = false;
    for (auto* p : portofoliu) {
        Crypto* cr = dynamic_cast<Crypto*>(p);
        if (cr) {
            cr->afiseaza(std::cout);
            std::cout << "\n";
            gasit = true;
        }
    }
    if (!gasit) std::cout << "Niciun activ Crypto in portofoliu.\n";
}

bool Investitor::areInstrument(const std::string& n) const {
    for (auto* p : portofoliu)
        if (p->getNume() == n) return true;
    return false;
}

int Investitor::getCantitateInstrument(const std::string& n) const {
    for (auto* p : portofoliu)
        if (p->getNume() == n) return p->getCantitate();
    return 0;
}

std::string Investitor::getNume() const { return nume; }
void Investitor::setNume(const std::string& n) { nume = n; }

std::ostream& operator<<(std::ostream& out, const Investitor& inv) {
    out << std::fixed << std::setprecision(2);
    out << "Investitor: " << inv.nume
        << " | Instrumente: " << inv.numarInstrumente() << "\n";
    out << "Sold liber: " << inv.soldLiber
        << " RON | Balanta totala: " << inv.getBalantaTotala() << " RON\n";
    if (inv.portofoliu.empty()) {
        out << "  (portofoliu gol)\n";
    } else {
        for (auto* p : inv.portofoliu)
            out << "  " << *p << "\n";
    }
    return out;
}
