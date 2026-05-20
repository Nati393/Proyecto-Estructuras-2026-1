#include "Pista.h"

//Inicializa pista con tipo y posicion
Pista::Pista(char t, int f, int c) {
    tipo    = t;
    fila    = f;
    columna = c;

    //Se agrega el nombre según el tipo
    if      (tipo == 'H') nombre = "Huella";
    else if (tipo == 'C') nombre = "Coartada";
    else if (tipo == 'T') nombre = "Testimonio";
    else if (tipo == 'P') nombre = "Prueba Forense";
    else                  nombre = "Desconocida";
}

//Retorna el nombre
string Pista::getNombre() {
    return nombre;
}