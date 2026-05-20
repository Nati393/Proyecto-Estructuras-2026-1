#ifndef DETECTIVE_H
#define DETECTIVE_H
#include <string>
#include <stack>
//Se importa la clase Pista
#include "Pista.h"

using namespace std;

class Detective {
public:
    string nombre;
    int fila;
    int columna;
    int puntaje;
    int pistasRecogidas;
    //LIFO:La ultima pista recogida es la primera disponible
    stack<Pista> pilaPistas;

    Detective(string n, int f, int c);

    //Aquí se mueve el detective
    void mover(int nuevaFila, int nuevaColumna);

    //Agrega pista a la pila
    void recogerPista(Pista p);

    //Devuelve la pista del tope sin sacarla
    Pista verUltimaPista();

    //Saca y devuelve la pista del tope
    Pista usarPista();

    //Verifica si tiene pistas
    bool tienePistas();

    //Suma 1 al puntaje por movimiento
    void sumarMovimiento();

    void mostrarPilas();
};
#endif