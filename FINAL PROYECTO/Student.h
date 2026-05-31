#ifndef STUDENT_H
#define STUDENT_H

#include "ProjectList.h"

struct Student {
    int student_id;
    string full_name;
    string career;
    int semester;
    float gpa;
    int skill_score;

    ProjectList projects;
};

#endif