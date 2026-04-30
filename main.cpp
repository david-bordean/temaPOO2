#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <ctime>
#include "Exceptii.h"
#include "Piata.h"
#include "Investitor.h"

static int citesteInt(const std::string& prompt = "") {
    int val;
    while (true) {
        if (!prompt.empty()) std::cout << prompt;
        std::cin >> val;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valoare invalida, incearca din nou: ";
        } else {
            std::cin.ignore();
            return val;
        }
    }
}

static double citesteDouble(const std::string& prompt = "") {
    double val;
    while (true) {
        if (!prompt.empty()) std::cout << prompt;
        std::cin >> val;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Valoare invalida, incearca din nou: ";
        } else {
            std::cin.ignore();
            return val;
        }
    }
}

// ============================================================
//  MENIU PIATA PUBLICA
// ============================================================

static void meniuPiataPublica(Piata& piata) {
    int optiune = -1;
    while (optiune != 0) {
        std::cout << "\n=== PIATA FINANCIARA ===\n";
        std::cout << "1. Toata piata\n";
        std::cout << "2. Doar actiuni\n";
        std::cout << "3. Doar crypto\n";
        std::cout << "4. Doar obligatiuni\n";
        std::cout << "5. Cauta instrument\n";
        std::cout << "0. Inapoi\n";
        std::cout << "Alegere: ";
        optiune = citesteInt();

        if (optiune == 1) {
            std::cout << piata;
        } else if (optiune == 2) {
            piata.afiseazaActiuni(std::cout);
        } else if (optiune == 3) {
            piata.afiseazaCrypto(std::cout);
        } else if (optiune == 4) {
            piata.afiseazaObligatiuni(std::cout);
        } else if (optiune == 5) {
            std::string n;
            std::cout << "Nume instrument cautat: ";
            std::getline(std::cin, n);
            piata.cauta(n);
        } else if (optiune != 0) {
            std::cout << "Optiune invalida.\n";
        }
    }
}

// ============================================================
//  MENIU PORTOFOLIU
// ============================================================

static void afiseazaMeniuPortofoliu(const Investitor& inv) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\n======= PORTOFOLIU: " << inv.getNume() << " =======\n";
    std::cout << "Sold liber:     " << inv.getSoldLiber()     << " RON\n";
    std::cout << "Balanta totala: " << inv.getBalantaTotala() << " RON\n";
    std::cout << "1. Vizualizeaza portofoliu\n";
    std::cout << "2. Vizualizeaza doar crypto din portofoliu\n";
    std::cout << "3. Cauta instrument in portofoliu\n";
    std::cout << "4. Cauta instrument in piata\n";
    std::cout << "5. Cumpara instrument\n";
    std::cout << "6. Vinde instrument\n";
    std::cout << "7. Adauga fonduri\n";
    std::cout << "8. Retrage fonduri\n";
    std::cout << "9. Istoric tranzactii\n";
    std::cout << "0. Deconecteaza-te\n";
    std::cout << "Alegere: ";
}

