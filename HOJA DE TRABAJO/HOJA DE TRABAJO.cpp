#include <iostream> //MAURA SELENA VELASQUEZ ORTEGA
using namespace std;//CARNE: 9941-24-14056

// Definición del nodo
struct Nodo {
    int dato;
    Nodo* siguiente;
};

// Puntero al tope de la pila
Nodo* tope = NULL;

// PUSH: insertar elemento en la pila
void push(int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = tope;
    tope = nuevo;

    cout << "Elemento " << valor << " insertado en la pila." << endl;
}

// POP: eliminar elemento del tope
void pop() {
    if (tope == NULL) {
        cout << "La pila esta vacia. No se puede eliminar." << endl;
        return;
    }

    Nodo* temp = tope;
    cout << "Elemento eliminado: " << temp->dato << endl;

    tope = tope->siguiente;
    delete temp;
}

// PEEK: ver el elemento en el tope
void peek() {
    if (tope == NULL) {
        cout << "La pila esta vacia." << endl;
    } else {
        cout << "Elemento en el tope: " << tope->dato << endl;
    }
}

// Mostrar toda la pila
void mostrar() {
    if (tope == NULL) {
        cout << "La pila esta vacia." << endl;
        return;
    }

    Nodo* actual = tope;
    cout << "Contenido de la pila (tope -> base): ";

    while (actual != NULL) {
        cout << actual->dato << " -> ";
        actual = actual->siguiente;
            cout << "NULL" << endl;
    }
}

    // Contar elementos
int contarElementos(Nodo* tope) {
    int contador = 0;
    Nodo* actual = tope;

    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }

    return contador;
}

// Buscar elemento
void buscarElemento(Nodo* tope, int valor) {
    if (tope == NULL) {
        cout << "Error: La pila esta vacia.\n";
        return;
    }

    Nodo* actual = tope;
    int posicion = 1;
    bool encontrado = false;

    while (actual != NULL) {
        if (actual->dato == valor) {
            cout << "Elemento encontrado en la posicion: " << posicion << endl;
            encontrado = true;
        }
        actual = actual->siguiente;
        posicion++;
    }

    if (!encontrado) {
        cout << "Elemento no encontrado.\n";
    }
}

// Vaciar pila
void vaciarPila(Nodo*& tope) {
    if (tope == NULL) {
        cout << "La pila ya esta vacia.\n";
        return;
    }

    while (tope != NULL) {
        Nodo* aux = tope;
        tope = tope->siguiente;
        delete aux;
    }

    cout << "Pila vaciada correctamente.\n";
}

// Programa principal
int main() {
    int opcion, valor;

    do {
        cout << "\n===== MENU PILA =====" << endl;
        cout << "1. Push (Insertar)" << endl;
        cout << "2. Pop (Eliminar)" << endl;
        cout << "3. Peek (Ver tope)" << endl;
        cout << "4. Mostrar pila" << endl;
         cout << "5. Contar elementos\n";
        cout << "6. Buscar elemento\n";
            cout << "7. Vaciar pila\n";
        cout << "8. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese valor: ";
                cin >> valor;
                push(valor);
                break;
            case 2:
                pop();
                break;
            case 3:
                peek();
                break;
            case 4:
                mostrar();
                break;
                
            case 5:
                cout << "Cantidad de elementos: " << contarElementos(tope) << endl;
                break;

            case 6:
                cout << "Ingrese valor a buscar: ";
                cin >> valor;
                buscarElemento(tope, valor);
                break;

            case 7:
                vaciarPila(tope);
                break;

            case 8:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }

    } while (opcion != 8);

    return 0;
}
