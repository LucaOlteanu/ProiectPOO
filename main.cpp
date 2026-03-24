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
    char* nume;
    char* adresa;
    double sold;
    int id;
public:
    Client(const char* nume_, const char* adresa_, const double sold_, const int id_): sold{sold_}, id{id_} {
        nume = new char[strlen(nume_) + 1];
        strcpy(nume, nume_);
        adresa = new char[strlen(adresa_) + 1];
        strcpy(adresa, adresa_);
    }

    Client(const Client& other) : sold{other.sold}, id{other.id} {
        nume = new char[strlen(other.nume) + 1];
        strcpy(nume, other.nume);
        adresa = new char[strlen(other.adresa) + 1];
        strcpy(adresa, other.adresa);
    }

    Client& operator=(const Client& other) {
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

    const char* getNume() const { return nume; }
    const char* getAdresa() const { return adresa; }
    double getSold() const { return sold; }
    int getId() const { return id; }

    friend std::ostream& operator<<(std::ostream& os, const Client& c);

    ~Client() {
        delete[] nume;
        delete[] adresa;
    }
};

std::ostream& operator<<(std::ostream& os, const Client& c) {
    os << c.nume;
    return os;
}

class Produs {
        char* nume;
        double pret;
        int id, stoc;
    public:
        Produs(const char* nume_, const double pret_, const int id_, int stoc_) : pret{pret_}, id{id_}, stoc{stoc_} {
            nume = new char[strlen(nume_) + 1];
            strcpy(nume, nume_);
        }

        Produs(const Produs& other): stoc{other.stoc}, id{other.id}, pret{other.pret} {
            this->nume = new char[strlen(other.nume) + 1];
            strcpy(this->nume, other.nume);
        }

        Produs& operator=(const Produs& other) {
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

        const char* getNume() const { return nume; }
        double getPret() const { return pret; }
        int getStoc() const { return stoc; }
        int getId() const { return id; }

        friend std::ostream& operator<<(std::ostream& os, const Produs& pr);

        ~Produs() {
            delete[] nume;
        }
};

std::ostream& operator<<(std::ostream& os, const Produs& pr) {
    os << pr.id << " " << pr.nume << " " << pr.pret<<" lei: " ;
    if (pr.stoc > 0) os<<"Disponibil"<<"\n";
    else os << "Indisponibil" << "\n";
    return os;
}

class Cos {
    Client proprietar;
    int id_comanda;
    int nrProduse;
    double valoare;

    struct ItemComanda {
        int idProdus;
        int cantitate;
        double pretUnitar;
    };
    ItemComanda* items;

public:

    Cos(const Client& proprietar_, const int id_comanda_) : proprietar{proprietar_}, id_comanda{id_comanda_}, nrProduse{0}, valoare{0.0} {
        items = new ItemComanda[10];
    }

    Cos(const Cos& other)
        : proprietar{other.proprietar}, id_comanda{other.id_comanda},
          nrProduse{other.nrProduse}, valoare{other.valoare}
    {
        items = new ItemComanda[10];
        for (int i = 0; i < nrProduse; ++i)
            items[i] = other.items[i];

    }

    Cos& operator=(const Cos& other) {
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

    friend std::ostream& operator<<(std::ostream& os, const Cos& c);

    ~Cos() {
        delete[] items;
    }

    void adaugaProdus(int idProdus, int cantitate, double pret, Produs** catalog, int nrProduse) {

        bool gasit = false;
        for (int i = 0; i < nrProduse; ++i) {
            if (catalog[i]->getId() == idProdus) {
                if (catalog[i]->getStoc() < cantitate) {
                    std::cout << "Stoc insuficient pentru produsul "
                              << catalog[i]->getNume() << " (stoc: "
                              << catalog[i]->getStoc() << ")\n";
                    if (catalog[i]->getId()%10 != 0 || catalog[i+1]->getId() == catalog[i]->getId()+1 ) {
                        std::cout << "Produse similare: ";
                        int idsim = catalog[i]->getId() / 10;
                        for (int j = 0; j < nrProduse; ++j) {
                            if (catalog[j]->getId() / 10 == idsim)
                                std::cout << *catalog[i];
                        }
                    }
                    return;
                }
                gasit = true;
                break;
            }
        }
        if (!gasit) {
            std::cout << "Produsul cu ID " << idProdus << " nu există în catalog.\n";
            return;
        }

        items[nrProduse].idProdus = idProdus;
        items[nrProduse].cantitate = cantitate;
        items[nrProduse].pretUnitar = pret;
        nrProduse++;

        valoare += cantitate * pret;
    }

};
std::ostream& operator<<(std::ostream& os, const Cos& c) {
    os<<"Id-ul comenzii: "<<c.id_comanda<<"\n"<<c.nrProduse<<" produse in valoare de "<<c.valoare<<" de lei";
    return os;
}

int main() {
    int nr = 10;
    Produs** catalog = new Produs*[nr];
    catalog[0] = new Produs("Scaun romantic", 89.99, 210, 12);
    catalog[1] = new Produs ("Masa inima", 209.98, 220, 16);
    catalog[2] = new Produs ("Fata de masa carouri", 24.97, 230, 44);
    catalog[3] = new Produs ("Set tacamuri inox", 36.66,240, 31);
    catalog[4] = new Produs("Carne tocata vita", 15.50, 110, 23);
    catalog[5] = new Produs ("Fusilli", 6.99, 120, 40);
    catalog[6] = new Produs ("Spaghetti", 5.49, 121, 20);
    catalog[7] = new Produs ("Penne", 7.67, 122, 32);
    catalog[8] = new Produs ("Sos rosu", 10.00, 130, 50);
    catalog[9] = new Produs ("Sos alb", 14.20, 131, 34);

    char nume[100];
    char adresa[200];
    double sold;
    int id=12345;

    std::cout << "Salut, bine ai venit pe platforma de aprovizionare pentru restaurantul tau romantic de paste!\n";
    std::cout << "Introdu numele: ";
    std::cin.getline(nume, 100);

    std::cout << "Introdu adresa: ";
    std::cin.getline(adresa, 200);

    std::cout << "Introdu soldul disponibil: ";
    std::cin >> sold;

    Client client(nume, adresa, sold, id);

    std::cout << "Catalog produse:\n";
    for (int i = 0; i < nr; ++i) {
        std::cout << *catalog[i];
    }
    int idprod;
    int cantitateprod;
    while (true){
        std::cin >> idprod >> cantitateprod;
        Cos::adaugaProdus(idprod, cantitateprod);
    }

    return 0;
}