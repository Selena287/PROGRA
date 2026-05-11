#include <iostream>
#include <limits>
#include "AVL.h"


using namespace std;

void cleanInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Student readStudentFromKeyboard() {
    Student student;

    cout << "\n INGRESAR ESTUDIANTE \n";

    cout << "ID DEL ESTUDIANTE: ";
    cin >> student.student_id;
    cleanInputBuffer();

    cout << "NOMBRE COMPLETO: ";
    getline(cin, student.full_name);

    cout << "CARRERA: ";
    getline(cin, student.career);

    cout << "SEMESTRE: ";
    cin >> student.semester;

    cout << "GPA: ";
    cin >> student.gpa;

    cout << "SKILL SCORE: ";
    cin >> student.skill_score;

    return student;
}

void showFoundStudent(const Student& student) {
    cout << "\n ESTUDIANTE :\n";
    cout << "ID: " << student.student_id << endl;
    cout << "NOMBRE COMPLETO: " << student.full_name << endl;
    cout << "CARRERA: " << student.career << endl;
    cout << "SEMESTRE: " << student.semester << endl;
    cout << "GPA: " << student.gpa << endl;
    cout << "SKILL SCORE: " << student.skill_score << endl;
}

int main() {
    AVL academicRanking;
    int option;

    do {

        cout << " RANKING ACADEMICO - AVL\n";
       cout << "MAURA SELENA VELASQUEZ ORTEGA\n";
        cout << "1. INGRESAR ESTUDIANTE\n";
        cout << "2. MOSTRAR RANKING\n";
        cout << "3. BUSCAR POR SKILL_SCORE\n";
        cout << "4. MOSTRAR ESTADISTICAS AVL\n";
        cout << "5. SALIR\n";
        cout << "ESCOJA UNA OPCION: ";
        cin >> option;

        switch (option) {
            case 1: {
                Student student = readStudentFromKeyboard();
                academicRanking.insertStudent(student);
                cout << "\n SE INSERTO ESTUDIANTE CORRECTAMENTE EN ARBOL AVL.\n";
                break;
            }

            case 2: {
                academicRanking.showRanking();
                break;
            }

            case 3: {
                int skillScore;
                Student result;

                cout << "\n INGRESE skill_score QUE DESEA ENCONTRAR: ";
                cin >> skillScore;

                if (academicRanking.findBySkillScore(skillScore, result)) {
                    showFoundStudent(result);
                } else {
                    cout << "\n NO HAY NINGUN REGISTRO DE ESTUDIANTE EN SKILL.SCORE\n";
                }
                break;
            }

            case 4: {
                academicRanking.showStatistics();
                break;
            }

            case 5: {
                cout << "\n SALIENDO DEL PROGRAMA...\n";
                break;
            }

            default: {
                cout << "\nOPCION INCORRECTA. INGRESE OPCION NUEVAMENTE\n";
                break;
            }
        }

    } while (option != 5);

    return 0;
}



