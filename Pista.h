#ifndef PISTA_H
#define PISTA_H
#include <string>
using namespace std;

// representa las evidencias que encuentra el detective en el mapa
// H=Huella ;  C=Coartada ;  T=Testimonio ;  P=Prueba Forense.
// t , f y c : No confundir estos son tipo, fila y columna!!!!!.
class Pista {
public:
    char tipo; // 'H', 'C', 'T', 'P'
    int fila;
    int columna;

    Pista(char t, int f, int c);
    string getNombreTipo() const;
};

#endif