#include <iostream>//MAURA SELENA VELASQUEZ ORTEGA
using namespace std;//9941-24-14056

struct Estudiante
{
    int carne;
    string nombre;
    string apellido;
    string carrera;
    Estudiante* siguiente;
};

// VALIDAR SI EXISTE CARNÉ
bool existeCarne(Estudiante* cabeza, int carne)
{
    while(cabeza != NULL)
    {
        if(cabeza->carne == carne)
        {
            return true;
        }
        cabeza = cabeza->siguiente;
    }
    return false;
}

// INSERTAR AL INICIO
void insertarInicio(Estudiante*& cabeza)
{
    Estudiante* nuevo = new Estudiante();

    cout << "\nDigite codigo: ";
    cin >> nuevo->carne;
    cin.ignore();

    if(existeCarne(cabeza, nuevo->carne))
    {
        cout << "Advertencia: el codigo ya esta registrado.\n";
        delete nuevo;
        return;
    }

    cout << "Digite nombres: ";
    getline(cin, nuevo->nombre);

    cout << "Digite apellidos: ";
    getline(cin, nuevo->apellido);

    cout << "Digite facultad: ";
    getline(cin, nuevo->carrera);

    nuevo->siguiente = cabeza;
    cabeza = nuevo;

    cout << "Registro agregado al principio correctamente.\n";
}

// INSERTAR AL FINAL
void insertarFinal(Estudiante*& cabeza)
{
    Estudiante* nuevo = new Estudiante();

    cout << "\nDigite codigo: ";
    cin >> nuevo->carne;
    cin.ignore();

    if(existeCarne(cabeza, nuevo->carne))
    {
        cout << "Advertencia: el codigo ya esta registrado.\n";
        delete nuevo;
        return;
    }

    cout << "Digite nombres: ";
    getline(cin, nuevo->nombre);

    cout << "Digite apellidos: ";
    getline(cin, nuevo->apellido);

    cout << "Digite facultad: ";
    getline(cin, nuevo->carrera);

    nuevo->siguiente = NULL;

    if(cabeza == NULL)
    {
        cabeza = nuevo;
    }
    else
    {
        Estudiante* temp = cabeza;
        while(temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevo;
    }

    cout << "Registro agregado al final correctamente.\n";
}

// MOSTRAR ESTUDIANTES
void mostrar(Estudiante* cabeza)
{
    if(cabeza == NULL)
    {
        cout << "\nLista vacia.\n";
        return;
    }

    int contador = 0;
    Estudiante* temp = cabeza;

    cout << "\n--- LISTA DE REGISTROS ---\n";

    while(temp != NULL)
    {
        cout << "Codigo: " << temp->carne << endl;
        cout << "Nombres: " << temp->nombre << endl;
        cout << "Apellidos: " << temp->apellido << endl;
        cout << "Facultad: " << temp->carrera << endl;
        cout << "-----------------------------\n";

        contador++;
        temp = temp->siguiente;
    }

    cout << "Total de registros: " << contador << endl;
}

// BUSCAR ESTUDIANTE
void buscar(Estudiante* cabeza)
{
    int carne;
    cout << "\nDigite codigo a buscar: ";
    cin >> carne;

    Estudiante* temp = cabeza;

    while(temp != NULL)
    {
        if(temp->carne == carne)
        {
            cout << "\nRegistro encontrado:\n";
            cout << "Nombres: " << temp->nombre << endl;
            cout << "Apellidos: " << temp->apellido << endl;
            cout << "Facultad: " << temp->carrera << endl;
            return;
        }
        temp = temp->siguiente;
    }

    cout << "Registro no encontrado.\n";
}

// ELIMINAR ESTUDIANTE
void eliminar(Estudiante*& cabeza)
{
    int carne;
    cout << "\nDigite codigo a eliminar: ";
    cin >> carne;

    Estudiante* temp = cabeza;
    Estudiante* anterior = NULL;

    while(temp != NULL)
    {
        if(temp->carne == carne)
        {
            if(temp == cabeza)
            {
                cabeza = cabeza->siguiente;
            }
            else
            {
                anterior->siguiente = temp->siguiente;
            }

            delete temp;
            cout << "Registro eliminado correctamente.\n";
            return;
        }

        anterior = temp;
        temp = temp->siguiente;
    }

    cout << "Registro no encontrado.\n";
}

// LIBERAR MEMORIA
void liberarMemoria(Estudiante*& cabeza)
{
    Estudiante* temp;

    while(cabeza != NULL)
    {
        temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }

    cout << "Memoria liberada correctamente.\n";
}

// MENÚ PRINCIPAL
int main()
{
    Estudiante* cabeza = NULL;
    int opcion;

    do
    {
    
        cout << "\n===== MENU =====\n";
        cout << "1. Agregar registro al inicio\n";
        cout << "2. Agregar registro al final\n";
        cout << "3. Mostrar todos los registros\n";
        cout << "4. Buscar registro\n";
        cout << "5. Eliminar registro\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch(opcion)
        {
            case 1:
                insertarInicio(cabeza);
                break;
            case 2:
                insertarFinal(cabeza);
                break;
            case 3:
                mostrar(cabeza);
                break;
            case 4:
                buscar(cabeza);
                break;
            case 5:
                eliminar(cabeza);
                break;
            case 6:
                liberarMemoria(cabeza);
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }

    } while(opcion != 6);

    return 0;
}


