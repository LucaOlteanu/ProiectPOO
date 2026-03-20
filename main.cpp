/*
Tema proiectului este Comert, ideea mea de implementare a unui program orientat pe obiecte va fi o comanda online de produse de la un singur magazin. Pentru inceput,
clasele vor fi Produs, Utilizator si Cos/Comanda
 */
#include <iostream>
#include <string>

class Client {
    std::string nume;
    std::string adresa;
    double sold;
    int id;
public:
    Client(const std::string& nume_, std::string& adresa_, double sold_, const int id_) : nume{nume_}, adresa{adresa_}, sold{sold_}, id{id_} {}
};

class Produs {
        std::string nume;
        double pret;
        int id;
        int stoc;
    public:
        Produs(const std::string& nume_, double pret_, const int id_, int stoc_) : nume{nume_}, pret {pret_}, id{id_}, stoc{stoc_} {}
};

class Cos {
        double valoare;
        Client proprietar;
        int id_comanda;
        int nrProduse;
        std::string status;
    public:
        Cos(const Client proprietar_, const int id_comanda_, int nrProduse_, double valoare_, std::string status_): proprietar{proprietar_}, id_comanda{id_comanda_}, nrProduse{nrProduse_}, status{status_}, valoare {valoare_} {}
};
int main() {
    return 0;
}