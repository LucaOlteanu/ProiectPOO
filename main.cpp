/*
Tema proiectului este Comert, ideea mea de implementare a unui program orientat pe obiecte va fi o comanda online de produse de la un singur magazin. Pentru inceput,
clasele vor fi Produs, Utilizator si Cos/Comanda. Utilizatorul va introduce datele sale personale pentru comanda(nume, adresa si soldul asigurat), iar dupa aceea va putea
incepe sesiunea de cumparare. Acesta va putea vedea la inceput o lista cu toate produsele impreuna cu pretul si disponibilitatea lor. Acesta va putea alege cate un produs
si cantitatea pentru acesta, iar cand este gata va scrie check-out pentru a finaliza comanda.
Ca functii vom avea:
-atunci cand se doreste cumpararea unui produs intr-o cantitate mai mare decat stocul acesta va fi rugat sa aleaga una dintre alternative sau sa renunte la acesta
-la check-out, daca valoarea cosului este mai mare decat soldul va incepe o sesiune de eliminare de produse pana cand se va ajunge la o suma platibila
-doua functii de afisare pentru lista de produse si sumarul comenzii
-functia de adaugare si scoatere din cos
 */
#include <iostream>
#include <cstring>

class Client {
    char *nume;
    char *adresa;
    double sold;
    int id;

public:
    Client(const char *nume_, const char *adresa_, const double sold_, const int id_) : sold{sold_}, id{id_} {
        nume = new char[strlen(nume_) + 1];
        strcpy(nume, nume_);
        adresa = new char[strlen(adresa_) + 1];
        strcpy(adresa, adresa_);
    }

    Client(const Client &other) : sold{other.sold}, id{other.id} {
        nume = new char[strlen(other.nume) + 1];
        strcpy(nume, other.nume);
        adresa = new char[strlen(other.adresa) + 1];
        strcpy(adresa, other.adresa);
    }

    Client &operator=(const Client &other) {
        if (this != &other) {
            delete[] nume;
            delete[] adresa;
            nume = new char[strlen(other.nume) + 1];
            strcpy(nume, other.nume);
            adresa = new char[strlen(other.adresa) + 1];
            strcpy(adresa, other.adresa);
            sold = other.sold;
            id = other.id;
        }
        return *this;
    }

    const char *getNume() const { return nume; }
    const char *getAdresa() const { return adresa; }
    double getSold() const { return sold; }
    int getId() const { return id; }

    friend std::ostream &operator<<(std::ostream &os, const Client &c);

    ~Client() {
        delete[] nume;
        delete[] adresa;
    }
};

std::ostream &operator<<(std::ostream &os, const Client &c) {
    os << c.nume;
    return os;
}

class Produs {
    char *nume;
    double pret;
    int id, stoc;

public:
    Produs(const char *nume_, const double pret_, const int id_, int stoc_) : pret{pret_}, id{id_}, stoc{stoc_} {
        nume = new char[strlen(nume_) + 1];
        strcpy(nume, nume_);
    }

    Produs(const Produs &other) : stoc{other.stoc}, id{other.id}, pret{other.pret} {
        this->nume = new char[strlen(other.nume) + 1];
        strcpy(this->nume, other.nume);
    }

    Produs &operator=(const Produs &other) {
        if (this != &other) {
            delete[] nume;
            nume = new char[strlen(other.nume) + 1];
            strcpy(nume, other.nume);
            pret = other.pret;
            id = other.id;
            stoc = other.stoc;
        }
        return *this;
    }

    void actualizeazaStoc(int numar) {
        stoc -= numar;
        if (stoc < 0) stoc = 0;
    }

    const char *getNume() const { return nume; }
    double getPret() const { return pret; }
    int getStoc() const { return stoc; }
    int getId() const { return id; }

    friend std::ostream &operator<<(std::ostream &os, const Produs &pr);

    ~Produs() {
        delete[] nume;
    }
};

std::ostream &operator<<(std::ostream &os, const Produs &pr) {
    os << pr.id << " " << pr.nume << " " << pr.pret << " lei: " << pr.stoc << " bucati\n";
    return os;
}

class Cos {
    Client proprietar;
    int id_comanda;
    int nrProduse;
    double valoare;
    int nrCatalog = 10;

    struct ItemComanda {
        int idProdus;
        int cantitate;
        double pretUnitar;
    };

    ItemComanda *items;

public:
    Cos(const Client &proprietar_, const int id_comanda_) : proprietar{proprietar_}, id_comanda{id_comanda_},
                                                            nrProduse{0}, valoare{0.0} {
        items = new ItemComanda[10];
    }

