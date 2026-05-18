#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Student {

    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;
};

struct Nodo {

    Student dato;
    Nodo* siguiente;
};

class TablaHash {

private:

    Nodo** tabla;
    int tamanio;

public:

    int cantidad;
    int colisiones;

    TablaHash(int t) {

        tamanio = t;
        cantidad = 0;
        colisiones = 0;

        tabla = new Nodo*[tamanio];

        for (int i = 0; i < tamanio; i++) {

            tabla[i] = NULL;
        }
    }

    int funcionHash(int id) {

        return id % tamanio;
    }

    bool existe(int id) {

        int indice = funcionHash(id);

        Nodo* aux = tabla[indice];

        while (aux != NULL) {

            if (aux->dato.student_id == id) {

                return true;
            }

            aux = aux->siguiente;
        }

        return false;
    }

    void insertar(Student e) {

        if (existe(e.student_id)) {

            cout << "Estudiante duplicado\n";

            return;
        }

        int indice = funcionHash(e.student_id);

        Nodo* nuevo = new Nodo;

        nuevo->dato = e;
        nuevo->siguiente = NULL;

        if (tabla[indice] != NULL) {

            colisiones++;
        }

        nuevo->siguiente = tabla[indice];

        tabla[indice] = nuevo;

        cantidad++;

        cout << "Estudiante insertado\n";
    }

    void buscar(int id) {

        int indice = funcionHash(id);

        Nodo* aux = tabla[indice];

        while (aux != NULL) {

            if (aux->dato.student_id == id) {

                cout << "\n===== ESTUDIANTE ENCONTRADO =====\n";

                cout << "ID: " << aux->dato.student_id << endl;
                cout << "Nombre: " << aux->dato.full_name << endl;
                cout << "Carrera: " << aux->dato.career << endl;
                cout << "Semestre: " << aux->dato.semester << endl;
                cout << "GPA: " << aux->dato.gpa << endl;
                cout << "Skill Score: " << aux->dato.skill_score << endl;

                return;
            }

            aux = aux->siguiente;
        }

        cout << "Estudiante no encontrado\n";
    }

    void eliminar(int id) {

        int indice = funcionHash(id);

        Nodo* aux = tabla[indice];
        Nodo* anterior = NULL;

        while (aux != NULL) {

            if (aux->dato.student_id == id) {

                if (anterior == NULL) {

                    tabla[indice] = aux->siguiente;
                }

                else {

                    anterior->siguiente = aux->siguiente;
                }

                delete aux;

                cantidad--;

                cout << "Estudiante eliminado\n";

                return;
            }

            anterior = aux;
            aux = aux->siguiente;
        }

        cout << "Estudiante no encontrado\n";
    }

    void mostrarTabla() {

        cout << "\n===== TABLA HASH =====\n";

        for (int i = 0; i < tamanio; i++) {

            cout << "\nBucket " << i << ": ";

            Nodo* aux = tabla[i];

            while (aux != NULL) {

                cout << aux->dato.student_id << " -> ";

                aux = aux->siguiente;
            }

            cout << "NULL\n";
        }
    }

    void mostrarEstadisticas() {

        cout << "\n===== ESTADISTICAS =====\n";

        cout << "Cantidad de estudiantes: " << cantidad << endl;

        cout << "Colisiones generadas: " << colisiones << endl;

        float factor = (float)cantidad / tamanio;

        cout << "Factor de carga: " << factor << endl;
    }

    void cargarCSV(string nombreArchivo) {

        ifstream archivo(nombreArchivo);

        if (!archivo) {

            cout << "Error al abrir archivo\n";

            return;
        }

        string linea;

        getline(archivo, linea);

        while (getline(archivo, linea)) {

            stringstream ss(linea);

            string dato;

            Student e;

            getline(ss, dato, ',');
            e.student_id = stoi(dato);

            getline(ss, e.full_name, ',');

            getline(ss, e.career, ',');

            getline(ss, dato, ',');
            e.semester = stoi(dato);

            getline(ss, dato, ',');
            e.gpa = stof(dato);

            getline(ss, dato, ',');
            e.skill_score = stoi(dato);

            insertar(e);
        }

        archivo.close();

        cout << "Archivo CSV cargado correctamente\n";
    }
};

int main() {

    TablaHash tabla(10);

    int opcion;

    cout << "MAURA SELENA VELASQUEZ ORTEGA\n";
    cout << "CARNE: 9941-24-14056\n";

    do {

        cout << "\n===== MENU =====\n";

        cout << "1. Cargar archivo CSV\n";
        cout << "2. Buscar estudiante\n";
        cout << "3. Eliminar estudiante\n";
        cout << "4. Mostrar tabla hash\n";
        cout << "5. Mostrar estadisticas\n";
        cout << "6. Salir\n";

        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion) {

            case 1: {

                string archivo;

                cout << "Ingrese nombre del archivo CSV: ";
                cin >> archivo;

                tabla.cargarCSV(archivo);

                break;
            }

            case 2: {

                int id;

                cout << "Ingrese student_id: ";
                cin >> id;

                tabla.buscar(id);

                break;
            }

            case 3: {

                int id;

                cout << "Ingrese student_id: ";
                cin >> id;

                tabla.eliminar(id);

                break;
            }

            case 4:

                tabla.mostrarTabla();

                break;

            case 5:

                tabla.mostrarEstadisticas();

                break;

            case 6:

                cout << "Saliendo...\n";

                break;

            default:

                cout << "Opcion invalida\n";
        }

    } while (opcion != 6);

    return 0;
}