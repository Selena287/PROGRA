#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

struct AdjNode {
    int student_id;
    AdjNode* next;
};

struct GraphNode {
    int student_id;
    AdjNode* adjList;
    GraphNode* next;
};

class Graph {
private:
    GraphNode* head;

    GraphNode* findNode(int id) {
        GraphNode* temp = head;
        while (temp != nullptr) {
            if (temp->student_id == id)
                return temp;
            temp = temp->next;
        }
        return nullptr;
    }

    bool connectionExists(GraphNode* node, int id) {
        AdjNode* temp = node->adjList;
        while (temp != nullptr) {
            if (temp->student_id == id)
                return true;
            temp = temp->next;
        }
        return false;
    }

public:
    int totalConnections;

    Graph() {
        head = nullptr;
        totalConnections = 0;
    }

    void addStudent(int id) {
        if (findNode(id) != nullptr)
            return;

        GraphNode* newNode = new GraphNode;
        newNode->student_id = id;
        newNode->adjList = nullptr;
        newNode->next = head;
        head = newNode;
    }

    void connect(int id1, int id2) {
        if (id1 == id2) {
            cout << "No se puede conectar consigo mismo\n";
            return;
        }

        GraphNode* n1 = findNode(id1);
        GraphNode* n2 = findNode(id2);

        if (n1 == nullptr || n2 == nullptr) {
            cout << "Uno o ambos estudiantes no existen\n";
            return;
        }

        if (connectionExists(n1, id2)) {
            cout << "Conexion duplicada\n";
            return;
        }

        AdjNode* a1 = new AdjNode{id2, n1->adjList};
        n1->adjList = a1;

        AdjNode* a2 = new AdjNode{id1, n2->adjList};
        n2->adjList = a2;

        totalConnections++;
        cout << "Conexion creada\n";
    }

    void showConnections(int id) {
        GraphNode* node = findNode(id);

        if (node == nullptr) {
            cout << "Estudiante no encontrado\n";
            return;
        }

        AdjNode* temp = node->adjList;

        cout << "Conexiones de " << id << ": ";
        while (temp != nullptr) {
            cout << temp->student_id << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool areConnected(int id1, int id2) {
        GraphNode* n1 = findNode(id1);
        if (n1 == nullptr) return false;

        return connectionExists(n1, id2);
    }


    void BFS(int start) {
        GraphNode* node = findNode(start);

        if (node == nullptr) {
            cout << "Nodo no encontrado\n";
            return;
        }

        int visited[1000] = {0};

        int queue[1000];
        int front = 0, rear = 0;

        queue[rear++] = start;
        visited[start] = 1;

        while (front < rear) {
            int current = queue[front++];
            cout << current << " ";

            GraphNode* currNode = findNode(current);
            AdjNode* temp = currNode->adjList;

            while (temp != nullptr) {
                if (!visited[temp->student_id]) {
                    visited[temp->student_id] = 1;
                    queue[rear++] = temp->student_id;
                }
                temp = temp->next;
            }
        }

        cout << endl;
    }


    void DFSUtil(int id, int visited[]) {
        visited[id] = 1;
        cout << id << " ";

        GraphNode* node = findNode(id);
        AdjNode* temp = node->adjList;

        while (temp != nullptr) {
            if (!visited[temp->student_id]) {
                DFSUtil(temp->student_id, visited);
            }
            temp = temp->next;
        }
    }

    void DFS(int start) {
        int visited[1000] = {0};

        if (findNode(start) == nullptr) {
            cout << "Nodo no encontrado\n";
            return;
        }

        DFSUtil(start, visited);
        cout << endl;
    }
};

#endif