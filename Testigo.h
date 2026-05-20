#ifndef TESTIGO_H
#define TESTIGO_H
#include <string>

using namespace std;

class Testigo {
public:
    string nombre;
    string declaracion;
    int fila;
    int columna;
    bool yaDeclaró;
    Testigo(string n, string dec, int f, int c);

    string getDeclaracion();
};
#endif