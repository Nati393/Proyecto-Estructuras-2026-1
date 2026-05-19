#ifndef MAPA_H
#define MAPA_H
#include "Ubicacion.h"

const int FILAS    = 11;
const int COLUMNAS = 11;

class Mapa {
private:
    Ubicacion* cabeza;

    //Navega hasta (fila, columna) desde cabeza
    Ubicacion* obtenerNodo(int fila, int col);

public:
    Mapa();
    ~Mapa();
    //Marca los bordes (EDIFICIOS)
    void inicializarBordes();

    //Ubica LOS elementos
    void colocarCallejones(int cantidad);
    void colocarPistas(int cantidad);
    void colocarTestigos(int cantidad);

    //Verifica si la celda interior libre
    bool posicionDisponible(int fila, int col);

    //Tapa lo que ya se descubrio
    void resetearDescubiertas();

    //Devuelve nodo al Juego
    Ubicacion* getNodo(int fila, int col);

    //Imprime el tablero
    void imprimirTablero(int filaDetective, int colDetective);
};

#endif