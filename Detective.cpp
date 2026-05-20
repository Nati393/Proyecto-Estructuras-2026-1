#include "Detective.h"
#include <iostream>
using namespace std;

Detective::Detective(string n, int f, int c) {
    nombre = n;
    fila  = f;
    columna = c;
    puntaje  = 0;
    pistasRecogidas = 0;
}
//Se reemplaza la posición actual con la nueva
void Detective::mover(int nuevaFila, int nuevaColumna) {
    fila    = nuevaFila;
    columna = nuevaColumna;
}
//Mete la pista a la pila y cuenta cuántas lleva
void Detective::recogerPista(Pista p) {
    pilaPistas.push(p);
    pistasRecogidas++;
}
Pista Detective::verUltimaPista() {
    return pilaPistas.top();
}
//Agarra y sac el tope de la pila
Pista Detective::usarPista() {
    Pista p = pilaPistas.top();
    pilaPistas.pop();
    pistasRecogidas--;
    return p;
}
//Verifica si la pila no está vacía
bool Detective::tienePistas() {
    return !pilaPistas.empty();
}
//Se suma un punto a un movimiento
void Detective::sumarMovimiento() {
    puntaje++;
}
//Se imprimme desde la primera pista hasta la última
void Detective::mostrarPilas() {
    if (pilaPistas.empty()) {
        cout << "No tienes ninguna pista.\n";
        return;
    }
    stack<Pista> copia = pilaPistas;
    stack<Pista> invertida;

    while (!copia.empty()) {
        invertida.push(copia.top());
        copia.pop();
    }
    //Imprime la pila
    cout << "\n[ Pistas recolectadas ]\n";
    cout << "[ # # # # # # # # # ]\n";

    //Se guardan las pistas que hay en la pila
    int total = invertida.size();
    int pos = 1;

    while (!invertida.empty()) {
        //Agarra la pista y la saca
        Pista p = invertida.top();
        invertida.pop();
        //Agregar la pista de acuerdo al orden
        if (pos == total)
            cout << "[ # " << p.getNombre() << " # ]  última\n";
        else
            cout << "[ # " << p.getNombre() << " # ]\n";
        pos++;
    }
    cout << "[ # # # # # # # # # ]\n";
}