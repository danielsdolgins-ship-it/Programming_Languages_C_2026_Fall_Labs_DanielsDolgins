// week5_task3_student_management_system.c
// Name: Daniels  Surname: Dolgins  Student ID: 251RDC081
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement the functions to load, save, add, and list students.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int  load_students(Student arr[], int max);          // returns number of records loaded
int  save_students(const Student arr[], int count);  // 0 on success, -1 on error
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    char input[LINE_LEN];
    int running = 1;

    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;
        if (read_line("Select an option: ", input, sizeof input) != 0) {
            choice = 3;                         // end of input: save and exit instead of looping forever
        } else {
            char *end;
            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;   // non-numbers become invalid
        }

        switch (choice) {
            case 1:
                list_students(students, count);
                break;
            case 2:
                add_student(students, &count);
                break;
            case 3:
                if (save_students(students, count) != 0){
                    printf("Error saving data\n");
                }
                printf("Data saved. Goodbye!\n");
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
// The trailing newline is removed. Returns 0 on success, -1 on end of input (EOF).
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == size - 1) {
        // Line was longer than the buffer: discard the rest of it.
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}


int load_students(Student arr[], int max) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL){
    return 0;
}

    char line [LINE_LEN];
    int count = 0;
    while (count < max && fgets(line, sizeof(line), fp) !=NULL) {
    Student s;
    if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3){
        arr[count++] = s;
        }
    }
    fclose(fp);
    return count;
}



int save_students(const Student arr[], int count) {
    FILE *fp = fopen(DATA_FILE, "w");
    if (fp == NULL){
    return -1;
}

for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }

    fclose(fp);
    return 0;
}


void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
}

    char name[LINE_LEN], id_str[LINE_LEN], gpa_str[LINE_LEN];

    read_line("Enter name: ", name, sizeof(name));
    read_line("Enter ID: ", id_str, sizeof(id_str));
    read_line("Enter GPA: ", gpa_str, sizeof(gpa_str));

    if (strlen(name) == 0) {
        printf("Invalid input. Student not added.\n");
        return;
    }
    if (strchr(name, ',') != NULL) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    char *end_id;
    long id_val = strtol(id_str, &end_id, 10);
    if (end_id == id_str) {
        printf("Invalid input. Student not added.\n");
        return;
    }
    if (*end_id != '\0') {
        printf("Invalid input. Student not added.\n");
        return;
    }

    char *end_gpa;
    float gpa_val = strtof(gpa_str, &end_gpa);
    if (end_gpa == gpa_str) {
        printf("Invalid input. Student not added.\n");
        return;
    }
    if (*end_gpa != '\0') {
        printf("Invalid input. Student not added.\n");
        return;
    }
    if (gpa_val < 0.0f) {
        printf("Invalid input. Student not added.\n");
        return;
    }
    if (gpa_val > 4.0f) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // Store record
    strcpy(arr[*count].name, name);
    arr[*count].id = (int)id_val;
    arr[*count].gpa = gpa_val;
    (*count)++;

    printf("Student added successfully!\n");
}

void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
}
    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}
