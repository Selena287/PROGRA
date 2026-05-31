#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "Student.h"

using namespace std;

struct HashNode {
    Student data;
    HashNode* next;
};

class HashTable {
private:
    HashNode** table;
    int size;
    int count;

public:
    int collisions;

    HashTable(int s = 50) {
        size = s;
        count = 0;
        collisions = 0;

        table = new HashNode*[size];

        for (int i = 0; i < size; i++)
            table[i] = nullptr;
    }

    int hashFunction(int id) {
        return id % size;
    }

    // INSERTAR
    void insert(Student s) {
        int index = hashFunction(s.student_id);

        HashNode* temp = table[index];

        // validar duplicado
        while (temp != nullptr) {
            if (temp->data.student_id == s.student_id) {
                cout << " ID duplicado\n";
                return;
            }
            temp = temp->next;
        }

        if (table[index] != nullptr)
            collisions++;

        HashNode* newNode = new HashNode;
        newNode->data = s;
        newNode->next = table[index];
        table[index] = newNode;

        count++;

        cout << " Estudiante insertado\n";
    }

    // BUSCAR
    Student* search(int id) {
        int index = hashFunction(id);

        HashNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->data.student_id == id)
                return &(temp->data);
            temp = temp->next;
        }

        return nullptr;
    }

    // ELIMINAR
    bool remove(int id) {
        int index = hashFunction(id);

        HashNode* temp = table[index];
        HashNode* prev = nullptr;

        while (temp != nullptr) {
            if (temp->data.student_id == id) {

                if (prev == nullptr)
                    table[index] = temp->next;
                else
                    prev->next = temp->next;

                delete temp;
                count--;

                cout << " Estudiante eliminado\n";
                return true;
            }

            prev = temp;
            temp = temp->next;
        }

        cout << " Estudiante no encontrado\n";
        return false;
    }

    // FACTOR DE CARGA
    float loadFactor() {
        return (float)count / size;
    }

    int getCount() {
        return count;
    }

    void showStats() {
        cout << "\n HASH TABLE STATS\n";
        cout << "Total estudiantes: " << count << endl;
        cout << "Colisiones: " << collisions << endl;
        cout << "Factor de carga: " << loadFactor() << endl;
    }
};

#endif