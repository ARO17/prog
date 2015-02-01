/*
 * hash.c -- Hash function training
 * 
 * Written by Harold André
 * E-mail     <harold.andre@gmx.fr>
 * 
 * Started on  Sat Jan 17 14:06:05 2015 Harold André
 * Last update Sat Jan 17 16:02:41 2015 Harold André
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOOKSIZE 100

/* data */
typedef struct student {

    char name[30];
    int age;

} Student;


typedef struct list List;

struct list {

    Student *student;
    List *next;

};

/* functions */
unsigned int hash(char *name, unsigned int tabSize);
Student *createStudent(char *name, unsigned int age);
void addStudent(Student *student, Student *student_array[]);
Student *findStudent(char *name, Student *student_array[]);
Student *collision(char *name, unsigned int hashNumber);

int main(int argc, char *argv[])
{
    int i;
    Student *studentBook[BOOKSIZE];
    Student *student = malloc(sizeof(Student));

    for (i = 0; i < BOOKSIZE; i++) {
	studentBook[i] = NULL;
    }

    addStudent(createStudent("Jean Dupont", 34), studentBook);
    addStudent(createStudent("Marcel Delahousse", 45), studentBook);
    addStudent(createStudent("Mohamed Bousouf", 12), studentBook);
    addStudent(createStudent("Michael Jackson", 42), studentBook);
    /* create collision */
    addStudent(createStudent("chaelMi sonJack", 12), studentBook);

    student = findStudent("Michael Jackson", studentBook);
    printf("Michael Jackson : %s, %d\n", student->name, student->age);

    return 0;
}

unsigned int hash(char *name, unsigned int tabSize)
{
    int i;
    unsigned int hashNumber = 0;

    for (i = 0; name[i] != '\0'; i++) {
	hashNumber += name[i];
    }
    hashNumber %= tabSize;

    return hashNumber;
}

Student *createStudent(char *name, unsigned int age)
{
    Student *student = malloc(sizeof(Student));
    strncpy(student->name, name, strlen(name) + 1);
    student->age = age;

    printf("name = %s\n", name);
    printf("sizeof name = %lu\n", sizeof(name));
    printf("strlen name = %zu\n", strlen(name));

    return student;
}

void addStudent(Student *student, Student *student_array[])
{
    unsigned int hashNumber;

    hashNumber = hash(student->name, BOOKSIZE); 

    if (student_array[hashNumber] != NULL) {
	collision(student->name, hashNumber);
    } else {
	student_array[hashNumber] = student;
    }
}

Student *findStudent(char *name, Student *student_array[])
{
    return student_array[hash(name, BOOKSIZE)];
}

Student *collision(char *name, unsigned int hashNumber)
{
    /* TODO: Handle the collision */
    fprintf(stderr, "Collision in the hash table\n");
    fprintf(stderr, "Because: %s, hash number: %u\n", name, hashNumber);

    return NULL;
}
