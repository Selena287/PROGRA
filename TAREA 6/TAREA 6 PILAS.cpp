#include <iostream> //MAURA SELENA VELASQUEZ ORTEGA
#include <string>   // CARNET: 9941-24-14056
using namespace std;

// Definición del elemento de la pila
struct Elemento {
    string dato;
    Elemento* sig;
};

// Vaciar completamente una pila
void vaciar(Elemento*& cima) {
    while (cima != NULL) {
        Elemento* temp = cima;
        cima = cima->sig;
        delete temp;
    }
}

// Insertar elemento (PUSH)
void insertar(Elemento*& cima, string valor) {
    Elemento* nuevoNodo = new Elemento;
    nuevoNodo->dato = valor;
    nuevoNodo->sig = cima;
    cima = nuevoNodo;
}

// Extraer elemento (POP)
bool extraer(Elemento*& cima, string& valor) {
    if (cima == NULL) return false;

    Elemento* temp = cima;
    valor = temp->dato;
    cima = cima->sig;
    delete temp;
    return true;
}

// Imprimir contenido de una pila
void imprimir(Elemento* cima, string titulo) {
    cout << "\n----------------------------------\n";
    cout << titulo << endl;
    cout << "----------------------------------\n";

    if (cima == NULL) {
        cout << "Sin elementos.\n";
        return;
    }

    Elemento* aux = cima;
    int i = 1;

    while (aux != NULL) {
        cout << i++ << ") " << aux->dato << endl;
        aux = aux->sig;
    }
}

// Mostrar ambas pilas
void verTodo(Elemento* pila1, Elemento* pila2) {
    imprimir(pila1, "Historial activo");
    imprimir(pila2, "Historial de rehacer");
}

// Programa principal
int main() {
    Elemento* historial = NULL;
    Elemento* recuperacion = NULL;

    int opcionMenu;
    string textoIngresado, temporal;

    cout << "*************\n";
    cout << "   SISTEMA DE CONTROL DE ACCIONES\n";
    cout << "*************\n";

    do {
        cout << "\n------ OPCIONES ------\n";
        cout << "1) Nueva accion\n";
        cout << "2) Deshacer\n";
        cout << "3) Rehacer\n";
        cout << "4) Ver historial\n";
        cout << "5) Ver rehacer\n";
        cout << "6) Ver todo\n";
        cout << "7) Terminar\n";
        cout << "Elige: ";
        cin >> opcionMenu;
        cin.ignore();

        switch (opcionMenu) {

        case 1:
            cout << "Describe la accion: ";
            getline(cin, textoIngresado);

            insertar(historial, textoIngresado);
            vaciar(recuperacion);

            cout << "Accion guardada.\n";
            break;

        case 2:
            if (extraer(historial, temporal)) {
                insertar(recuperacion, temporal);
                cout << "Se deshizo: " << temporal << endl;
            } else {
                cout << "Nada que deshacer.\n";
            }
            break;

        case 3:
            if (extraer(recuperacion, temporal)) {
                insertar(historial, temporal);
                cout << "Se recupero: " << temporal << endl;
            } else {
                cout << "Nada que rehacer.\n";
            }
            break;

        case 4:
            imprimir(historial, "Acciones actuales");
            break;

        case 5:
            imprimir(recuperacion, "Acciones deshechas");
            break;

        case 6:
            verTodo(historial, recuperacion);
            break;

        case 7:
            cout << "Cerrando programa...\n";
            break;

        default:
            cout << "Opcion incorrecta.\n";
        }

    } while (opcionMenu != 7);

    // Liberación de memoria
    vaciar(historial);
    vaciar(recuperacion);

    cout << "Memoria limpiada.\n";
    return 0;
}