    Cos(const Cos &other)
        : proprietar{other.proprietar}, id_comanda{other.id_comanda},
          nrProduse{other.nrProduse}, valoare{other.valoare} {
        items = new ItemComanda[10];
        for (int i = 0; i < nrProduse; ++i)
            items[i] = other.items[i];
    }

    Cos &operator=(const Cos &other) {
        if (this != &other) {
            delete[] items;
            proprietar = other.proprietar;
            id_comanda = other.id_comanda;
            nrProduse = other.nrProduse;
            valoare = other.valoare;

            items = new ItemComanda[10];
            for (int i = 0; i < nrProduse; ++i)
                items[i] = other.items[i];
        }
        return *this;
    }

    int getNrProduse() const { return nrProduse; }

    friend std::ostream &operator<<(std::ostream &os, const Cos &c);

    ~Cos() {
        delete[] items;
    }

    void adaugaProdus(int idProdus, int cantitate, const double pret, Produs **catalog) {
        for (int i = 0; i < nrCatalog; ++i) {
            if (catalog[i]->getId() == idProdus) {
                if (catalog[i]->getStoc() < cantitate) {
                    std::cout << "Stoc insuficient pentru produsul "
                            << catalog[i]->getNume() << " (stoc: "
                            << catalog[i]->getStoc() << ")\n";
                    const int idsim = catalog[i]->getId() / 10;
                    int nrsim=0;
                    for (int j = 0; j < nrCatalog; ++j) {
                        if (catalog[j]->getId() / 10 == idsim && i != j){
                            if (nrsim == 0) {
                                std::cout << "Produse similare: \n"; nrsim++;
                            }
                        std::cout << *catalog[j]<<"\n";
                        }
                    }
                    return;
                }
                break;
            }
        }

        items[nrProduse].idProdus = idProdus;
        items[nrProduse].cantitate = cantitate;
        items[nrProduse].pretUnitar = pret;
        nrProduse++;
        valoare += cantitate * pret;
    }

    void eliminaProdus(int index, int numar = 0) {
        if (index < 0 || index >= nrProduse) {
            std::cout << "Index invalid.\n";
            return;
        }
        if (numar > 0 && numar < items[index].cantitate) {
            valoare -= numar * items[index].pretUnitar;
            items[index].cantitate -= numar;
        } else {
            valoare -= items[index].cantitate * items[index].pretUnitar;
            for (int i = index; i < nrProduse - 1; ++i)
                items[i] = items[i + 1];
            nrProduse--;
        }
    }

    void afiseazaCos() const {
        std::cout << "=== COS DE CUMPARATURI ===\n";
        if (nrProduse == 0) {
            std::cout << "Cosul este gol.\n";
        } else {
            std::cout << "Produse:\n";
            for (int i = 0; i < nrProduse; ++i) {
                std::cout <<"Index: "<< i+1 <<"  - Produs ID: " << items[i].idProdus
                        << ", Cantitate: " << items[i].cantitate
                        << ", Pret unitar: " << items[i].pretUnitar
                        << ", Subtotal: " << items[i].cantitate * items[i].pretUnitar << "\n";
            }
            std::cout << "Total: " << valoare << " lei\n";
        }
        std::cout << "=====================\n";
    }
private:
    void sesiuneEliminare() {
        while (valoare > proprietar.getSold()) {
            std::cout << "\nATENTIE: Cosul depaseste soldul!\n";;

            afiseazaCos();

            std::cout << "Alege indexul produsului de eliminat: ";
            int index;
            std::cin >> index;
            index--;

            if (index < 0 || index >= nrProduse) {
                std::cout << "Index invalid. Incearca din nou.\n";
                continue;
            }

            std::cout << "Cate bucati vrei sa elimini? (0 = tot): ";
            int numar;
            std::cin >> numar;

            eliminaProdus(index, numar);
        }

        afiseazaCos();
    }
public:
    bool proceseazaComanda(Produs **catalog) {
        if (nrProduse == 0) {
            std::cout << "Cosul este gol.\n";
            return false;
        }

        if (proprietar.getSold() < valoare) {
            sesiuneEliminare();
            std::cout << "\n Cosul a fost redus la un total acceptabil.\n";
        }

        for (int i = 0; i < nrProduse; ++i) {
            for (int j = 0; j < nrCatalog; ++j) {
                if (catalog[j]->getId() == items[i].idProdus) {
                    catalog[j]->actualizeazaStoc(items[i].cantitate);
                    break;
                }
            }
        }

        std::cout << "Comanda a fost procesata cu succes!\n";
        return true;
    }
};

