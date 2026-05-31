#ifndef PROJECTLIST_H
#define PROJECTLIST_H

#include <iostream>
using namespace std;

struct Project {
    int project_id;
    string title;
    string description;
    int year;
};

struct ProjectNode {
    Project data;
    ProjectNode* next;
};

class ProjectList {
private:
    ProjectNode* head;
    int total;

public:
    ProjectList() {
        head = nullptr;
        total = 0;
    }

    bool exists(int id) {
        ProjectNode* temp = head;
        while (temp != nullptr) {
            if (temp->data.project_id == id)
                return true;
            temp = temp->next;
        }
        return false;
    }

    void add(Project p) {
        if (exists(p.project_id)) {
            cout << " Proyecto duplicado\n";
            return;
        }

        ProjectNode* newNode = new ProjectNode;
        newNode->data = p;
        newNode->next = head;
        head = newNode;
        total++;

        cout << "Proyecto agregado\n";
    }

    void show() {
        if (!head) {
            cout << "No hay proyectos\n";
            return;
        }

        ProjectNode* temp = head;
        while (temp != nullptr) {
            cout << "ID: " << temp->data.project_id
                 << " | " << temp->data.title
                 << " | Year: " << temp->data.year << endl;
            temp = temp->next;
        }
    }

    ProjectNode* search(int id) {
        ProjectNode* temp = head;
        while (temp != nullptr) {
            if (temp->data.project_id == id)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    void remove(int id) {
        ProjectNode* temp = head;
        ProjectNode* prev = nullptr;

        while (temp != nullptr) {
            if (temp->data.project_id == id) {
                if (prev == nullptr)
                    head = temp->next;
                else
                    prev->next = temp->next;

                delete temp;
                total--;
                cout << " Proyecto eliminado\n";
                return;
            }
            prev = temp;
            temp = temp->next;
        }

        cout << "Proyecto no encontrado\n";
    }

    int getTotal() {
        return total;
    }
};

#endif