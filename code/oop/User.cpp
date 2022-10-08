#include<iostream>
#include<vector>
#include<string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

class User {
    short int uid;
    short int age;
    string name;
    vector<string> hobbies;

    public:
    static const bool isHuman = true;
    User(short int id, short int a, string n, vector<string> h) {
        uid = id;
        age = a;
        name = n;
        hobbies = h;
    }

    inline void setName(string n) {
        name = n;
    }

    inline void setAge(short int a) {
        age = a;
    }

    inline string getName() {
        return name;
    }

    inline int getAge() {
        return age;
    }

    string printHobbies() {
        string res;
        for (int i = 0; i < hobbies.size(); i++) {
            res += ((i==hobbies.size()-1) ? hobbies[i] : hobbies[i] + ", ");
        }
        return res;
    }

    void describe() {
        cout << "ID: " << uid << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Hobbies: " + printHobbies() << endl;
    }
};