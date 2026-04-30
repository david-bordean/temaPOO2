#pragma once
#include <string>
#include <stdexcept>

class ExceptiePortofoliu : public std::exception {
protected:
    std::string mesaj;
public:
    explicit ExceptiePortofoliu(const std::string& m) : mesaj(m) {}
    const char* what() const noexcept override { return mesaj.c_str(); }
};

class ExceptieValoareInvalida : public ExceptiePortofoliu {
public:
    ExceptieValoareInvalida(const std::string& camp, double val)
        : ExceptiePortofoliu("Valoare invalida pentru " + camp +
                             ": " + std::to_string(val)) {}
};

class ExceptieCantitateInsuficienta : public ExceptiePortofoliu {
public:
    ExceptieCantitateInsuficienta(const std::string& numeInstrument, int disponibil, int cerut)
        : ExceptiePortofoliu("Cantitate insuficienta pentru " + numeInstrument +
                             ": disponibil " + std::to_string(disponibil) +
                             ", cerut " + std::to_string(cerut)) {}
};

class ExceptieInstrumentNegasit : public ExceptiePortofoliu {
public:
    explicit ExceptieInstrumentNegasit(const std::string& numeInstrument)
        : ExceptiePortofoliu("Instrumentul '" + numeInstrument + "' nu exista in portofoliu.") {}
};

class ExceptieFonduriInsuficiente : public ExceptiePortofoliu {
public:
    ExceptieFonduriInsuficiente(double disponibil, double necesar)
        : ExceptiePortofoliu("Fonduri insuficiente: disponibil " +
                             std::to_string((int)disponibil) + " RON, necesar " +
                             std::to_string((int)necesar) + " RON") {}
};
