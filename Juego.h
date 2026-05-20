#ifndef JUEGO_H
#define JUEGO_H

#include "Mapa.h"
#include "Detective.h"
#include "Sospechoso.h"
#include "Testigo.h"
#include "HistorialABB.h"
#include <unordered_map>
#include <queue>
#include <vector>
using namespace std;

class Juego {
private:
    Mapa mapa;
    Detective* detective;
    //Tabla Hash de sospechosos: búsqueda O(1) por nombre (punto 15)
    unordered_map<string, Sospechoso> tablaSospechosos;
    //Cola de declaraciones de testigos (punto 17)
    queue<Testigo> colaTestigos;
    //Historial de puntajes en ABB (punto 19)
    HistorialABB historial;
    //Nombre del culpable para comparar en acusación
    string nombreCulpable;
    //Indice del atributo que se revelará en la próxima pista
    int indiceAtributoRevelado;

    //Inicializa los 8 sospechosos en la tabla hash
    void inicializarSospechosos();

    //Coloca detective en posición aleatoria libre
    void posicionarDetective();

    //Maneja lo que pasa al pisar una celda
    void procesarCelda();

    //Aplica efecto de la pista usada con X
    void aplicarEfectoPista(Pista p);

    //Muestra tabla hash de sospechosos con atributos revelados
    void mostrarSospechosos();

    //Fase final: el usuario acusa a un sospechoso
    void faseAcusacion();

    //Imprime encabezado con nombre y puntaje
    void imprimirEncabezado();

public:
    Juego();
    ~Juego();

    //Inicia y controla el flujo completo del juego
    void iniciar();
};

#endif