static void meniuPortofoliu(Investitor& inv, Piata& piata) {
    int optiune = -1;

    while (optiune != 0) {
        afiseazaMeniuPortofoliu(inv);
        optiune = citesteInt();

        try {
            if (optiune == 1) {
                std::cout << "\n" << inv;

            } else if (optiune == 2) {
                inv.afiseazaCrypto();

            } else if (optiune == 3) {
                std::string n;
                std::cout << "Nume instrument: ";
                std::getline(std::cin, n);
                inv.cautaInstrument(n);

            } else if (optiune == 4) {
                std::string n;
                std::cout << "Nume instrument cautat: ";
                std::getline(std::cin, n);
                piata.cauta(n);

            } else if (optiune == 5) {
                piata.afiseazaCatalogNumerot();
                int nr = citesteInt("Alegere: ");
                if (nr == 0) continue;
                if (nr < 1 || nr > piata.numarInstrumente()) {
                    std::cout << "Optiune invalida.\n";
                    continue;
                }
                int cant = citesteInt("Cantitate: ");
                const InstrumentFinanciar& instr = piata.getInstrument(nr);
                inv.cumpara(instr, cant);
                std::cout << std::fixed << std::setprecision(2);
                std::cout << "Cumparare efectuata. Cost: "
                          << instr.getPretCurent() * cant << " RON.\n";

            } else if (optiune == 6) {
                std::cout << "\n" << inv;
                std::string n;
                std::cout << "Nume instrument de vandut: ";
                std::getline(std::cin, n);
                int cant = citesteInt("Cantitate: ");
                inv.vinde(n, cant);
                std::cout << "Vanzare efectuata.\n";

            } else if (optiune == 7) {
                double suma = citesteDouble("Suma de adaugat (RON): ");
                inv.adaugaFonduri(suma);
                std::cout << std::fixed << std::setprecision(2);
                std::cout << "Fonduri adaugate. Sold liber: "
                          << inv.getSoldLiber() << " RON.\n";

            } else if (optiune == 8) {
                double suma = citesteDouble("Suma de retras (RON): ");
                inv.retrageFonduri(suma);
                std::cout << std::fixed << std::setprecision(2);
                std::cout << "Fonduri retrase. Sold liber: "
                          << inv.getSoldLiber() << " RON.\n";

            } else if (optiune == 9) {
                inv.afiseazaIstoricTranzactii();

            } else if (optiune != 0) {
                std::cout << "Optiune invalida.\n";
            }

        } catch (const ExceptieFonduriInsuficiente& e) {
            std::cout << "[Eroare fonduri]   " << e.what() << "\n";
        } catch (const ExceptieCantitateInsuficienta& e) {
            std::cout << "[Eroare cantitate] " << e.what() << "\n";
        } catch (const ExceptieInstrumentNegasit& e) {
            std::cout << "[Eroare cautare]   " << e.what() << "\n";
        } catch (const ExceptieValoareInvalida& e) {
            std::cout << "[Eroare valoare]   " << e.what() << "\n";
        } catch (const ExceptiePortofoliu& e) {
            std::cout << "[Eroare]           " << e.what() << "\n";
        }
    }

    std::cout << "Deconectat din contul '" << inv.getNume() << "'.\n";
}

// ============================================================
//  MENIU PRINCIPAL
// ============================================================

static void afiseazaMeniuPrincipal() {
    std::cout << "\n========== SISTEM INVESTITII ==========\n";
    std::cout << "1. Creeaza cont nou\n";
    std::cout << "2. Conecteaza-te la cont existent\n";
    std::cout << "3. Vizualizeaza piata (fara cont)\n";
    std::cout << "4. Trece o zi (actualizeaza preturi)\n";
    std::cout << "0. Iesire\n";
    std::cout << "Alegere: ";
}

// ============================================================
//  MAIN
// ============================================================

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    std::vector<Investitor> investitori;
    Piata piata;
    int optiune = -1;

    std::cout << "=== Bun venit in aplicatia de investitii! ===\n";

    while (optiune != 0) {
        afiseazaMeniuPrincipal();
        optiune = citesteInt();

        if (optiune == 1) {
            std::string nume;
            std::cout << "Nume utilizator: ";
            std::getline(std::cin, nume);

            bool exista = false;
            for (auto& inv : investitori)
                if (inv.getNume() == nume) { exista = true; break; }

            if (exista) {
                std::cout << "Exista deja un cont cu acest nume. Conectare automata...\n";
                for (auto& inv : investitori) {
                    if (inv.getNume() == nume) {
                        meniuPortofoliu(inv, piata);
                        break;
                    }
                }
            } else {
                double soldInitial = citesteDouble("Sold initial (RON): ");
                if (soldInitial < 0) soldInitial = 0;
                investitori.emplace_back(nume, soldInitial);
                std::cout << "Cont creat cu succes pentru '" << nume << "'!\n";
                meniuPortofoliu(investitori.back(), piata);
            }

        } else if (optiune == 2) {
            std::string nume;
            std::cout << "Nume utilizator: ";
            std::getline(std::cin, nume);

            Investitor* inv = nullptr;
            for (auto& i : investitori)
                if (i.getNume() == nume) { inv = &i; break; }

            if (!inv) {
                std::cout << "Contul '" << nume << "' nu a fost gasit.\n";
            } else {
                meniuPortofoliu(*inv, piata);
            }

        } else if (optiune == 3) {
            meniuPiataPublica(piata);

        } else if (optiune == 4) {
            piata.actualizeazaPreturi();
            for (auto& inv : investitori)
                inv.actualizeazaPreturiPortofoliu(piata);

        } else if (optiune != 0) {
            std::cout << "Optiune invalida.\n";
        }
    }

    std::cout << "La revedere!\n";
    return 0;
}
