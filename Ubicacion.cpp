#include "Ubicacion.h"

//Constructor para inicializar
Ubicacion::Ubicacion(int f, int c) {
    fila            = f;
    columna         = c;
    tipo            = TipoCelda::NO_VISITADO;
    descubierta     = false;
    tipoPista       = '\0';
    callejonVisible = false;
    arriba          = nullptr;
    abajo           = nullptr;
    izquierda       = nullptr;
    derecha         = nullptr;
}