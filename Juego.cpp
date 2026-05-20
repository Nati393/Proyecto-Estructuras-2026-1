#include "Juego.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Juego::Juego() : mapa() {
    detective              = nullptr;
    indiceAtributoRevelado = 0;
    mapa.colocarCallejones(16);
    mapa.colocarPistas(10);
    mapa.colocarTestigos(5);
    inicializarSospechosos();
}

Juego::~Juego() {
    delete detective;
}

//Crea 8 sospechosos con atributos y los mete a la tabla hash
void Juego::inicializarSospechosos() {
    //Lista predefinida de candidatos (punto 15)
    vector<pair<string, vector<string>>> candidatos = {
        {"Carlos",   {"alto",  "zurdo",    "cabello negro", "piel clara",  "nariz ancha"}},
        {"Diana",    {"baja",  "diestra",  "cabello rojo",  "piel morena", "nariz fina"}},
        {"Eduardo",  {"medio", "zurdo",    "cabello rubio", "piel clara",  "ojos verdes"}},
        {"Fernanda", {"alta",  "diestra",  "cabello rojo",  "piel clara",  "nariz fina"}},
        {"Gonzalo",  {"alto",  "diestro",  "cabello negro",  "piel morena", "ojos cafe"}},
        {"Hilda",    {"baja",  "zurda",    "cabello gris", "piel clara",  "nariz ancha"}},
        {"Ivan",     {"medio", "diestro",  "cabello rubio", "piel morena", "ojos azules"}},
        {"Julia",    {"alta",  "zurda",    "cabello gris", "piel clara",  "nariz fina"}}
    };

    //Inserta los 8 en la tabla hash
    for (auto& par : candidatos) {
        Sospechoso s(par.first, par.second);
        tablaSospechosos[par.first] = s;
    }

    //Marca uno al azar como culpable (punto 15)
    vector<string> nombres = {"Carlos","Diana","Eduardo","Fernanda",
                              "Gonzalo","Hilda","Ivan","Julia"};
    nombreCulpable = nombres[rand() % 8];
    tablaSospechosos[nombreCulpable].esCulpable = true;
}

//Ubica al detective en una celda libre aleatoria
void Juego::posicionarDetective() {
    int f, c;
    do {
        f = 1 + rand() % 9;
        c = 1 + rand() % 9;
    } while (!mapa.posicionDisponible(f, c));

    //Marca la celda como descubierta
    mapa.getNodo(f, c)->tipo       = TipoCelda::VACIO;
    mapa.getNodo(f, c)->descubierta = true;
}

//Imprime nombre del detective y puntaje actual
void Juego::imprimirEncabezado() {
    cout << "\n" << detective->nombre
         << ", tu puntaje actual es: " << detective->puntaje << "\n";
}

//Revisa qué hay en la celda actual y actúa según el tipo
void Juego::procesarCelda() {
    Ubicacion* celda = mapa.getNodo(detective->fila, detective->columna);

    if (celda->tipo == TipoCelda::PISTA) {
        //Crea la pista, la mete a la pila y revela un atributo del culpable
        Pista p(celda->tipoPista, celda->fila, celda->columna);
        detective->recogerPista(p);

        celda->tipo       = TipoCelda::VACIO;
        celda->descubierta = true;

        cout << "\n!!! Encontraste una " << p.getNombre() << " !!!\n";

        //Revela atributo del culpable (punto 16)
        Sospechoso& culpable = tablaSospechosos[nombreCulpable];
        if (indiceAtributoRevelado < (int)culpable.atributos.size()) {
            string attr = culpable.revelarAtributo(indiceAtributoRevelado);
            cout << "Dato del culpable revelado: " << attr << "\n";
            indiceAtributoRevelado++;
        }

    } else if (celda->tipo == TipoCelda::TESTIGO) {
        //Agrega testigo a la cola si no ha declarado aún (punto 17)
        if (!celda->descubierta) {
            Testigo t("Testigo", "Vi algo sospechoso en la zona...",
                      celda->fila, celda->columna);
            colaTestigos.push(t);
            celda->descubierta = true;
            cout << "\nUn testigo vio algo. Presiona I para interrogarlo.\n";
        }
    } else {
        celda->tipo       = TipoCelda::VACIO;
        celda->descubierta = true;
    }
}

//Aplica el efecto según el tipo de pista usada (punto 14)
void Juego::aplicarEfectoPista(Pista p) {
    if (p.tipo == 'H') {
        //Huella: reduce puntaje a la mitad
        detective->puntaje /= 2;
        cout << "Huella usada: tu puntaje se redujo a la mitad -> "
             << detective->puntaje << "\n";

    } else if (p.tipo == 'C') {
        //Coartada: elimina 2 callejones del mapa
        int eliminados = 0;
        for (int f = 1; f <= 9 && eliminados < 2; f++) {
            for (int c = 1; c <= 9 && eliminados < 2; c++) {
                Ubicacion* n = mapa.getNodo(f, c);
                if (n->tipo == TipoCelda::CALLEJON) {
                    n->tipo        = TipoCelda::VACIO;
                    n->descubierta = true;
                    eliminados++;
                }
            }
        }
        cout << "Coartada usada: se eliminaron " << eliminados << " callejones.\n";

    } else if (p.tipo == 'T') {
        //Testimonio: azar entre resetear o duplicar puntaje
        if (rand() % 2 == 0) {
            detective->puntaje = 0;
            cout << "Testimonio usada: tu puntaje se reseteo a 0.\n";
        } else {
            detective->puntaje *= 2;
            cout << "Testimonio usada: tu puntaje se duplico -> "
                 << detective->puntaje << "\n";
        }

    } else if (p.tipo == 'P') {
        //Prueba forense: mueve detective a posicion aleatoria libre
        int f, c;
        do {
            f = 1 + rand() % 9;
            c = 1 + rand() % 9;
        } while (!mapa.posicionDisponible(f, c));
        detective->mover(f, c);
        cout << "Prueba forense usada: el detective se movio a ["
             << f << "," << c << "].\n";
    }

    //El mapa se tapa de nuevo con 'o' (punto 14)
    mapa.resetearDescubiertas();

    //Recoloca la pista usada en posicion aleatoria libre
    int f, c;
    do {
        f = 1 + rand() % 9;
        c = 1 + rand() % 9;
    } while (!mapa.posicionDisponible(f, c));
    Ubicacion* nuevaCelda  = mapa.getNodo(f, c);
    nuevaCelda->tipo       = TipoCelda::PISTA;
    nuevaCelda->tipoPista  = p.tipo;

    cout << "La pista volvio al mapa.\n";
}

