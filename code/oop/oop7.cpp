#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;

class Hero {
    public:
    string hero_name;
    int health;
    char level;

    Hero() {
        cout << "Empty constructor called" << endl;
    }

    Hero(string name, int health, char level) {
        hero_name = name;
        this -> health = health;
        this -> level = level;
    }
};

class Employee {
    public:
    int id;
    string firstname;
    string lastname;
    string reports_to;
    string designation;

    Employee() {
        cout << "Empty obect created" << endl;
    }

    // Parameterized Constructor
    Employee(int id, string firstname, string lastname, string reports_to, string designation) {
        this -> id = id;
        this -> firstname = firstname;
        this -> lastname = lastname;
        this -> reports_to = reports_to;
        this -> designation = designation;
    }

    // Copy Constructor
    Employee(Employee &emp, string firstname, string lastname) {
        this -> id = emp.id+1;
        this -> designation = emp.designation;
        this -> reports_to = emp.reports_to;
        this -> firstname = firstname;
        this -> lastname = lastname;
    }

    // Copy Constructor
    Employee(Employee &emp) {
        this -> id = emp.id+1;
        this -> designation = emp.designation;
        this -> reports_to = reports_to;
    }

    /**
     * Why are we always passing 'emp' by pass by reference method?
     * If we were to pass emp by pass by value method, then the value (previously created instance of Employee) would need to get copied into the 'emp' variable which in itself is the work of the copy constructor. So, it becomes a loop.
     * Employee(Employee emp) {
     *    // some code
     * }
     * 
     * int main() {
     *    Employee emp0(...params);
     *    Employee emp1(emp0); // Here, emp0 would need to get stored into 'emp' of the copy constructor which in itself is the work of copy constructor so it becomes a loop. To avoid this, we pass Employee objects by pass-by-reference.
     * }
     */

    void describe() {
        cout << "Id: " << this -> id << endl;
        cout << "Full Name: " << this -> firstname + " " + this -> lastname << endl;
        cout << "Designation: " << this -> designation << endl;
        cout << "Reports to: " << this -> reports_to << endl;
    }
};

int main() {
    Hero h1("Chokra", 100000, 'A');

    /**
     * Suppose we want to create a new hero with the same values as of h1.
     * Option 1
     * => Hero h2()
     * => h2.hero_name = h1.hero_name;
     * => h2.health = h1.health;
     * => h2.level = h1.level;
     * Option 2
     * => Hero h2(h1);
     * This happens using Copy Constructor. 
     * Every class has a Default Copy Constructor which is created by the compiler.
     * This copy constructor makes the option 2 possible.
     * 
     * We can also create our own Copy Constructor where we can select which property needs to be copied or what modification needs to be done
     * There can be multiple Copy Constructor in a class
     * Default Copy Constructor gets deleted once user defined copy constructor are defined
     */

    Hero h2(h1); // Call Default Copy Constructor
    // Copies all the properties of h1 to h2

    Employee emp0(12, "Vinay", "Reddy", "Dr. K. Shivan", "Senior Propulsion Engineer");
    Employee emp1(emp0, "Suyash", "Purwar");
    Employee emp2(emp1, "Sandeep", "Sarma");

    emp0.describe();
    emp1.describe();
    emp2.describe();
}