#include<iostream>
#include<vector>
#include<string>
#include "User.cpp"

using std::cout;
using std::endl;
using std::vector;
using std::string;

class Hero {
    /**
     * There are three Access Modifiers:
     * 1. public - makes the data members and methods accessible outside the class
     * 2. private - makes the data member and methods inaccessible outside the class but inside the class they can be accessed.
     * 3. protected - not accessible outside/inside the class
     * By default, properties and methods are private.
     */

    int level; // level is private
    /**
     * private members are not directly accessible outside the class.
     * It can be accessed indirectly outside the class through getter and setter functions.
     */

    public:
    int health; // health is public

    int getLevel() { // Getter function
        return level;
    }
    
    void setLevel(int l) { // Setter function
        level = l;
    }
};

class Employee {
    short int employee_id;

    public:
    string first_name;
    string middle_name;
    string last_name;
    string department;
    string reports_to;

    Employee(short int eid, string fn, string ln, string dept, string rt, string mn="") {
        employee_id = eid;
        first_name = fn;
        middle_name = mn;
        last_name = ln;
        department = dept;
        reports_to = rt;
    };

    inline string fullname() {
        return
        first_name +
        " " +  (middle_name!="" ? middle_name + " " : "") +
        last_name;
    }
};

int main() {
    Hero suyash;
    suyash.health = 100;
    suyash.setLevel(500);
    cout << suyash.getLevel() << endl;
    cout << suyash.health << endl;

    // Static Memory Allocation
    User shubham((short int)1, (short int)24, "Shubham Purwar", vector<string>({"Programming", "Philosophy", "Politics", "History"}));
    cout << shubham.printHobbies() << endl;

    shubham.setAge(shubham.getAge()+1);
    cout << shubham.getAge() << endl;
    shubham.setName("Mr. Shubham Purwar");
    cout << shubham.getName() << endl;

    // Dynamic Memory Allocation
    // Creating the instance of User class in the heap memory
    User *purti = new User(2, 28, "Purti Purwar", vector<string>({"Reading Books", "Philosophy", "Sleeping"}));
    purti->describe();
    cout << "Is Human? " << purti->isHuman << endl;
    string purtiName = purti->getName();
    cout << purtiName << endl;
    cout << (*purti).getAge() << endl;
    cout << (*purti).isHuman << endl;

    // General format for creating instance of the class in the memory
    // Class_Name *name_of_instance = new Class_Name(args.. if any)
    // Accessing the data members
    // *(name_of_instance).property_name  === name_of_instance -> property_name
    // Accessing the methods
    // *(name_of_instance).method_name(args.. if any) === name_of_instance -> method_name(args.. if any)

    Employee *emp1 = new Employee((short int)132, "Shubham", "Purwar", "Software Development", "Mr. N.J. Patnayak");
    cout << emp1 -> fullname() << endl;
    emp1 -> middle_name = "Sandeep";
    cout << emp1 -> fullname() << endl;
    string emp1_dept = emp1 -> department;
    cout << emp1_dept << endl;


    return 0;
}