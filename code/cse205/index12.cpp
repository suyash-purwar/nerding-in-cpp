#include<iostream>

using namespace std;

class Queue {
    public:
        int q[50];
        int front, rear, max;
        
        Queue() {
            front = rear = -1;
        }

        int isEmpty() {
            return front == rear;
        }

        int isFull() {
            return rear == max-1;
        }

        void insert(int i) {
            if (!isFull()) {
                q[++rear] = i;
            } else {
                cout << "Queue is full" << endl;
            }
        }

        int deleteElement() {
            if (!isEmpty()) {
                return q[++front];
            } else {
                cout << "Queue is empty" << endl;
                return -1;
            }
        }
};

int main() {
    Queue q;
    cout << q.isEmpty() << endl;
    cout << q.isFull() << endl;
    q.insert(12);
    cout << q.deleteElement() << endl;
    cout << q.isEmpty() << endl;
    return 0;
}