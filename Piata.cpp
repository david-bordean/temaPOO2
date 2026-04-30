#include "Piata.h"
#include <cstdlib>
#include <iomanip>

Piata::Piata()
    : actiuni(Actiune::getCatalog()),
      cryptos(Crypto::getCatalog()),
      obligatiuni(Obligatiune::getCatalog())
{}

void Piata::actualizeazaPreturi() {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n--- Actualizare preturi (zi noua) ---\n";
    for (auto& a : actiuni) {
        double procent = 0.90 + (std::rand() % 21) / 100.0;
        double inainte = a.getPretCurent();
        a.actualizeazaPret(procent);
        std::cout << "  " << a.getNume() << ": " << inainte
                  << " -> " << a.getPretCurent() << " RON\n";
    }
    for (auto& c : cryptos) {
        double procent = 0.90 + (std::rand() % 21) / 100.0;
        double inainte = c.getPretCurent();
        c.actualizeazaPret(procent);
        std::cout << "  " << c.getNume() << ": " << inainte
                  << " -> " << c.getPretCurent() << " RON\n";
    }
    for (auto& o : obligatiuni) {
        double procent = 0.90 + (std::rand() % 21) / 100.0;
        double inainte = o.getPretCurent();
        o.actualizeazaPret(procent);
        std::cout << "  " << o.getNume() << ": " << inainte
                  << " -> " << o.getPretCurent() << " RON\n";
    }
}

double Piata::getPret(const std::string& n) const {
    for (const auto& a : actiuni)
        if (a.getNume() == n) return a.getPretCurent();
    for (const auto& c : cryptos)
        if (c.getNume() == n) return c.getPretCurent();
    for (const auto& o : obligatiuni)
        if (o.getNume() == n) return o.getPretCurent();
    return 0.0;
}

void Piata::cauta(const std::string& n) const {
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& a : actiuni) {
        if (a.getNume() == n) {
            std::cout << "Actiune: " << a.getNume()
                      << " | Pret: " << a.getPretCurent() << " RON/actiune\n";
            return;
        }
    }
    for (const auto& c : cryptos) {
        if (c.getNume() == n) {
            std::cout << "Crypto: " << c.getNume()
                      << " (" << c.getSimbol() << ")"
                      << " | Pret: " << c.getPretCurent() << " RON\n";
            return;
        }
    }
    for (const auto& o : obligatiuni) {
        if (o.getNume() == n) {
            std::cout << "Obligatiune: " << o.getNume()
                      << " | Pret: " << o.getPretCurent() << " RON/unitate"
                      << " | Rata: " << o.getRataDobanzi() << "%"
                      << " | Scadenta: " << o.getAniiPanaLaScadenta() << " ani\n";
            return;
        }
    }
    std::cout << "Instrumentul '" << n << "' nu a fost gasit in piata.\n";
}

void Piata::afiseazaCatalogNumerot() const {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n=== INSTRUMENTE DISPONIBILE ===\n";
    int idx = 1;
    std::cout << "--- ACTIUNI ---\n";
    for (const auto& a : actiuni)
        std::cout << "  " << idx++ << ". " << a.getNume()
                  << " - " << a.getPretCurent() << " RON/actiune\n";
    std::cout << "--- CRYPTO ---\n";
    for (const auto& c : cryptos)
        std::cout << "  " << idx++ << ". " << c.getNume()
                  << " (" << c.getSimbol() << ")"
                  << " - " << c.getPretCurent() << " RON\n";
    std::cout << "--- OBLIGATIUNI ---\n";
    for (const auto& o : obligatiuni)
        std::cout << "  " << idx++ << ". " << o.getNume()
                  << " - " << o.getPretCurent() << " RON/unitate"
                  << " (rata: " << o.getRataDobanzi() << "%"
                  << ", " << o.getAniiPanaLaScadenta() << " ani)\n";
    std::cout << "  0. Anulare\n";
}

void Piata::afiseazaActiuni(std::ostream& out) const {
    out << std::fixed << std::setprecision(2);
    out << "\n--- ACTIUNI ---\n";
    for (const auto& a : actiuni)
        out << "  " << a.getNume()
            << " - " << a.getPretCurent() << " RON/actiune\n";
}

void Piata::afiseazaCrypto(std::ostream& out) const {
    out << std::fixed << std::setprecision(2);
    out << "\n--- CRYPTO ---\n";
    for (const auto& c : cryptos)
        out << "  " << c.getNume()
            << " (" << c.getSimbol() << ")"
            << " - " << c.getPretCurent() << " RON\n";
}

void Piata::afiseazaObligatiuni(std::ostream& out) const {
    out << std::fixed << std::setprecision(2);
    out << "\n--- OBLIGATIUNI ---\n";
    for (const auto& o : obligatiuni)
        out << "  " << o.getNume()
            << " - " << o.getPretCurent() << " RON/unitate"
            << " (rata: " << o.getRataDobanzi() << "%"
            << ", " << o.getAniiPanaLaScadenta() << " ani)\n";
}

const InstrumentFinanciar& Piata::getInstrument(int idx) const {
    int i = idx - 1;
    if (i < (int)actiuni.size()) return actiuni[i];
    i -= (int)actiuni.size();
    if (i < (int)cryptos.size()) return cryptos[i];
    i -= (int)cryptos.size();
    return obligatiuni[i];
}

int Piata::numarInstrumente() const {
    return (int)(actiuni.size() + cryptos.size() + obligatiuni.size());
}

std::ostream& operator<<(std::ostream& out, const Piata& p) {
    p.afiseazaActiuni(out);
    p.afiseazaCrypto(out);
    p.afiseazaObligatiuni(out);
    return out;
}
