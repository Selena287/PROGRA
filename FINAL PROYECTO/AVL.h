#ifndef AVL_H
#define AVL_H

#include <iostream>
#include "Student.h"

using namespace std;

struct AVLNode {
    Student data;
    AVLNode* left;
    AVLNode* right;
    int height;
};

class AVL {
private:

    int getHeight(AVLNode* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalance(AVLNode* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    AVLNode* insertNode(AVLNode* node, Student s) {
        if (node == nullptr) {
            AVLNode* newNode = new AVLNode;
            newNode->data = s;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            return newNode;
        }

        if (s.skill_score < node->data.skill_score)
            node->left = insertNode(node->left, s);
        else if (s.skill_score > node->data.skill_score)
            node->right = insertNode(node->right, s);
        else
            return node;

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && s.skill_score < node->left->data.skill_score)
            return rightRotate(node);

        if (balance < -1 && s.skill_score > node->right->data.skill_score)
            return leftRotate(node);

        if (balance > 1 && s.skill_score > node->left->data.skill_score) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && s.skill_score < node->right->data.skill_score) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorderTraversal(AVLNode* node) {
        if (node == nullptr) return;

        inorderTraversal(node->left);
        cout << node->data.full_name << " | Score: " << node->data.skill_score << endl;
        inorderTraversal(node->right);
    }

    AVLNode* searchNode(AVLNode* node, int score) {
        if (node == nullptr) return nullptr;

        if (score == node->data.skill_score)
            return node;

        if (score < node->data.skill_score)
            return searchNode(node->left, score);
        else
            return searchNode(node->right, score);
    }

public:
    AVLNode* root;

    AVL() {
        root = nullptr;
    }

    void insert(Student s) {
        root = insertNode(root, s);
    }

    void showRanking() {
        if (root == nullptr) {
            cout << "No hay datos en el ranking\n";
            return;
        }
        inorderTraversal(root);
    }

    void search(int score) {
        AVLNode* result = searchNode(root, score);

        if (result)
            cout << "Encontrado: " << result->data.full_name << endl;
        else
            cout << "No encontrado\n";
    }

    int getHeight() {
        return getHeight(root);
    }
};

#endif