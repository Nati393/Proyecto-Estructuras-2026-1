#ifndef UBICACION_H
#define UBICACION_H
#include <string>
using namespace std;

//Clasifica lo quee hay en la celda
enum class TipoCelda {
    EDIFICIO,
    NO_VISITADO,
    VACIO,
    CALLEJON,
    PISTA,
    TESTIGO
};

class Ubicacion {
public:
    int fila;
    int columna;
    TipoCelda tipo;
    bool descubierta;
    char tipoPista;
    bool callejonVisible;

    //Punteros es donde extiende la lista doble
    Ubicacion* arriba;
    Ubicacion* abajo;
    Ubicacion* izquierda;
    Ubicacion* derecha;

    //En filas y columnas
    Ubicacion(int f, int c);
};
#endif