//Muestra tabla hash con sospechosos y atributos revelados (punto 16)
void Juego::mostrarSospechosos() {
    cout << "\n===== SOSPECHOSOS DEL CASO =====\n";
    //La busqueda en unordered_map es O(1) promedio (punto 18)
    for (auto& par : tablaSospechosos) {
        cout << "  " << par.first << " | caracteristicas confirmadas: "
             << par.second.getAtributosRevelados() << "\n";
    }
    cout << "================================\n";
}

//Fase de acusacion cuando se recogen las 10 pistas (punto 18)
void Juego::faseAcusacion() {
    cout << "\n" << detective->nombre
         << ", has recolectado las 10 pistas. Es momento de acusar.\n";
    mostrarSospechosos();

    cout << "\n¿A quién acusas? > ";
    string acusado;
    cin >> acusado;

    //Busqueda O(1) en la tabla hash (punto 18)
    if (tablaSospechosos.count(acusado)) {
        if (tablaSospechosos[acusado].esCulpable) {
            cout << "\n¡Caso resuelto! " << acusado << " era el culpable.\n";
            cout << "Puntaje final: " << detective->puntaje << " movimientos.\n";
        } else {
            detective->puntaje *= 2;
            cout << "\nIncorrecto. El culpable era " << nombreCulpable << ".\n";
            cout << "Puntaje penalizado: " << detective->puntaje << " movimientos.\n";
        }
    } else {
        cout << "Ese sospechoso no existe en el caso.\n";
    }

    //Guarda puntaje en el ABB (punto 21)
    historial.insertar(detective->nombre, detective->puntaje);
}

//Flujo principal del juego
void Juego::iniciar() {
    cout << "\n========================================\n";
    cout << "       EL CASO DEL DETECTIVE            \n";
    cout << "========================================\n";
    cout << "Ingresa el nombre del detective: ";
    string nombre;
    cin >> nombre;

    //Verifica si ya ha jugado antes (punto 22)
    historial.buscarDetective(nombre);

    posicionarDetective();
    detective = new Detective(nombre, 5, 5);

    char tecla;
    while (detective->pistasRecogidas < 10) {
        imprimirEncabezado();
        mapa.imprimirTablero(detective->fila, detective->columna);
        cout << "\nMovimiento (W/A/S/D) | T: pistas | Q: sospechosos | "
             << "I: interrogar | X: usar pista\n> ";
        cin >> tecla;
        tecla = toupper(tecla);

        if (tecla == 'W' || tecla == 'A' || tecla == 'S' || tecla == 'D') {
            //Calcula nueva posicion según tecla
            int nf = detective->fila;
            int nc = detective->columna;
            if      (tecla == 'W') nf--;
            else if (tecla == 'S') nf++;
            else if (tecla == 'A') nc--;
            else if (tecla == 'D') nc++;

            Ubicacion* destino = mapa.getNodo(nf, nc);

            if (destino->tipo == TipoCelda::EDIFICIO) {
                cout << "No puedes salir del mapa.\n";
            } else if (destino->tipo == TipoCelda::CALLEJON) {
                //Revela el callejon pero no mueve al detective (punto 9)
                destino->callejonVisible = true;
                cout << "Hay un callejon cerrado, no puedes pasar.\n";
                detective->sumarMovimiento();
            } else {
                //Movimiento válido
                detective->mover(nf, nc);
                detective->sumarMovimiento();
                procesarCelda();
            }

        } else if (tecla == 'T') {
            //Muestra pila de pistas (punto 13)
            detective->mostrarPilas();

        } else if (tecla == 'Q') {
            //Muestra tabla hash de sospechosos (punto 16)
            mostrarSospechosos();

        } else if (tecla == 'I') {
            //Interroga al siguiente testigo de la cola (punto 17)
            if (!colaTestigos.empty()) {
                Testigo t = colaTestigos.front();
                colaTestigos.pop();
                cout << "\nTestigo dice: " << t.getDeclaracion() << "\n";
                //Revela un atributo adicional del culpable
                Sospechoso& culpable = tablaSospechosos[nombreCulpable];
                if (indiceAtributoRevelado < (int)culpable.atributos.size()) {
                    string attr = culpable.revelarAtributo(indiceAtributoRevelado);
                    cout << "Dato adicional del culpable: " << attr << "\n";
                    indiceAtributoRevelado++;
                }
            } else {
                cout << "No hay testigos en la cola.\n";
            }

        } else if (tecla == 'X') {
            //Usa la última pista de la pila (punto 14)
            if (detective->tienePistas()) {
                Pista p = detective->usarPista();
                aplicarEfectoPista(p);
            } else {
                cout << "No tienes pistas para usar.\n";
            }
        }
    }

    //Fase de acusacion al recoger las 10 pistas
    faseAcusacion();

    //Muestra historial final
    cout << "\n";
    historial.mostrarHistorial();
}