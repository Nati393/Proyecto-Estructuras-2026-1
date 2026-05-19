#include "Mapa.h"
#include <iostream>
using namespace std;
int main() {
    Mapa mapa;
    mapa.colocarCallejones(16);
    mapa.colocarPistas(10);
    mapa.colocarTestigos(5);

    cout << "\n----- EL CASO DEL DETECTIVE -----\n\n";
    //Definimos la posición del detective
    mapa.imprimirTablero(5, 5);
    return 0;
}