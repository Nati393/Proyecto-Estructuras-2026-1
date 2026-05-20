#include "HistorialABB.h"
#include <iostream>
#include <algorithm>
using namespace std;

//Inicializa nodo con nombre, puntaje y punteros en nullptr
NodoABB::NodoABB(string n, int p) {
    nombre    = n;
    puntaje   = p;
    izquierdo = nullptr;
    derecho   = nullptr;
}

HistorialABB::HistorialABB() {
    raiz = nullptr;
}

HistorialABB::~HistorialABB() {
    destruirRec(raiz);
}

//Libera memoria de todos los nodos del árbol
void HistorialABB::destruirRec(NodoABB* nodo) {
    if (nodo == nullptr) return;
    destruirRec(nodo->izquierdo);
    destruirRec(nodo->derecho);
    delete nodo;
}

//Inserta recursivamente ordenando por nombre (como vimos en clase)
//Si el detective ya existe, conserva el menor puntaje (punto 20)
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

//Recorre el árbol inorden y guarda cada nodo en el vector
//El inorden del ABB da los nombres en orden alfabético
//Luego ordenamos ese vector por puntaje para cumplir el punto 23
void HistorialABB::inordenRec(NodoABB* nodo, vector<NodoABB*>& nodos) {
    if (nodo == nullptr) return;
    inordenRec(nodo->izquierdo, nodos);
    nodos.push_back(nodo);
    inordenRec(nodo->derecho, nodos);
}

//Muestra todos los detectives ordenados de menor a mayor puntaje (punto 23)
//Primero recoge todos los nodos con inorden, luego los ordena por puntaje
void HistorialABB::mostrarHistorial() {
    if (raiz == nullptr) {
        cout << "No hay detectives registrados aun.\n";
        return;
    }

    //Recoge todos los nodos del ABB en un vector
    vector<NodoABB*> nodos;
    inordenRec(raiz, nodos);

    //Ordena el vector de menor a mayor puntaje con bubble sort
    //Usamos bubble sort porque lo vimos en clase
    for (int i = 0; i < (int)nodos.size() - 1; i++) {
        for (int j = 0; j < (int)nodos.size() - i - 1; j++) {
            if (nodos[j]->puntaje > nodos[j+1]->puntaje) {
                NodoABB* temp = nodos[j];
                nodos[j]      = nodos[j+1];
                nodos[j+1]    = temp;
            }
        }
    }

    //Imprime el historial ordenado de menor a mayor puntaje
    cout << "\n===== HISTORIAL DE DETECTIVES =====\n";
    cout << "  (ordenado de menor a mayor puntaje)\n";
    for (int i = 0; i < (int)nodos.size(); i++) {
        cout << "  " << i+1 << ". " << nodos[i]->nombre
             << " -> " << nodos[i]->puntaje << " movimientos\n";
    }
    cout << "===================================\n";
}

//Busca detective por nombre en el ABB (punto 22)
NodoABB* HistorialABB::buscarRec(NodoABB* nodo, string nombre) {
    if (nodo == nullptr)        return nullptr;
    if (nombre == nodo->nombre) return nodo;
    if (nombre < nodo->nombre)  return buscarRec(nodo->izquierdo, nombre);
    return buscarRec(nodo->derecho, nombre);
}

//Muestra si el detective ha jugado antes y cuál fue su mejor puntaje
void HistorialABB::buscarDetective(string nombre) {
    NodoABB* resultado = buscarRec(raiz, nombre);
    if (resultado != nullptr)
        cout << nombre << " ha jugado antes. Mejor puntaje: "
             << resultado->puntaje << " movimientos.\n";
    else
        cout << nombre << " no ha jugado antes.\n";
}