#include <iostream>

using namespace std;

class Stack {
    public:
        int s[20];
        int top, MAX;

        Stack() {
            top = -1;
            MAX = 20;
        }

        void push(char c) {
            if (top == MAX-1) {
                cout << "Stack is overflow" << endl;
            } else {
                s[++top] = c;
            }
        }

        char pop() {
            char ch;
            if (top == -1) {
                cout << "Stack is underflow";
            } else {
                ch = s[top];
                top--;
            }
            return ch;
        }

        int isEmpty() {
            return (top == -1);
        }

        char getTop() {
            char ch;
            if (isEmpty()) {
                cout << "Stack is empty";
            } else {
                ch = s[top];
            }
            return ch;
        }
};

int main() {
    Stack stack;
    cout << stack.getTop() << endl;
    cout << stack.isEmpty() << endl;
    stack.push('F');
    cout << stack.pop() << endl;
    stack.push('U');
    cout << stack.pop() << endl;
    cout << stack.pop() << endl;
    return 0;
}