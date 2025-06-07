#include<iostream>
#include<string>
#include<vector>

using namespace std;

int main() {
    // Structure is a user defined type
    // As opposed to array, it stores element of different types
    struct user {
        short int id;
        string name;
        short int age;
        float height;
        vector<string> hobbies;
    };

    struct user suyash;
    struct user shubham;

    suyash.id = 1;
    suyash.name = "Suyash";
    suyash.age = 19;
    suyash.height = 5.7;
    suyash.hobbies = {"Photography", "Philosophy", "Sleeping"};

    cout << suyash.id << endl;
    cout << suyash.name << endl;
    cout << suyash.age << endl;
    cout << suyash.height << endl;
    for (int i = 0; i < suyash.hobbies.size(); i++) {
        cout << suyash.hobbies[i] << " ";
    }
    cout << endl;

    return 0;
}