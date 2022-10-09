#include<iostream>
#include<string>
#include<cstring>

using std::cout;
using std::endl;
using std::string;

class Hero {
    char health;

    public:
    // Space for the character array of 20 elements is created in the heap memory.
    // Pointer variable 'name' (which is in the stack memory) stores the address of the first element of the character array which resides in the heap memory.
    char *name = new char[20];
    // Insteading of doing this (at line 13), why did we not do this (line 15)
    // char name[100]
    // This is because it's a bad practice
    // Creation of instances in the stack memory could lead to overflow of stack memory and program may crash
    // Since heap has larger memory, we should utilize that
    int level;

    void setHealth(char health) {
        this -> health = health;
    }

    char getHealth() {
        return health;
    }

    void setName(char name[]) {
        // Note: 'char name[]' is equivalent to 'char *name'
        // Address of the first element of the character array is being received.
        // strcpy copies values from character array and stores it in the this->name array.
        // this->name is a pointer variable which points to a memory address in the heap memory
        strcpy(this->name, name);
    }

    void print() {
        cout << endl;
        cout << "[ " << this -> name << ", " << this -> level << ", " << this -> health << " ]" << endl;
    }
};

class Student {
    public:
    static const int hobbies_size = 10;
    int id;
    int age;
    string name;
    string *hobbies = new string[hobbies_size];

    Student(int id, string name, int age, string *hobbies) {
        this -> id = id;
        this -> age = age;
        this -> name = name;
        /**
         * Copying the values we received from hobbies into this->hobbies.
         * Writing 'this->hobbies = hobbies' wouldn't do the job
         * this->hobbies would start pointing to the address of the hobbies array.
         * Changes to the hobbies array would get reflected in the this-> hobbies which is not intentional.
         * So, we need to deep copy the values here and that is done below.
         */
        for (int i = 0; i < this -> hobbies_size; i++) {
            (this -> hobbies)[i] = hobbies[i];
        }
    }

    // Deep copy
    Student(Student &s) {
        // Created a new space in the heap memory for the current object.
        string *temp_hobbies = new string[hobbies_size];
        // Deep copying the values from the previous object to the current object
        for (int i = 0; i < hobbies_size; i++) {
            temp_hobbies[i] = s.hobbies[i];
        }
        // Assigning the address of the temp_hobbies array to the pointer variable hobbies.
        this -> hobbies = temp_hobbies;
        this -> age = s.age;
        this -> id = s.id;
    }

    void describeHobbies() {
        for (int i = 0; i < hobbies_size; i++) {
            cout << hobbies[i] << " ";
        }
        cout << endl;
    }
};

/**
 * Default Copy Constructor makes a shallow copy
 */

int main() {
    char name[7] = "Suyash";

    Hero h1;
    h1.level = 1100;
    h1.setHealth('D');
    h1.setName(name); // Character array is being passed. Actually address of first element of the character array name2 is getting passed
    h1.print();

    /**
     * Default copy constructor copies the values of h1 to h2
     * Remember? that 'h1->name' points to a memory address in the heap memory
     * So, 'h2->name' also points to the same memory address
     * So, any change in 'h2->name' or 'h1->name' reflect in the other as both of them point to the same memory address.
     */
    Hero h2(h1);
    h2.print(); // All the values of h1 are copied into h2

    char name2[7] = "Ashnov";
    h1.setName(name2); // We are changing the value stored in the heap memory here and since both h1.name and h2.name points to the same memory address, the value changes for both.
    h1.print();

    h2.print(); // Value of name in the h2 object changed automatically
    // To avoid this behaviour we do the follow the procedure followed in the Student class

    string hobbies[10] = {"Philosophy", "Programming", "Photography", "Badminton"};
    Student student1(1, "Suyash Purwar", 19, hobbies);
    hobbies[4] = "Listening Songs"; // Making changes here would have no impact as the values from the hobbies are deep copied and not by pass-by-reference method.
    student1.describeHobbies(); // Philosophy", "Programming", "Photography", "Badminton"

    Student student2(student1);
    student2.describeHobbies(); // Philosophy", "Programming", "Photography", "Badminton"

    student1.hobbies[4] = "Sleeping"; // Changes here would have no impact on the student2.hobbies because of deep copying.

    student1.describeHobbies(); // Philosophy", "Programming", "Photography", "Badminton", "Sleeping"
    student2.describeHobbies(); // // Philosophy", "Programming", "Photography", "Badminton"

    return 0;
}