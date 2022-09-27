#include<iostream>

using namespace std;

class Node {
    public:
        int data;
        Node *link;
};

class Stack {
    public:
    Node *top;
    Stack() {
        top = NULL;
    }

    void push(int t) {
        Node *temp = new Node();
        if (temp == NULL) {
            cout << "Stack Overflow" << endl;
        } else {
            temp -> data = t;
            temp -> link = NULL;
            if (top == NULL) {
                top = temp;
            } else {
                temp -> link = top;
                top = temp;
            }
        }
    }

    int pop() {
        int x;
        Node *temp = top;
        if (temp == NULL) {
            cout << "Stack underflow" << endl;
            return -1;
        } else {
            x = top -> data;
            top = temp -> link;
        }
        return x;
    }
};

int main() {
    Stack s;
    s.push(1);
    s.push(3);
    cout << s.pop() << endl;
    cout << s.pop() << endl;
    return 0;
}