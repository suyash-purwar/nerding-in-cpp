#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned short age;
    float height;
    char name[23];
} Person;

size_t input_person_count() {
    size_t person_count;
    scanf("%zu", &person_count);

    return person_count;
}

Person create_person() {
    char name[24];
    unsigned short age;
    float height;

    scanf("%s", name);
    scanf("%hd", &age);
    scanf("%f", &height);

    Person person;
    strcpy(person.name, name);
    person.age = age;
    person.height = height;

    return person;
}

Person* input_persons(size_t person_count) {
    Person* person_ptr = (Person*)malloc(sizeof(Person) * person_count);

    for (size_t i = 0; i < person_count; i++) {
        *(person_ptr + i) = create_person();
    }

    return person_ptr;
}

void print_person(Person* person_ptr) {
    printf("Person details:\n");
    printf("Name: %s\n", person_ptr->name);
    printf("Age: %d\n", person_ptr->age);
    printf("Height: %.2f\n", person_ptr->height);
}

int main() {
    size_t person_count = input_person_count();

    if (person_count <= 0) {
        printf("Person count must be more than zero.");
        return -1;
    }

    Person* person_array = input_persons(person_count);

    for (size_t i = 0; i < person_count; i++) {
        print_person(person_array + i);
    }
}