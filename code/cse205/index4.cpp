#include<iostream>

using namespace std;

class Node {
    public:
        int data;
        Node *link;
};

class LinkedList {
    public:
        Node *first, *last;

        LinkedList() {
            first = NULL;
            last = NULL;
        }

        void create() {
            int a;
            Node *temp;
            temp = new Node();
            cout << "Enter the data element: ";
            cin >> a;
            temp -> data = a;
            temp -> link = NULL;
            if (first == NULL) {
                first = temp;
                last = temp;
            } else {
                last -> link = temp;
                last = temp;
            }
        }

        void display() {
            Node *temp=first;
            if (temp == NULL) {
                cout << "List is Empty";
            } else {
                while (temp != NULL) {
                    cout << temp -> data << " ===> ";
                    temp = temp -> link;
                }
                cout << "NULL" << endl;
            }
        }

        void insert_at_start() {
            int n;
            Node *temp = new Node();
            cout << "Enter the data to insert at the beginning: ";
            cin >> n;
            temp -> data = n;
            temp -> link = NULL;
            temp -> link = first;
            first = temp;
        }

        void insert_at_end() {
            int n;
            Node *temp = new Node();
            cout << "Enter the data to insert at the ending: ";
            cin >> n;
            temp -> data = n;
            temp -> link = NULL;

            last -> link = temp;
            last = temp;
        }
};

int main() {
    LinkedList list;
    list.create();
    list.create();
    list.create();
    list.display();
    list.insert_at_start();
    list.display();
    list.insert_at_end();
    list.display();
    return 0;
}