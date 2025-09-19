#include <stdio.h>

// #include "libs/Person.h"

int main() {
    char name[20];
    short int age;

    scanf("Enter name: %c", &name);
    scanf("Enter age: %hd", &age);

    // Person p1 = create_person(name, age);

    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
}