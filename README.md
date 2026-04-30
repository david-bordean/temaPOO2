# temaPOO2
# Sistem de Gestionare a Portofoliului de Investiții

Aplicație C++ care simulează gestionarea unui portofoliu de investiții financiare. Utilizatorii pot cumpăra și vinde instrumente financiare (acțiuni, criptomonede, obligațiuni), pot urmări profitul și valoarea portofoliului și pot vizualiza evoluția prețurilor pe piață. Aplicația suportă mai mulți investitori simultan, fiecare cu propriul portofoliu și sold disponibil.

---

## Clase

### `InstrumentFinanciar`
Clasă abstractă de bază pentru toate instrumentele financiare.

**Atribute:** `nume`, `pretCurent`, `pretCumparare`, `cantitate`

**Metode:**
- `calculeazaProfit()` — calcul profit curent *(pur virtual)*
- `valoare()` — calcul valoare totală deținută *(pur virtual)*
- `clone()` — copiere polimorfică *(pur virtual)*
- `afiseaza()` — afișează detaliile instrumentului
- `getNume()`, `getCantitate()`, `getPretCurent()`, `getPretCumparare()` — getteri
- `setPretCurent()` — setează prețul curent (cu validare)
- `modificaCantitate()` — adaugă/scade din cantitatea deținută
- `actualizeazaPret()` — înmulțește prețul curent cu un factor procentual
- `operator<<` — afișare prin stream

---

### `Actiune`
Reprezintă o acțiune la bursă. Derivată din `InstrumentFinanciar`.

**Atribute:** `numarActiuniCreate` *(static)*

**Metode:**
- `calculeazaProfit()` — `(pretCurent - pretCumparare) * cantitate`
- `valoare()` — `pretCurent * cantitate`
- `clone()` — returnează o copie alocată dinamic
- `getNrActiuniCreate()` *(static)* — numărul total de acțiuni instanțiate
- `getCatalog()` *(static)* — încarcă acțiunile din `actiuni.in`

---

### `Crypto`
Reprezintă o criptomonedă. Derivată din `InstrumentFinanciar`.

**Atribute:** `simbol`, `numarCryptoCreate` *(static)*

**Metode:**
- `calculeazaProfit()` — `(pretCurent - pretCumparare) * cantitate`
- `valoare()` — `pretCurent * cantitate`
- `clone()` — returnează o copie alocată dinamic
- `getSimbol()` — returnează simbolul criptomonedei (ex: BTC, ETH)
- `getNrCryptoCreate()` *(static)* — numărul total de crypto instanțiate
- `getCatalog()` *(static)* — încarcă criptomonedele din `crypto.in`

---

### `Obligatiune`
Reprezintă o obligațiune cu rată de dobândă fixă și scadență. Derivată din `InstrumentFinanciar`.

**Atribute:** `rataDobanzi`, `aniiPanaLaScadenta`

**Metode:**
- `calculeazaProfit()` — dobânzi totale + diferența de preț față de cumpărare
- `valoare()` — `pretCurent * cantitate`
- `clone()` — returnează o copie alocată dinamic
- `getRataDobanzi()` — returnează rata dobânzii
- `getAniiPanaLaScadenta()` — returnează numărul de ani până la scadență
- `getCatalog()` *(static)* — încarcă obligațiunile din `obligatiuni.in`

---

### `Tranzactie`
Modelează o tranzacție de cumpărare sau vânzare. Câmpul `tip` este stocat ca `char*` cu gestionare manuală a memoriei.

**Atribute:** `numeInstrument`, `tip` *(char\*)*, `cantitate`, `pret`

**Metode:**
- `getNume()`, `getTip()`, `getCantitate()`, `getPret()` — getteri
- `setCantitate()` — modifică cantitatea tranzacției
- `operator<<` — afișare prin stream
- Constructor de copiere, `operator=`, destructor *(regula celor 3)*

---

### `Investitor`
Reprezintă un utilizator cu propriul portofoliu de instrumente financiare.

**Atribute:** `nume`, `portofoliu` *(vector\<InstrumentFinanciar\*\>)*, `istoricTranzactii`, `soldLiber`

**Metode:**
- `cumpara(instr, cantitate)` — cumpără un instrument dacă există fonduri suficiente
- `vinde(numeInstr, cantitate)` — vinde din portofoliu; elimină automat instrumentul la cantitate 0
- `executaTranzactie(t)` — execută o tranzacție de tip `Tranzactie`
- `adaugaInstrument(instr)` — adaugă direct un instrument în portofoliu
- `operator+=` — sintaxă alternativă pentru `adaugaInstrument`
- `cautaInstrument(n)` — caută și afișează un instrument din portofoliu
- `valoareTotala()` — suma valorilor tuturor instrumentelor deținute
- `profitTotal()` — suma profiturilor tuturor instrumentelor deținute
- `getSoldLiber()`, `setSoldLiber()` — acces la soldul cash
- `getBalantaTotala()` — sold liber + valoare totală portofoliu
- `adaugaFonduri(suma)` / `retrageFonduri(suma)` — gestiunea soldului
- `afiseazaCrypto()` — listează doar activele crypto din portofoliu
- `afiseazaIstoricTranzactii()` — afișează toate tranzacțiile efectuate
- `actualizeazaPreturiPortofoliu(piata)` — sincronizează prețurile cu piața
- `areInstrument(n)` — verifică dacă un instrument se află în portofoliu
- `getCantitateInstrument(n)` — returnează cantitatea deținută dintr-un instrument
- `getNume()`, `setNume()` — acces la numele investitorului
- `operator<<` — afișare prin stream
- Constructor de copiere, `operator=`, destructor *(regula celor 3)*

---

### `Piata`
Catalogul central cu toate instrumentele disponibile pentru tranzacționare. La inițializare încarcă datele din fișierele `.in`.

**Atribute:** `actiuni` *(vector\<Actiune\>)*, `cryptos` *(vector\<Crypto\>)*, `obligatiuni` *(vector\<Obligatiune\>)*

**Metode:**
- `actualizeazaPreturi()` — modifică aleatoriu prețurile tuturor instrumentelor (factor între 0.90 și 1.10)
- `getPret(n)` — returnează prețul curent al unui instrument după nume
- `cauta(n)` — afișează detaliile unui instrument după nume
- `afiseazaCatalogNumerot()` — afișează lista numerotată pentru selecție la cumpărare
- `afiseazaActiuni()` / `afiseazaCrypto()` / `afiseazaObligatiuni()` — listare pe categorii
- `getInstrument(idx)` — returnează instrumentul de la indexul dat
- `numarInstrumente()` — numărul total de instrumente disponibile
- `operator<<` — afișare prin stream

---

### `Exceptii`
Ierarhie de excepții custom derivate din `std::exception`.

- `ExceptiePortofoliu` — clasă de bază pentru toate excepțiile aplicației
- `ExceptieValoareInvalida` — preț negativ/zero, cantitate sau sumă invalidă
- `ExceptieCantitateInsuficienta` — vânzare mai mult decât cantitatea deținută
- `ExceptieInstrumentNegasit` — instrumentul nu există în portofoliu
- `ExceptieFonduriInsuficiente` — soldul disponibil nu acoperă costul cumpărării
