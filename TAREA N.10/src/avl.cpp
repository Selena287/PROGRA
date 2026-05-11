#include "AVL.h"//MAURA SELENA VELASQUEZ ORTEGA
//CARNE:9941-24-14056

AVL::AVL() {
    root = nullptr;
    totalNodes = 0;
}

AVL::~AVL() {
    destroyTree(root);
}

int AVL::getHeight(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVL::getBalance(Node* node) const {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

int AVL::maxValue(int a, int b) const {
    return (a > b) ? a : b;
}

int AVL::compareStudents(const Student& a, const Student& b) const {
    if (a.skill_score > b.skill_score) {
        return -1;
    }

    if (a.skill_score < b.skill_score) {
        return 1;
    }

    if (a.student_id < b.student_id) {
        return -1;
    }

    if (a.student_id > b.student_id) {
        return 1;
    }

    return 0;
}

AVL::Node* AVL::rotateRight(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + maxValue(getHeight(y->left), getHeight(y->right));
    x->height = 1 + maxValue(getHeight(x->left), getHeight(x->right));

    return x;
}

AVL::Node* AVL::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + maxValue(getHeight(x->left), getHeight(x->right));
    y->height = 1 + maxValue(getHeight(y->left), getHeight(y->right));

    return y;
}

AVL::Node* AVL::insert(Node* node, const Student& student, bool& insertedNewNode) {
    if (node == nullptr) {
        insertedNewNode = true;
        return new Node(student);
    }

    int comparison = compareStudents(student, node->student);

    if (comparison < 0) {
        node->left = insert(node->left, student, insertedNewNode);
    } else if (comparison > 0) {
        node->right = insert(node->right, student, insertedNewNode);
    } else {
       
        node->student = student;
        insertedNewNode = false;
        return node;
    }

    node->height = 1 + maxValue(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

  
    if (balance > 1 && compareStudents(student, node->left->student) < 0) {
        return rotateRight(node);
    }

    if (balance < -1 && compareStudents(student, node->right->student) > 0) {
        return rotateLeft(node);
    }

   
    if (balance > 1 && compareStudents(student, node->left->student) > 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

  
    if (balance < -1 && compareStudents(student, node->right->student) < 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVL::insertStudent(const Student& student) {
    bool insertedNewNode = false;
    root = insert(root, student, insertedNewNode);

    if (insertedNewNode) {
        totalNodes++;
    }
}

void AVL::inOrderRanking(Node* node, int& position) const {
    if (node == nullptr) {
        return;
    }

    inOrderRanking(node->left, position);

    cout << position << ". "
         << node->student.full_name
         << " - SCORE: " << node->student.skill_score
         << " | ID: " << node->student.student_id
         << " | CARRERA: " << node->student.career
         << " | SEMESTRE: " << node->student.semester
         << " | GPA: " << node->student.gpa
         << endl;

    position++;

    inOrderRanking(node->right, position);
}

void AVL::showRanking() const {
    if (root == nullptr) {
        cout << "NO SE ENCUENTREA REGISTRO EN RANKING\n";
        return;
    }

    int position = 1;
    cout << "\n RANKING ACADEMICO AVL \n";
    inOrderRanking(root, position);
}

bool AVL::searchBySkillScore(Node* node, int skillScore, Student& result) const {
    if (node == nullptr) {
        return false;
    }

    if (skillScore == node->student.skill_score) {
        result = node->student;
        return true;
    }


    if (skillScore > node->student.skill_score) {
        return searchBySkillScore(node->left, skillScore, result);
    }


    return searchBySkillScore(node->right, skillScore, result);
}

bool AVL::findBySkillScore(int skillScore, Student& result) const {
    return searchBySkillScore(root, skillScore, result);
}

void AVL::showStatistics() const {
    cout << "\n ESTADISTICAS DEL ARBOL AVL \n";
    cout << "ALTURA DEL ARBOL: " << getTreeHeight() << endl;
    cout << "FACTOR DE BALANCE DE LA RAIZ: " << getRootBalanceFactor() << endl;
    cout << "CANTIDAD DE NODOS INGRESADOS: " << getTotalNodes() << endl;
}

int AVL::getTreeHeight() const {
    return getHeight(root);
}

int AVL::getRootBalanceFactor() const {
    return getBalance(root);
}

int AVL::getTotalNodes() const {
    return totalNodes;
}

void AVL::destroyTree(Node* node) {
    if (node == nullptr) {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}