#include "Sospechoso.h"

//Constructor vacío: unordered_map lo necesita para reservar espacio internamente
Sospechoso::Sospechoso() {
    nombre     = "";
    esCulpable = false;
}

//Inicializa sospechoso con su nombre y todos sus atributos físicos
Sospechoso::Sospechoso(string n, vector<string> attrs) {
    nombre     = n;
    atributos  = attrs;
    esCulpable = false;
}

//Revela el atributo en la posición 'indice' si existe
//Lo agrega a la lista de revelados para mostrarlo después
string Sospechoso::revelarAtributo(int indice) {
    if (indice >= 0 && indice < (int)atributos.size()) {
        string attr = atributos[indice];
        //Acumula el atributo revelado para mostrarlo con S
        atributosRevelados.push_back(attr);
        return attr;
    }
    return "";
}

//Une todos los atributos revelados en un solo texto con comas
//Si no se ha revelado nada aún, devuelve "-" como en el ejemplo del profe
string Sospechoso::getAtributosRevelados() {
    if (atributosRevelados.empty()) return "-";
    string resultado = "";
    for (int i = 0; i < (int)atributosRevelados.size(); i++) {
        resultado += atributosRevelados[i];
        //Agrega coma entre atributos pero no al final
        if (i < (int)atributosRevelados.size() - 1)
            resultado += ", ";
    }
    return resultado;
}