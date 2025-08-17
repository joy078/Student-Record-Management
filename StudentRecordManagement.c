#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    char grade[5];
};

const char *filename = "students.txt";

void addStudent() {
    FILE *fp = fopen(filename, "a");
    struct Student s;
    if (!fp) return;

    printf("ID: ");
    scanf("%d", &s.id);
    getchar();
    printf("Name: ");
    fgets(s.name, 50, stdin);
    s.name[strcspn(s.name, "\n")] = 0;
    printf("Age: ");
    scanf("%d", &s.age);
    printf("Grade: ");
    scanf("%s", s.grade);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
    printf("Added!\n");
}

void viewStudents() {
    FILE *fp = fopen(filename, "r");
    struct Student s;
    if (!fp) {
        printf("No records.\n");
        return;
    }
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d | %s | %d | %s\n", s.id, s.name, s.age, s.grade);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen(filename, "r");
    struct Student s;
    int id, found = 0;
    if (!fp) {
        printf("No records.\n");
        return;
    }
    printf("Search ID: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("Found: %d | %s | %d | %s\n", s.id, s.name, s.age, s.grade);
            found = 1;
            break;
        }
    }
    if (!found) printf("Not found.\n");
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen(filename, "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Student s;
    int id, found = 0;
    if (!fp || !temp) return;

    printf("Delete ID: ");
    scanf("%d", &id);
    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            found = 1;
            continue;
        }
        fwrite(&s, sizeof(s), 1, temp);
    }
    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp.txt", filename);
    if (found) printf("Deleted!\n");
    else printf("Not found.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n1.Add 2.View 3.Search 4.Delete 5.Exit\nChoice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: exit(0);
            default: printf("Invalid.\n");
        }
    }
}