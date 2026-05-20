#include "Mapa.h"
#include "Detective.h"
#include "Pista.h"
#include "Sospechoso.h"
#include "Testigo.h"
#include <iostream>
using namespace std;
int main() {
    Mapa mapa;
    mapa.colocarCallejones(16);
    mapa.colocarPistas(10);
    mapa.colocarTestigos(5);

    Detective detective("Natalia",5,5);
    cout << "\n----- EL CASO DEL DETECTIVE -----\n\n";
    //Definimos la posición del detective
    cout << detective.nombre << ", tu puntaje es: " << detective.puntaje << "\n\n";
    mapa.imprimirTablero(detective.fila, detective.columna);

    //Los datos son para verificar la funcionalidad de lo que hemos realizado
    Pista p('H', 3, 7);
    detective.recogerPista(p);
    cout << "\nPista recogida: " << p.getNombre() << "\n";
    detective.mostrarPilas();

    Sospechoso s("Carlos", {"alto", "zurdo", "cabello negro"});
    cout << "\nSospechoso: " << s.nombre << "\n";
    cout << "Atributos revelados: "<< s.getAtributosRevelados() << "\n";
    s.revelarAtributo(0);
    cout << "Atributos revelados: "<< s.getAtributosRevelados() << "\n";

    Testigo t("Rafael", "Vi a alguien alto salir corriendo", 2, 3);
    cout << "\nTestigo: " << t.nombre << "\n";
    cout << "Declaración: " << t.getDeclaracion() << "\n";

    return 0;
}