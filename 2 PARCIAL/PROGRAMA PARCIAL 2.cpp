#include <iostream> // MAURA SELENA VELASQUEZ ORTEGA
#include <cstring>  // CARNE: 9941-24-14056
using namespace std;

// DEFINICIÓN DE ESTRUCTURAS DE DATOS

struct ElementoBase {
    int info;
    ElementoBase* sig;
};

struct NodoStack {
    int valor;
    NodoStack* debajo;
};

struct NodoQueue {
    int dato;
    NodoQueue* prox;
};

struct NodoRegistro {
    int cantidad;
    char categoria[30];
    int correlativo;
    NodoRegistro* previo;
    NodoRegistro* siguiente;
};

struct NodoArbol {
    int clave;
    NodoArbol* izq;
    NodoArbol* der;
};


// PUNTEROS Y CONTADORES GLOBALES


NodoStack* ptrTope = NULL;

NodoQueue* ptrInicioCola = NULL;
NodoQueue* ptrFinCola = NULL;

ElementoBase* cabeceraNegativos = NULL;

NodoRegistro* listaDobleInicio = NULL;
NodoRegistro* listaDobleFin = NULL;

NodoArbol* raizPrincipalBST = NULL;

ElementoBase* auxListaStack = NULL;
ElementoBase* auxListaQueue = NULL;

int cuentaParesPos = 0;
int cuentaImparesPos = 0;
int cuentaValoresNegativos = 0;
int cuentaNulos = 0;
int acumuladoValidos = 0;
int indiceEntrada = 0;

int valorMaximo = 0;
int valorMinimo = 0;
bool existenDatos = false;


// GESTIÓN DE PILA (STACK)


void pushStack(int n) {
    NodoStack* temporal = new NodoStack();
    temporal->valor = n;
    temporal->debajo = ptrTope;
    ptrTope = temporal;
}

bool popStack(int &n) {
    if (ptrTope == NULL) {
        return false;
    }

    NodoStack* borrar = ptrTope;
    n = borrar->valor;
    ptrTope = ptrTope->debajo;
    delete borrar;

    return true;
}

void imprimirPila() {
    if (ptrTope == NULL) {
        cout << "\nLa pila esta vacia.\n";
        return;
    }

    NodoStack* aux = ptrTope;
    cout << "\nContenido de la PILA:\n";
    while (aux != NULL) {
        cout << aux->valor << endl;
        aux = aux->debajo;
    }
}


// GESTIÓN DE COLA (QUEUE)


void enqueue(int n) {
    NodoQueue* temp = new NodoQueue();
    temp->dato = n;
    temp->prox = NULL;

    if (ptrInicioCola == NULL) {
        ptrInicioCola = temp;
        ptrFinCola = temp;
    } else {
        ptrFinCola->prox = temp;
        ptrFinCola = temp;
    }
}

bool dequeue(int &n) {
    if (ptrInicioCola == NULL) {
        return false;
    }

    NodoQueue* borrar = ptrInicioCola;
    n = borrar->dato;
    ptrInicioCola = ptrInicioCola->prox;

    if (ptrInicioCola == NULL) {
        ptrFinCola = NULL;
    }

    delete borrar;
    return true;
}

void imprimirCola() {
    if (ptrInicioCola == NULL) {
        cout << "\nLa cola esta vacia.\n";
        return;
    }

    NodoQueue* aux = ptrInicioCola;
    cout << "\nContenido de la COLA:\n";
    while (aux != NULL) {
        cout << aux->dato << " ";
        aux = aux->prox;
    }
    cout << endl;
}


// LISTA ENLAZADA SIMPLE


void agregarListaSimple(ElementoBase* &punteroRaiz, int n) {
    ElementoBase* nuevoNodo = new ElementoBase();
    nuevoNodo->info = n;
    nuevoNodo->sig = NULL;

    if (punteroRaiz == NULL) {
        punteroRaiz = nuevoNodo;
    } else {
        ElementoBase* recorrido = punteroRaiz;
        while (recorrido->sig != NULL) {
            recorrido = recorrido->sig;
        }
        recorrido->sig = nuevoNodo;
    }
}

