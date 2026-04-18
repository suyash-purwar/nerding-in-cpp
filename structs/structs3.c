#include <stdio.h>
#include <string.h>

enum Class {
    INVALID_CLASS = -1,
    FIRST,
    SECOND,
    THIRD,
    FOURTH,
    FIFTH,
    SIXTH,
    SEVENTH,
    EIGHTH,
    NINETEENTH,
    TENTH,
    ELEVENTH,
    TWELFTH
};

const char classNames[12][4] = {
    "I",
    "II",
    "III",
    "IV",
    "V",
    "VI",
    "VII",
    "VIII",
    "IX",
    "X",
    "XI",
    "XII"
};

typedef struct {
    char name[20];
    short int age;
    enum Class class;
} Student;

Student create_student(char name[20], short int age, enum Class class) {
    Student student;
    strcpy(student.name, name);
    student.age = age;
    student.class = class;

    return student;
}

void print_student(Student student) {
    printf("Name: %s\n", student.name);
    printf("Age: %d\n", student.age);
    printf("Class: %s Standard\n", classNames[student.class]);
    printf("---------------------------\n");
}

enum Class get_class(char* className) {
    for (int i = 0; i < sizeof(classNames) / sizeof(classNames[0]); i++) {
        if (strcmp(classNames[i], className) == 0) {
            return i;
        }
    }

    return INVALID_CLASS;
}

int enter_student_details(Student* students) {
    short int no_of_students;

    printf("Enter number of students: ");
    scanf("%hd", &no_of_students);

    for (short int i = 0; i < no_of_students; i++) {
        char name[20];
        short int age;
        char class[4];

        printf("\nEnter details for student %i", i);

        printf("\nName:");
        scanf("%s", name);
        printf("Age:");
        scanf("%hd", &age);
        printf("Standard:");
        scanf("%s", class);

        enum Class class_identifier = get_class(class);

        Student student = create_student(name, age, class_identifier);
        students[i] = student;
    }

    printf("\nEntered details for %hd student(s)\n", no_of_students);

    return no_of_students;
}

int main() {
    Student students[100];

    short int count_of_students = enter_student_details(students);

    printf("\n");
    for (short int i = 0; i < count_of_students; i++) {
        print_student(students[i]);
    }
}