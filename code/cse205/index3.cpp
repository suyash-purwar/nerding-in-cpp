#include<iostream>

using namespace std;

// Binding Data Member and Member Function in a single unit is called Encapsulation

class Node {
    public:
        int x, y;

        Node() {
            x = 6;
            y = 9;  
        }
        
        void display() {
            cout << x << endl;
            cout << y << endl;
        }
};  

int main() {
    // Node node;
    // node.display();

    Node node;
    node.display();

    float f1 = 323.95;
    int x[] = {1, 3, 2};
    void *p = &f1;
    void *arr = &x;
    cout << p << endl;
    cout << arr << endl;
    return 0;
}