void visualizarListaSimple(ElementoBase* punteroRaiz, const char titulo[]) {
    if (punteroRaiz == NULL) {
        cout << "\n" << titulo << " esta vacia.\n";
        return;
    }

    ElementoBase* actual = punteroRaiz;
    cout << "\n" << titulo << ":\n";
    while (actual != NULL) {
        cout << actual->info << " ";
        actual = actual->sig;
    }
    cout << endl;
}

int purgarNegativosRango() {
    int contadorBajas = 0;

    while (cabeceraNegativos != NULL && cabeceraNegativos->info > -10 && cabeceraNegativos->info < 0) {
        ElementoBase* borrar = cabeceraNegativos;
        cabeceraNegativos = cabeceraNegativos->sig;
        delete borrar;
        contadorBajas++;
    }

    ElementoBase* cursor = cabeceraNegativos;
    while (cursor != NULL && cursor->sig != NULL) {
        if (cursor->sig->info > -10 && cursor->sig->info < 0) {
            ElementoBase* borrar = cursor->sig;
            cursor->sig = borrar->sig;
            delete borrar;
            contadorBajas++;
        } else {
            cursor = cursor->sig;
        }
    }
    return contadorBajas;
}


// LISTA DOBLEMENTE ENLAZADA (HISTORIAL)


void registrarEnLog(int v, const char etiqueta[]) {
    NodoRegistro* entrada = new NodoRegistro();
    entrada->cantidad = v;
    strcpy(entrada->categoria, etiqueta);
    entrada->correlativo = indiceEntrada;
    entrada->previo = NULL;
    entrada->siguiente = NULL;

    if (listaDobleInicio == NULL) {
        listaDobleInicio = entrada;
        listaDobleFin = entrada;
    } else {
        listaDobleFin->siguiente = entrada;
        entrada->previo = listaDobleFin;
        listaDobleFin = entrada;
    }
}

void mostrarBitacora() {
    if (listaDobleInicio == NULL) {
        cout << "\nEl historial esta vacio.\n";
        return;
    }

    NodoRegistro* aux = listaDobleInicio;
    cout << "\nHISTORIAL DE VALORES VALIDOS:\n";
    cout << "ID\tValor\tEstructura\n";

    while (aux != NULL) {
        cout << aux->correlativo << "\t" << aux->cantidad << "\t" << aux->categoria << endl;
        aux = aux->siguiente;
    }
}


// ÁRBOL BINARIO DE BÚSQUEDA (BST)


