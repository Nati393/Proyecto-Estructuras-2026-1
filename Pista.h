#ifndef PISTA_H
#define PISTA_H

#include <string>
using namespace std;

class Pista {
public:
    //tipo es H, C, T o P
    char tipo;
    string nombre;
    int fila;
    int columna;

    Pista(char t, int f, int c);

    //Devuelve el nombre del tipo
    string getNombre();
};

#endif