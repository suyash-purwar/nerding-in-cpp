#include <stdio.h>

struct RGB {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

typedef struct {
    char name[20];
    short int age;
} Person;

// Passing struct via reference
void print_rgb(struct RGB *rgb_ptr) {
    printf("RGB: (%d, %d, %d)\n", rgb_ptr->red, rgb_ptr->green, rgb_ptr->blue);
}

int main() {
    struct RGB color1 = { 255, 91, 216 };
    struct RGB *color1_ptr = &color1;
    print_rgb(color1_ptr);

    // Here we are firstly dereferencing it and then accessing the field
    struct RGB color2 = { 182, 8, 94};
    struct RGB *color2_ptr = &color2;
    printf("%d\n", (*color2_ptr).red);

    Person person1, *person1_ptr;
    person1_ptr = &person1;

    printf("Enter the name: ");
    scanf("%s", &(person1_ptr -> name)); // We added the '&' because we want the address of field inside the struct
    printf("Enter the age: ");
    scanf("%hd", &(person1_ptr -> age));

    printf("\nPrinting the person details\n");
    printf("Name: %s\n", person1_ptr -> name);
    printf("Age: %d\n", person1_ptr -> age);
}