NodoArbol* crearHoja(int v) {
    NodoArbol* nuevo = new NodoArbol();
    nuevo->clave = v;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

NodoArbol* insertarEnArbol(NodoArbol* nodoActual, int v) {
    if (nodoActual == NULL) {
        return crearHoja(v);
    }

    if (v < nodoActual->clave) {
        nodoActual->izq = insertarEnArbol(nodoActual->izq, v);
    } else {
        nodoActual->der = insertarEnArbol(nodoActual->der, v);
    }
    return nodoActual;
}

void recorridoIn(NodoArbol* nodoActual) {
    if (nodoActual != NULL) {
        recorridoIn(nodoActual->izq);
        cout << nodoActual->clave << " ";
        recorridoIn(nodoActual->der);
    }
}

void recorridoPre(NodoArbol* nodoActual) {
    if (nodoActual != NULL) {
        cout << nodoActual->clave << " ";
        recorridoPre(nodoActual->izq);
        recorridoPre(nodoActual->der);
    }
}

void recorridoPost(NodoArbol* nodoActual) {
    if (nodoActual != NULL) {
        recorridoPost(nodoActual->izq);
        recorridoPost(nodoActual->der);
        cout << nodoActual->clave << " ";
    }
}

bool encontrarEnBST(NodoArbol* nodoActual, int v) {
    if (nodoActual == NULL) return false;
    if (v == nodoActual->clave) return true;

    if (v < nodoActual->clave)
        return encontrarEnBST(nodoActual->izq, v);
    else
        return encontrarEnBST(nodoActual->der, v);
}

void vaciarArbol(NodoArbol* &nodoActual) {
    if (nodoActual != NULL) {
        vaciarArbol(nodoActual->izq);
        vaciarArbol(nodoActual->der);
        delete nodoActual;
        nodoActual = NULL;
    }
}

void generarArbolDesdeLog() {
    vaciarArbol(raizPrincipalBST);
    NodoRegistro* aux = listaDobleInicio;

    while (aux != NULL) {
        if (aux->cantidad > 0) {
            raizPrincipalBST = insertarEnArbol(raizPrincipalBST, aux->cantidad);
        }
        aux = aux->siguiente;
    }

    if (raizPrincipalBST == NULL) {
        cout << "\nNo hay numeros positivos para construir el BST.\n";
        return;
    }

    cout << "\nARBOL BST CONSTRUIDO CORRECTAMENTE.\n";
    cout << "\nInOrden: "; recorridoIn(raizPrincipalBST);
    cout << "\nPreOrden: "; recorridoPre(raizPrincipalBST);
    cout << "\nPostOrden: "; recorridoPost(raizPrincipalBST);
    cout << endl;
}


// ESTADÍSTICAS Y PROCESAMIENTO


void revisarLimites(int v) {
    if (!existenDatos) {
        valorMaximo = v;
        valorMinimo = v;
        existenDatos = true;
    } else {
        if (v > valorMaximo) valorMaximo = v;
        if (v < valorMinimo) valorMinimo = v;
    }
}

void reporteEstadistico() {
    cout << "\nESTADISTICAS DEL SISTEMA\n";
    cout << "Pares positivos: " << cuentaParesPos << endl;
    cout << "Impares positivos: " << cuentaImparesPos << endl;
    cout << "Negativos: " << cuentaValoresNegativos << endl;
    cout << "Ceros rechazados: " << cuentaNulos << endl;
    cout << "Total de valores validos: " << acumuladoValidos << endl;

    if (existenDatos) {
        cout << "Mayor valor ingresado: " << valorMaximo << endl;
        cout << "Menor valor ingresado: " << valorMinimo << endl;
    } else {
        cout << "No hay valores validos ingresados.\n";
    }
}

void capturaDeDatos() {
    int limite, num;
    cout << "\nCuantos numeros desea ingresar? ";
    cin >> limite;

    while (limite <= 0) {
        cout << "Error. N debe ser mayor que 0: ";
        cin >> limite;
    }

    for (int i = 1; i <= limite; i++) {
        cout << "Ingrese el numero " << i << ": ";
        cin >> num;

        if (num == 0) {
            cuentaNulos++;
            cout << "El cero no se almacena.\n";
        } else {
            indiceEntrada++;
            acumuladoValidos++;
            revisarLimites(num);

            if (num > 0 && num % 2 == 0) {
                enqueue(num);
                registrarEnLog(num, "COLA");
                cuentaParesPos++;
                cout << "Numero par positivo enviado a COLA.\n";
            } else if (num > 0 && num % 2 != 0) {
                pushStack(num);
                registrarEnLog(num, "PILA");
                cuentaImparesPos++;
                cout << "Numero impar positivo enviado a PILA.\n";
            } else if (num < 0) {
                agregarListaSimple(cabeceraNegativos, num);
                registrarEnLog(num, "LISTA SIMPLE");
                cuentaValoresNegativos++;
                cout << "Numero negativo enviado a LISTA SIMPLE.\n";
            }
        }
    }
}


// REORGANIZACIÓN FINAL


void limpiarListaSimple(ElementoBase* &punteroRaiz) {
    while (punteroRaiz != NULL) {
        ElementoBase* borrar = punteroRaiz;
        punteroRaiz = punteroRaiz->sig;
        delete borrar;
    }
}

void rehacerArbolDesdeListas() {
    vaciarArbol(raizPrincipalBST);
    ElementoBase* actual = auxListaStack;
    while (actual != NULL) {
        raizPrincipalBST = insertarEnArbol(raizPrincipalBST, actual->info);
        actual = actual->sig;
    }
    actual = auxListaQueue;
    while (actual != NULL) {
        raizPrincipalBST = insertarEnArbol(raizPrincipalBST, actual->info);
        actual = actual->sig;
    }
}

void trasvasarEstructuras() {
    int valorExtraido;
    limpiarListaSimple(auxListaStack);
    limpiarListaSimple(auxListaQueue);

    while (popStack(valorExtraido)) {
        agregarListaSimple(auxListaStack, valorExtraido);
    }
    while (dequeue(valorExtraido)) {
        agregarListaSimple(auxListaQueue, valorExtraido);
    }

    cout << "\nPila y Cola vaciadas a listas auxiliares.\n";
    visualizarListaSimple(auxListaStack, "LISTA AUXILIAR DE PILA");
    visualizarListaSimple(auxListaQueue, "LISTA AUXILIAR DE COLA");

    rehacerArbolDesdeListas();

    if (raizPrincipalBST != NULL) {
        cout << "\nBST reconstruido con datos reorganizados.\n";
        cout << "InOrden: "; recorridoIn(raizPrincipalBST);
        cout << "\nPreOrden: "; recorridoPre(raizPrincipalBST);
        cout << "\nPostOrden: "; recorridoPost(raizPrincipalBST);
        cout << endl;
    }
}


// LIMPIEZA TOTAL


void purgaFinal() {
    int dummy;
    while (popStack(dummy));
    while (dequeue(dummy));
    limpiarListaSimple(cabeceraNegativos);
    limpiarListaSimple(auxListaStack);
    limpiarListaSimple(auxListaQueue);
    
    while (listaDobleInicio != NULL) {
        NodoRegistro* b = listaDobleInicio;
        listaDobleInicio = listaDobleInicio->siguiente;
        delete b;
    }
    vaciarArbol(raizPrincipalBST);
}


// INTERFAZ


void menuPrincipal() {
    cout << "\n=====================================\n";
    cout << " SISTEMA DE ESTRUCTURAS DINAMICAS\n";
    cout << " Selena Velasquez\n";
    cout << " Carnet: 9941-24-14056\n";
    cout << "=====================================\n";
    cout << "1. Ingresar N numeros\n";
    cout << "2. Mostrar pila\n";
    cout << "3. Mostrar cola\n";
    cout << "4. Mostrar lista de negativos\n";
    cout << "5. Mostrar historial lista doble\n";
    cout << "6. Construir y mostrar BST\n";
    cout << "7. Eliminar negativos (magnitud < 10)\n";
    cout << "8. Buscar un valor en el BST\n";
    cout << "9. Mostrar estadisticas\n";
    cout << "10. Reorganizar estructuras\n";
    cout << "11. Salir\n";
    cout << "Seleccione una opcion: ";
}

int main() {
    int selector;
    bool finalizar = false;

    do {
        menuPrincipal();
        cin >> selector;

        switch (selector) {
            case 1: capturaDeDatos(); break;
            case 2: imprimirPila(); break;
            case 3: imprimirCola(); break;
            case 4: visualizarListaSimple(cabeceraNegativos, "LISTA DE NEGATIVOS"); break;
            case 5: mostrarBitacora(); break;
            case 6: generarArbolDesdeLog(); break;
            case 7: {
                int eliminados = purgarNegativosRango();
                cout << "\nNodos eliminados: " << eliminados << endl;
                break;
            }
            case 8: {
                int buscar;
                cout << "Valor a buscar: "; cin >> buscar;
                if(encontrarEnBST(raizPrincipalBST, buscar)) cout << "Existe.\n";
                else cout << "No existe.\n";
                break;
            }
            case 9: reporteEstadistico(); break;
            case 10: trasvasarEstructuras(); break;
            case 11:
                purgaFinal();
                finalizar = true;
                break;
            default: cout << "Opcion no valida.\n";
        }
    } while (!finalizar);

    return 0;
}
