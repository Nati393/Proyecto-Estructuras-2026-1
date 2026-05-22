#include "Mapa.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Construye 121 nodos y los enlaza en 4 direcciones
Mapa::Mapa() {
    //construcción inicial
    Ubicacion* nodos[FILAS][COLUMNAS];

    for (int f = 0; f < FILAS; f++)
        for (int c = 0; c < COLUMNAS; c++)
            nodos[f][c] = new Ubicacion(f, c);

    //Enlaza con vecinos
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            nodos[f][c]->arriba    = (f > 0)           ? nodos[f-1][c] : nullptr;
            nodos[f][c]->abajo     = (f < FILAS-1)     ? nodos[f+1][c] : nullptr;
            nodos[f][c]->izquierda = (c > 0)           ? nodos[f][c-1] : nullptr;
            nodos[f][c]->derecha   = (c < COLUMNAS-1)  ? nodos[f][c+1] : nullptr;
        }
    }
    cabeza=nodos[0][0];
    inicializarBordes();
}
//Aquí se libera la memoria de los nodos
Mapa::~Mapa() {
    Ubicacion* filaActual = cabeza;
    while (filaActual != nullptr) {
        Ubicacion* sigFila = filaActual->abajo;
        Ubicacion* nodo    = filaActual;
        while (nodo != nullptr) {
            Ubicacion* sigNodo = nodo->derecha;
            delete nodo;
            nodo = sigNodo;
        }
        filaActual = sigFila;
    }
}
//Empieza desde la cabeza hasta (fila, col) por punteros
Ubicacion* Mapa::obtenerNodo(int fila, int col) {
    Ubicacion* actual = cabeza;
    for (int f = 0; f < fila; f++) actual = actual->abajo;
    for (int c = 0; c < col;  c++) actual = actual->derecha;
    return actual;
}
Ubicacion* Mapa::getNodo(int fila, int col) {
    return obtenerNodo(fila, col);
}
// Marca los bordes exteriores como EDIFICIOS
void Mapa::inicializarBordes() {
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            if (f == 0 || f == FILAS-1 || c == 0 || c == COLUMNAS-1) {
                Ubicacion* n  = obtenerNodo(f, c);
                n->tipo       = TipoCelda::EDIFICIO;
                n->descubierta = true;
            }
        }
    }
}
//Revisa que la celda interior esté libre
bool Mapa::posicionDisponible(int fila, int col) {
    if (fila <= 0 || fila >= FILAS-1 || col<=0 || col>=COLUMNAS-1)
        return false;
    return obtenerNodo(fila, col)->tipo==TipoCelda::NO_VISITADO;
}
//Coloca los callejones
void Mapa::colocarCallejones(int cantidad) {
    int colocados = 0;
    while (colocados < cantidad) {
        int f = 1 + rand() % (FILAS-2);
        int c = 1 + rand() % (COLUMNAS-2);
        if (posicionDisponible(f, c)) {
            obtenerNodo(f, c)->tipo = TipoCelda::CALLEJON;
            colocados++;
        }
    }
}
//Asigna las pistas
void Mapa::colocarPistas(int cantidad) {
    char tipos[] = {'H', 'C', 'T', 'P'};
    int colocados = 0;
    while (colocados < cantidad) {
        int f = 1 + rand() % (FILAS-2);
        int c = 1 + rand() % (COLUMNAS-2);
        if (posicionDisponible(f, c)) {
            Ubicacion* n  = obtenerNodo(f, c);
            n->tipo       = TipoCelda::PISTA;
            n->tipoPista  = tipos[rand() % 4];
            colocados++;
        }
    }
}
//Coloca los testigos
void Mapa::colocarTestigos(int cantidad) {
    int colocados = 0;
    while (colocados < cantidad) {
        int f = 1 + rand() % (FILAS-2);
        int c = 1 + rand() % (COLUMNAS-2);
        if (posicionDisponible(f, c)) {
            obtenerNodo(f, c)->tipo = TipoCelda::TESTIGO;
            colocados++;
        }
    }
}
//Tapa las celdas que son descubiertas con NO_VISITADO
void Mapa::resetearDescubiertas() {
    Ubicacion* filaActual = cabeza->abajo;
    while (filaActual != nullptr && filaActual->abajo != nullptr) {
        Ubicacion* actual = filaActual->derecha;
        while (actual != nullptr && actual->derecha != nullptr) {
            if (actual->tipo == TipoCelda::VACIO) {
                actual->tipo       = TipoCelda::NO_VISITADO;
                actual->descubierta = false;
            }
            actual = actual->derecha;
        }
        filaActual = filaActual->abajo;
    }
}
// Dibuja el tablero siguiendo los punteros
void Mapa::imprimirTablero(int filaDetective, int colDetective) {
    Ubicacion* filaActual = cabeza;
    while (filaActual != nullptr) {
        Ubicacion* actual = filaActual;
        while (actual != nullptr) {
            int f = actual->fila;
            int c = actual->columna;

            if (f == filaDetective && c == colDetective) {
                cout << " I ";
            } else if (actual->tipo == TipoCelda::EDIFICIO) {
                cout << " # ";
            } else if (actual->tipo == TipoCelda::CALLEJON && actual->callejonVisible) {
                cout << " | ";
            } else if (actual->tipo == TipoCelda::TESTIGO && actual->descubierta) {
                cout << " W ";
            } else if (actual->descubierta) {
                cout << "   ";
            } else {
                cout << " o ";
            }
            actual = actual->derecha;
        }
        cout << "\n";
        filaActual = filaActual->abajo;
    }
}