std::ostream &operator<<(std::ostream &os, const Cos &c) {
    os << "Id-ul comenzii: " << c.id_comanda << "\n" << c.nrProduse << " produse in valoare de " << c.valoare <<
            " de lei";
    return os;
}

int main() {
    int nr = 10;
    Produs **catalog = new Produs *[nr];
    catalog[0] = new Produs("Scaun romantic", 89.99, 210, 12);
    catalog[1] = new Produs("Masa inima", 209.98, 220, 16);
    catalog[2] = new Produs("Fata de masa carouri", 24.97, 230, 44);
    catalog[3] = new Produs("Set tacamuri inox", 36.66, 240, 31);
    catalog[4] = new Produs("Carne tocata vita", 15.50, 110, 23);
    catalog[5] = new Produs("Fusilli", 6.99, 120, 40);
    catalog[6] = new Produs("Spaghetti", 5.49, 121, 20);
    catalog[7] = new Produs("Penne", 7.67, 122, 32);
    catalog[8] = new Produs("Sos rosu", 10.00, 130, 50);
    catalog[9] = new Produs("Sos alb", 14.20, 131, 34);

    char nume[100];
    char adresa[200];
    double sold;
    int id_client = 12345;
    int id_cos = 54321;

    std::cout << "Salut, bine ai venit pe platforma de aprovizionare pentru restaurantul tau romantic de paste!\n";
    std::cout << "Introdu numele: ";
    std::cin.getline(nume, 100);

    std::cout << "Introdu adresa: ";
    std::cin.getline(adresa, 200);

    std::cout << "Introdu soldul disponibil: ";
    std::cin >> sold;


    Client client(nume, adresa, sold, id_client);
    Cos cos(client, id_cos);


    bool comandaFinalizata = false;
    while (!comandaFinalizata) {
        std::cout << "\033[2J\033[1;1H";

        std::cout << "Catalog produse:\n";
        for (int i = 0; i < nr; ++i) {
        std::cout << *catalog[i];
        }

        std::cout << "\n--- MENIU ---\n";
        std::cout << "1. Adauga produs\n";
        std::cout << "2. Elimina produs\n";
        std::cout << "3. Afiseaza cos\n";
        std::cout << "4. Finalizeaza comanda (check-out)\n";
        std::cout << "5. Iesire \n";
        std::cout << "Alege optiunea: ";

        int opt;
        std::cin >> opt;
        std::cin.ignore();

        switch (opt) {
            case 1: {
                std::cout << "\033[2J\033[1;1H";
                std::cout << "Catalog produse:\n";
                for (int i = 0; i < nr; ++i) {
                std::cout << *catalog[i];
                }
                std::cout <<"\n";
                int id, cant;
                std::cout << "ID produs: ";
                std::cin >> id;
                std::cout << "Cantitate: ";
                std::cin >> cant;
                Produs* prodGasit = nullptr;
                for (int i = 0; i < nr; ++i) {
                    if (catalog[i]->getId() == id) {
                        prodGasit = catalog[i];
                        break;
                    }
                }
                if (prodGasit) {
                    cos.adaugaProdus(id, cant, prodGasit->getPret(), catalog);
                } else {
                    std::cout << "Produs inexistent.\n";
                }
                break;
            }
            case 2: {
                std::cout << "\033[2J\033[1;1H";
                std::cout << "Catalog produse:\n";
                for (int i = 0; i < nr; ++i) {
                std::cout << *catalog[i];
                }
                std::cout <<"\n";
                cos.afiseazaCos();
                if (cos.getNrProduse() == 0) break;
                std::cout << "Indexul produsului de eliminat: ";
                int idx;
                std::cin >> idx;
                std::cout << "Cate bucati (0 = tot): ";
                int cant;
                std::cin >> cant;
                cos.eliminaProdus(idx - 1, cant);
                break;
            }
            case 3:
                std::cout << "\033[2J\033[1;1H";
                cos.afiseazaCos();
                break;
            case 4:
                std::cout << "\033[2J\033[1;1H";
                if (cos.proceseazaComanda(catalog)) {
                    comandaFinalizata = true;
                }
                std::cout<<cos;
                break;
            case 5:
                std::cout << "Ai renuntat la comanda.\n";
                comandaFinalizata = true;
                break;
            default:
                std::cout << "Optiune invalida.\n";
        }
    }

    for (int i = 0; i < nr; ++i) delete catalog[i];
    delete[] catalog;

    return 0;
}
