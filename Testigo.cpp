#include "Testigo.h"

//Inicializa testigo con nombre, declaración y posición
Testigo::Testigo(string n, string dec, int f, int c) {
    nombre= n;
    declaracion = dec;
    fila = f;
    columna = c;
    yaDeclaró = false;
}
//Retorna la declaración del testigo
string Testigo::getDeclaracion() {
    return declaracion;
}