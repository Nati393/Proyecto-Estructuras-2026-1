#include "Sospechoso.h"

//Se inicializa sospechoso con nombre y atributos
Sospechoso::Sospechoso(string n, vector<string> attrs) {
    nombre = n;
    atributos = attrs;
    esCulpable  = false;
}
//Se revelan los atributos por indice
string Sospechoso::revelarAtributo(int indice) {
    //Verifica que el índice sea válido
    if (indice >= 0 && indice < (int)atributos.size()) {
        string attr = atributos[indice];
        //Lo agrega a la lista de revelados
        atributosRevelados.push_back(attr);
        return attr;
    }
    return "";
}
string Sospechoso::getAtributosRevelados() {
    if (atributosRevelados.empty()) return "-";
    //Recorre los atributos revelados y los une con una coma
    string resultado = "";
    for (int i = 0; i < (int)atributosRevelados.size(); i++) {
        resultado += atributosRevelados[i];
        if (i < (int)atributosRevelados.size() - 1)
            resultado += ", ";
    }
    return resultado;
}