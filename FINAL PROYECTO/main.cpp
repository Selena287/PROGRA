#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>

#include "HashTable.h"
#include "AVL.h"
#include "Graph.h"
#include "Queue.h"

using namespace std;


HashTable ht(100);
AVL avl;
Graph graph;
Queue requests;

int totalProjects = 0;
int totalConnections = 0;


void loadCSV() {
    ifstream file("students.csv");

    if (!file.is_open()) {
        cout << "Error al abrir archivo\n";
        return;
    }

    string line;
    getline(file, line);

    auto start = chrono::high_resolution_clock::now();

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Student s;

        getline(ss, temp, ','); s.student_id = stoi(temp);
        getline(ss, s.full_name, ',');
        getline(ss, s.career, ',');
        getline(ss, temp, ','); s.semester = stoi(temp);
        getline(ss, temp, ','); s.gpa = stof(temp);
        getline(ss, temp, ','); s.skill_score = stoi(temp);

        if (!ht.search(s.student_id)) {
            ht.insert(s);
            avl.insert(s);
            graph.addStudent(s.student_id);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(end - start).count();

    cout << "Datos cargados\n";
    cout << "Tiempo carga: " << time << " ms\n";

    file.close();
}


void registerStudent() {
    Student s;

    cout << "ID: ";
    cin >> s.student_id;

    if (ht.search(s.student_id)) {
        cout << "ID ya existe\n";
        return;
    }

    cin.ignore();
    cout << "Nombre: ";
    getline(cin, s.full_name);

    cout << "Carrera: ";
    getline(cin, s.career);

    cout << "Semestre: ";
    cin >> s.semester;

    cout << "GPA: ";
    cin >> s.gpa;

    cout << "Skill Score: ";
    cin >> s.skill_score;

    ht.insert(s);
    avl.insert(s);
    graph.addStudent(s.student_id);
}


void searchStudent() {
    int id;
    cout << "ID: ";
    cin >> id;

    Student* s = ht.search(id);

    if (s)
        cout << s->full_name << " | " << s->career << endl;
    else
        cout << "No encontrado\n";
}


void deleteStudent() {
    int id;
    cout << "ID: ";
    cin >> id;

    if (!ht.search(id)) {
        cout << "No existe\n";
        return;
    }

    ht.remove(id);
    cout << "Eliminado del sistema\n";
}


void addProject() {
    int id;
    cout << "ID estudiante: ";
    cin >> id;

    Student* s = ht.search(id);

    if (!s) {
        cout << "No existe\n";
        return;
    }

    Project p;

    cout << "Project ID: ";
    cin >> p.project_id;

    cin.ignore();
    cout << "Titulo: ";
    getline(cin, p.title);

    cout << "Descripcion: ";
    getline(cin, p.description);

    cout << "Year: ";
    cin >> p.year;

    s->projects.add(p);
    totalProjects++;
}

void showProjects() {
    int id;
    cout << "ID estudiante: ";
    cin >> id;

    Student* s = ht.search(id);

    if (!s) {
        cout << "No existe\n";
        return;
    }

    s->projects.show();
}


void connectStudents() {
    int a, b;
    cout << "ID1: ";
    cin >> a;
    cout << "ID2: ";
    cin >> b;

    if (!ht.search(a) || !ht.search(b)) {
        cout << "Uno no existe\n";
        return;
    }

    graph.connect(a, b);
    totalConnections++;
}

void checkConnection() {
    int a, b;
    cin >> a >> b;

    if (graph.areConnected(a, b))
        cout << "Si estan conectados\n";
    else
        cout << "No estan conectados\n";
}

void showConnections() {
    int id;
    cin >> id;
    graph.showConnections(id);
}

void runBFS() {
    int id;
    cin >> id;
    graph.BFS(id);
}

void runDFS() {
    int id;
    cin >> id;
    graph.DFS(id);
}


void showStats() {
    cout << "Total estudiantes: " << ht.getCount() << endl;
    cout << "Total conexiones: " << totalConnections << endl;
    cout << "Total proyectos: " << totalProjects << endl;
    cout << "Colisiones hash: " << ht.collisions << endl;
    cout << "Factor carga: " << ht.loadFactor() << endl;
    cout << "Altura AVL: " << avl.getHeight() << endl;
}


void benchmark() {
    ofstream file("cpp_results.csv");
    file << "language,operation,structure,records,time_ms\n";

    int n = 10000;

    HashTable ht_test(20000);

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        Student s = {i, "Test", "Sys", 1, 80, i};
        ht_test.insert(s);
    }

    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double, milli>(end - start).count();

    file << "C++,insert,HashTable," << n << "," << time << "\n";

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        ht_test.search(i);
    }
    end = chrono::high_resolution_clock::now();
    time = chrono::duration<double, milli>(end - start).count();

    file << "C++,search,HashTable," << n << "," << time << "\n";

    AVL avl_test;

    start = chrono::high_resolution_clock::now();
    for (int i = 0; i < n; i++) {
        Student s = {i, "Test", "Sys", 1, 80, i};
        avl_test.insert(s);
    }
    end = chrono::high_resolution_clock::now();
    time = chrono::duration<double, milli>(end - start).count();

    file << "C++,insert,AVL," << n << "," << time << "\n";

    start = chrono::high_resolution_clock::now();
    avl_test.showRanking();
    end = chrono::high_resolution_clock::now();
    time = chrono::duration<double, milli>(end - start).count();

    file << "C++,traversal,AVL," << n << "," << time << "\n";

    Graph g;
    for (int i = 0; i < n; i++) g.addStudent(i);
    for (int i = 0; i < n - 1; i++) g.connect(i, i + 1);

    start = chrono::high_resolution_clock::now();
    g.BFS(0);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration<double, milli>(end - start).count();

    file << "C++,bfs,Graph," << n << "," << time << "\n";

    start = chrono::high_resolution_clock::now();
    g.DFS(0);
    end = chrono::high_resolution_clock::now();
    time = chrono::duration<double, milli>(end - start).count();

    file << "C++,dfs,Graph," << n << "," << time << "\n";

    file.close();

    cout << "Benchmark generado\n";
}


int main() {

    int op;

    do {
        cout << "MAURA SELENA VELASQUEZ ORTEGA\n";
        cout << "CARNE: 9941-24-14056\n";
        cout << "\n1. Cargar CSV\n";

        cout << "2. Registrar estudiante\n";
        cout << "3. Buscar estudiante\n";
        cout << "4. Eliminar estudiante\n";
        cout << "5. Agregar proyecto\n";
        cout << "6. Mostrar proyectos\n";
        cout << "7. Conectar estudiantes\n";
        cout << "8. Verificar conexion\n";
        cout << "9. Mostrar conexiones\n";
        cout << "10. BFS\n";
        cout << "11. DFS\n";
        cout << "12. Ranking\n";
        cout << "13. Estadisticas\n";
        cout << "14. Benchmark\n";
        cout << "15. Salir\n";

        cin >> op;

        switch (op) {
            case 1: loadCSV(); break;
            case 2: registerStudent(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: addProject(); break;
            case 6: showProjects(); break;
            case 7: connectStudents(); break;
            case 8: checkConnection(); break;
            case 9: showConnections(); break;
            case 10: runBFS(); break;
            case 11: runDFS(); break;
            case 12: avl.showRanking(); break;
            case 13: showStats(); break;
            case 14: benchmark(); break;
        }

    } while (op != 15);

    return 0;
}