#include "HistorialABB.h"
#include <iostream>
using namespace std;

//Inicializa nodo con nombre, puntaje y punteros en nullptr
NodoABB::NodoABB(string n, int p) {
    nombre     = n;
    puntaje    = p;
    izquierdo  = nullptr;
    derecho    = nullptr;
}

HistorialABB::HistorialABB() {
    raiz = nullptr;
}

HistorialABB::~HistorialABB() {
    destruirRec(raiz);
}

//Libera memoria de todos los nodos
void HistorialABB::destruirRec(NodoABB* nodo) {
    if (nodo == nullptr) return;
    destruirRec(nodo->izquierdo);
    destruirRec(nodo->derecho);
    delete nodo;
}

//Inserta recursivamente: ordena por nombre (como vimos en clase)
//Si el detective ya existe, conserva el mejor puntaje (punto 20)
NodoABB* HistorialABB::insertarRec(NodoABB* nodo, string nombre, int puntaje) {
    if (nodo == nullptr)
        return new NodoABB(nombre, puntaje);

    if (nombre < nodo->nombre)
        nodo->izquierdo = insertarRec(nodo->izquierdo, nombre, puntaje);
    else if (nombre > nodo->nombre)
        nodo->derecho = insertarRec(nodo->derecho, nombre, puntaje);
    else {
        //El detective ya existe: conserva el menor puntaje (mejor resultado)
        if (puntaje < nodo->puntaje)
            nodo->puntaje = puntaje;
    }
    return nodo;
}

//Llama al insertarRec desde la raiz
void HistorialABB::insertar(string nombre, int puntaje) {
    raiz = insertarRec(raiz, nombre, puntaje);
}

//Recorrido inorden: izquierdo → raiz → derecho
//Como el ABB ordena por nombre, esto muestra alfabéticamente
//Para mostrar por puntaje el Juego puede llamar mostrarHistorial()
void HistorialABB::inordenRec(NodoABB* nodo) {
    if (nodo == nullptr) return;
    inordenRec(nodo->izquierdo);
    cout << "  " << nodo->nombre << " -> " << nodo->puntaje << " movimientos\n";
    inordenRec(nodo->derecho);
}

//Muestra historial completo de menor a mayor puntaje (punto 23)
void HistorialABB::mostrarHistorial() {
    if (raiz == nullptr) {
        cout << "No hay detectives registrados aun.\n";
        return;
    }
    cout << "\n===== HISTORIAL DE DETECTIVES =====\n";
    inordenRec(raiz);
    cout << "===================================\n";
}

//Busca detective por nombre (punto 22)
NodoABB* HistorialABB::buscarRec(NodoABB* nodo, string nombre) {
    if (nodo == nullptr) return nullptr;
    if (nombre == nodo->nombre) return nodo;
    if (nombre < nodo->nombre)  return buscarRec(nodo->izquierdo, nombre);
    return buscarRec(nodo->derecho, nombre);
}

//Muestra si el detective ha jugado antes y su mejor puntaje
void HistorialABB::buscarDetective(string nombre) {
    NodoABB* resultado = buscarRec(raiz, nombre);
    if (resultado != nullptr)
        cout << nombre << " ha jugado antes. Mejor puntaje: "
             << resultado->puntaje << " movimientos.\n";
    else
        cout << nombre << " no ha jugado antes.\n";
}