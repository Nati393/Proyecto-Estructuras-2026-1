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

    //Constructor vacío necesario para que unordered_map pueda crear sospechosos
    Sospechoso();

    //Constructor principal con nombre y lista de atributos
    Sospechoso(string n, vector<string> attrs);

    //Revela el atributo en la posición indicada y lo acumula
    string revelarAtributo(int indice);

    //Devuelve todos los atributos revelados separados por coma
    string getAtributosRevelados();
};

#endif