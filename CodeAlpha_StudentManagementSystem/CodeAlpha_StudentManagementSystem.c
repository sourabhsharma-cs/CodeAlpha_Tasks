#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int roll;
    char name[50];
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    do {
        printf("\n========== STUDENT MANAGEMENT SYSTEM ==========\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Program Exited Successfully.\n"); break;
            default: printf("Invalid Choice! Try Again.\n");
        }
    } while (choice != 6);

    return 0;
}

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct student s;

    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student Added Successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct student s;

    if (fp == NULL) {
        printf("No Records Found!\n");
        return;
    }

    printf("\n%-12s %-25s %-10s\n", "Roll", "Name", "Marks");
    printf("-----------------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%-12d %-25s %-10.2f\n",
               s.roll, s.name, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    struct student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found!\n");
            printf("Roll  : %d\n", s.roll);
            printf("Name  : %s\n", s.name);
            printf("Marks : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen("students.dat", "rb+");
    struct student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("File Error!\n");
        return;
    }

    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            printf("Record Updated Successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    struct student s;
    int roll, found = 0;

    if (fp == NULL || temp == NULL) {
        printf("File Error!\n");
        return;
    }

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll != roll)
            fwrite(&s, sizeof(s), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student Deleted Successfully!\n");
    else
        printf("Student Not Found!\n");
}
