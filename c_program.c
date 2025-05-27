#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50

// Structure to store student information
typedef struct {
    int rollNo;
    char name[NAME_LENGTH];
    int marks[3];
    float average;
    char grade;
} Student;

// Function prototypes
void addStudent(Student students[], int *count);
void displayStudent(const Student *s);
void displayAllStudents(const Student students[], int count);
void saveToFile(const Student students[], int count);
void loadFromFile(Student students[], int *count);
void calculateGrade(Student *s);
void calculateAverage(Student *s);

int main() {
    Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice;

    loadFromFile(students, &studentCount);

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Save and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                displayAllStudents(students, studentCount);
                break;
            case 3:
                saveToFile(students, studentCount);
                printf("Data saved successfully. Exiting...\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students. Maximum limit reached.\n");
        return;
    }

    Student s;
    s.rollNo = *count + 1;
    printf("Enter name: ");
    getchar();  // To consume newline character left by previous input
    fgets(s.name, NAME_LENGTH, stdin);
    s.name[strcspn(s.name, "\n")] = '\0';  // Remove newline character

    printf("Enter marks for 3 subjects:\n");
    for (int i = 0; i < 3; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%d", &s.marks[i]);
    }

    calculateAverage(&s);
    calculateGrade(&s);

    students[*count] = s;
    (*count)++;

    printf("Student added successfully!\n");
}

void displayStudent(const Student *s) {
    printf("\nRoll No: %d\n", s->rollNo);
    printf("Name: %s\n", s->name);
    printf("Marks: %d, %d, %d\n", s->marks[0], s->marks[1], s->marks[2]);
    printf("Average: %.2f\n", s->average);
    printf("Grade: %c\n", s->grade);
}

void displayAllStudents(const Student students[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        displayStudent(&students[i]);
    }
}

void saveToFile(const Student students[], int count) {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), count, file);
    fclose(file);
}

void loadFromFile(Student students[], int *count) {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }
    fread(count, sizeof(int), 1, file);
    fread(students, sizeof(Student), *count, fi*

