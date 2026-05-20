#include "Pista.h"

Pista::Pista(char t, int f, int c) {
    tipo    = t;
    fila    = f;
    columna = c;
}

// retorna el nombre completo del tipo de pista.
string Pista::getNombreTipo() const {
    if (tipo == 'H') return "Huella";
    if (tipo == 'C') return "Coartada";
    if (tipo == 'T') return "Testimonio";
    if (tipo == 'P') return "Prueba Forense";
    return "Desconocida";
}