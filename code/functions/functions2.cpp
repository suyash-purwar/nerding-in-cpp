#include <iostream>

using std::cout;
using std::endl;
using std::string;

void introduceMe(string name, string city="null", int age=0); // Default parameters has to be situated at the end of the paramete list
void dashes(int count=10);

int main() {
    string name, city;
    int age;

    introduceMe("Suyash");
    introduceMe("Shubham", "Etawah");
    introduceMe("Madhav", "New York", 28);

    return 0;
}

void introduceMe(string name, string city, int age) {
    cout << "My name is " << name << endl;
    if (city != "null")
        cout << "I live in " << city << endl;
    if (age)
        cout << "I'm " << age << " years old!" << endl;
    dashes(20);
}

void dashes(int count) {
    for (int i = 0; i < count; i++) {
        cout << "-";
    }
    cout << endl;
}
