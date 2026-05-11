#ifndef AVL_H //MAURA SELENA VELASQUEZ ORTEGA
//CARNE:9941-24-14056
#define AVL_H

#include "Student.h"
#include <iostream>
using namespace std;

class AVL {
private:
    struct Node {
        Student student;
        Node* left;
        Node* right;
        int height;

        Node(const Student& value) {
            student = value;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    Node* root;
    int totalNodes;

    int getHeight(Node* node) const;
    int getBalance(Node* node) const;
    int maxValue(int a, int b) const;
    int compareStudents(const Student& a, const Student& b) const;

    Node* insert(Node* node, const Student& student, bool& insertedNewNode);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);

    void inOrderRanking(Node* node, int& position) const;
    bool searchBySkillScore(Node* node, int skillScore, Student& result) const;
    void destroyTree(Node* node);

public:
    AVL();
    ~AVL();

    void insertStudent(const Student& student);
    void showRanking() const;
    bool findBySkillScore(int skillScore, Student& result) const;
    void showStatistics() const;

    int getTreeHeight() const;
    int getRootBalanceFactor() const;
    int getTotalNodes() const;
};

#endif