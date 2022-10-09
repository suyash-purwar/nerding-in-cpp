#include<iostream>
#include<vector>
#include<string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

/**
 * Every class have a constructor and it's job is to initialize the object.
 * class A also have a constructor which is called Default Constructor.
 * It gets called at the time of object creation.
 * Default Constructor doesn't take any parameters.
 * There could be multiple constructors in a class.
 * 
 * If we want to provide some data at the time of object creation we can use Parameterized Constructor which takes arguments.
 * class B has parameterized constructor.
 * 
 * There are three types of constructor in C++:
 * 1) Default Constructor
 * 2) Parameterized Constructor
 * 3) Copy Constructor
*/

class A {
    int prop1;
    string prop2;
};

/**
 * In class B, parameterized constructor is defined now.
 * So, will default constructor be called at time of object creation
 * No, only parameterized constructor will be called
 * As soon an programmer-defined constructor starts to exist, default costructor made by the compiler dies
 */
class B {
    public:
    int prop1;
    string prop2;

    // Parameterized Constructor
    B(int p1, string p2) {
        prop1 = p1;
        prop2 = p2;
    }
};

class Car {
    public:
    int manfacturing_id;
    int model_id;
    string color;
    string model_name;
    bool is_automatic;

    Car() {
        cout << "Empty object initialized" << endl;
    }

    // Parameterized Constructor
    Car(int mnft_id, int model_id) {
        manfacturing_id = mnft_id;
        this -> model_id = model_id;
    }

    // Parameterized Constructor
    Car(int manufacturing_id, int model_id, string color, string model_name, bool isAutomatic) {
        // this points to current object being created from the class
        // Suppose: 
        // Car c1();  | Here, this points to c1
        this -> manfacturing_id = manufacturing_id; // This is same as (*this).manufacturing_id = manufacturing_id
        this -> model_id = model_id; // This is same as (*this).model_id = model_id
        this -> color = color;
        this -> model_name = model_name;
        this -> is_automatic = is_automatic;
    }

    void showIds() {
        cout << "Manufacturing id: " << this -> manfacturing_id << endl;
        cout << "Model id: " << this -> model_id << endl;
    }

    Car* returnThis() {
        // 'this' is a pointer variable
        // 'this' returns the address at which instance of Car is stored
        // '*this' reutrns the instance of Car
        // cout << "Size of 'this' is: " << sizeof(this) << endl; // 8

        return this;
    }

    Car returnValueOfThis() {
        return *this;
    }
};

int main() {
    // Creating object statically
    A a1; // This is same as A a1();

    // B b1; // This will throw errors as there's only one parameterized constructor. Default no longer exists
    
    Car *car1 = new Car(49993, 192, "Matte Black", "Honda City 2", true);
    car1 -> showIds();

    cout << car1 -> returnThis() -> model_id << endl;
    // Above line can also be written like:
    cout << (*(*car1).returnThis()).model_id << endl;

    // car1->returnValueOfThis() returns the object itself. 
    // Note it does not return the address of the object, it return the object itself
    // That is why we cannot write the below like like 'car1->returnValueOfThis()->returnValueOfThis()'
    cout << "Color is: " << car1->returnValueOfThis().color << endl;

    // Chaining the object methods
    cout << car1->returnThis()->returnThis()->returnThis()->returnThis() << endl;
    // More complex chaining
    cout << car1->returnThis()->returnThis()->returnValueOfThis().returnValueOfThis().returnThis()->model_name << endl;
    return 0;
}
