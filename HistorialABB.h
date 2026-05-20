#ifndef HISTORIALABB_H
#define HISTORIALABB_H

#include <string>
#include <vector>
using namespace std;

//Nodo del ABB: guarda nombre del detective y su mejor puntaje
struct NodoABB {
    string nombre;
    int puntaje;
    NodoABB* izquierdo;
    NodoABB* derecho;

    NodoABB(string n, int p);
};

//ABB para historial de puntajes (puntos 19, 20, 21, 22, 23)
class HistorialABB {
private:
    NodoABB* raiz;

    //Inserta recursivamente respetando el orden del ABB por nombre
    NodoABB* insertarRec(NodoABB* nodo, string nombre, int puntaje);

    //Recorre inorden y guarda nodos en un vector para ordenar por puntaje
    void inordenRec(NodoABB* nodo, vector<NodoABB*>& nodos);

    //Busca un detective por nombre recursivamente
    NodoABB* buscarRec(NodoABB* nodo, string nombre);

    //Libera memoria recursivamente
    void destruirRec(NodoABB* nodo);

public:
    HistorialABB();
    ~HistorialABB();

    //Inserta o actualiza puntaje del detective
    void insertar(string nombre, int puntaje);

    //Muestra todos los detectives de menor a mayor puntaje (punto 23)
    void mostrarHistorial();

    //Busca y muestra el mejor puntaje de un detective (punto 22)
    void buscarDetective(string nombre);
};

#endif