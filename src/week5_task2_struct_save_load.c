// week5_task2_struct_save_load.c
// Name: Daniels  Surname: Dolgins  Student ID: 251RDC081
//
// Task 2: Save and load structured records from a file
// Week 5 – Files & Modular Programming
// Build: make lab5   Run: ./bin/week5_task2_struct_save_load
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct Student {
    char name[MAX_NAME_LEN];
    int age;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int save_student(const Student *s, const char *filename);  // 0 on success, -1 on error
int load_student(const char *filename, Student *out);      // 0 on success, -1 on error

int main(void) {
    Student s1 = {0};
    strcpy(s1.name, "Alice");
    s1.age = 21;
    s1.gpa = 3.75f;

    Student loaded = {0};
    const char *filename = "student.txt";

    printf("Saving student to file...\n");
    save_student(&s1, filename);

    printf("Loading student from file...\n");
    load_student(filename, &loaded);

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    return EXIT_SUCCESS;
}

int save_student(const Student *s, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL){
    return -1;
}

    fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);
    fclose(fp);
    return 0;
}

int load_student(const char *filename, Student *out) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL){
    return -1;
}

    fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa);
    fclose(fp);
    return 0;
}
