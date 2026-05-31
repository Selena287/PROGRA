#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

struct Request {
    int from_id;
    int to_id;
};

struct QueueNode {
    Request data;
    QueueNode* next;
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    int total;

public:
    Queue() {
        front = nullptr;
        rear = nullptr;
        total = 0;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void enqueue(Request r) {
        QueueNode* newNode = new QueueNode;
        newNode->data = r;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }

        total++;
        cout << "Solicitud agregada a la cola\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "No hay solicitudes pendientes\n";
            return;
        }

        QueueNode* temp = front;
        cout << "Procesando solicitud: "
             << temp->data.from_id << " -> "
             << temp->data.to_id << endl;

        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        delete temp;
        total--;
    }

    void show() {
        if (isEmpty()) {
            cout << "Cola vacia\n";
            return;
        }

        QueueNode* temp = front;

        cout << "Solicitudes pendientes:\n";
        while (temp != nullptr) {
            cout << temp->data.from_id << " -> " << temp->data.to_id << endl;
            temp = temp->next;
        }
    }

    int getTotal() {
        return total;
    }
};

#endif