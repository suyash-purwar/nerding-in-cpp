#include <iostream>

using namespace std;

class Node {
    public:
        int data;
        Node* link;
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
                cout << "Stack is full" << endl;
                exit(0);
            }
            temp -> data = t;
            temp -> link = NULL;
            if (top == NULL) {
                top = temp;
            } else {
                temp -> link = top;
                top = temp;
            }
        }

        int pop() {
            int x;
            Node* temp = top;
            if (top -> link == NULL) {
                cout << "Stack is empty" << endl;
            } else {
                x = top -> data;
                top = top -> link;
                delete temp;
                return x;
            }
        }

        int isEmpty() {
            return (top == NULL);
        }

        int getTop() {

        }
};


int main() {
    Stack stack;
    stack.push(12);
    stack.push(89);
    stack.push(3);
    int popped = stack.pop();
    cout << popped << endl;

    return 0;
}