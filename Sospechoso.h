#ifndef SOSPECHOSO_H
#define SOSPECHOSO_H
#include <string>
#include <vector>

using namespace std;

class Sospechoso {
public:
    string nombre;
    vector<string> atributos;
    vector<string> atributosRevelados;
    bool esCulpable;

    //Se declara el constructor con los parámetros y el tipo
    Sospechoso(string n, vector<string> attrs);

    //Se revela el sig atributo que no ha sido revelado
    string revelarAtributo(int indice);

    //Devuelve atributos que ya fueron revelados
    string getAtributosRevelados();
};
#endif