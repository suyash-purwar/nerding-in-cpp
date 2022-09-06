#include<iostream>

using namespace std;

class Node {
    public:
        int data;
        Node *link;
};

Node *first, *last;

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

        void insert_at_given_position() {
            int d, pos, count = 1;
            Node *temp, *pre, *cur;
            cout << "Enter the data to insert at given position: ";
            cin >> d;
            cout << "Enter the position to insert data: ";
            cin >> pos;

            pre = NULL;
            cur = first;
            temp = new Node();
            temp -> data = d;
            temp -> link = NULL;

            while (count != pos) {
                pre = cur;
                cur = cur -> link;
                count++;
            }

            if (count == pos) {
                pre -> link = temp;
                temp -> link = cur;
            } else {
                cout << "Insertion is not possible" << endl;
            }
        }

        void delete_from_start() {
            Node *temp = first;
            if (temp == NULL) {
                cout << "Deletion is not possible";
            } else {
                cout << "First Element Deleted: " << temp -> data << endl;
                first = first -> link;
                delete temp;
            }
        }

        void delete_from_end() {
            Node *pre, *cur;
            cur = first;
            pre = NULL;
            while (cur != last) {
                pre = cur;
                cur = cur -> link;
            }
            if (cur == last) {
                cout << "The last element deleted: " << cur -> data << endl;
                pre -> link = NULL;
                last = pre;
                delete cur;
            } else {
                cout << "Deletion is not possible" << endl;
            }
        }

        void delete_at_given_position() {
            int pos, count=1;
            Node *pre, *cur;
            pre = NULL;
            cur = first;
            cout << "Enter the position of element to delete: ";
            cin >> pos;
            while (count != pos) {
                pre = cur;
                cur = cur -> link;
                count++;
            }
            if (count == pos) {
                cout << "Deleted element: " << cur -> data << endl;
                pre -> link = cur -> link;
                delete cur;
            } else {
                cout << "Deletion is not possible" << endl;
            }
        }

        void reverse_traversal(Node *t) {
            if (t == NULL) {
                return;
            }
            reverse_traversal(t -> link);
            cout << t -> data << " ===> ";
        }

        void search() {
            int count = 0;
            Node *temp = first;
            bool flag = false;
            cout << "Enter the element to search:";
            int key;
            cin >> key;
            if (temp == NULL) {
                cout << "List is empty!" << endl;
            } else {
                while (temp != NULL) {
                    count++;
                    if (temp -> data == key) {
                        flag = true;
                        cout << "Element found at position " << count << endl;
                        return;
                    }
                    temp = temp -> link;
                }
            }
        }
};

int main() {
    LinkedList list;
    list.create();
    list.create();
    list.create();
    list.display();
    // list.insert_at_start();
    // list.display();
    // list.insert_at_end();
    // list.display();
    // list.insert_at_given_position();
    // list.create();
    // list.delete_from_start();
    // list.display();
    // list.delete_from_end();
    // list.display();
    // list.delete_at_given_position();
    // list.display();
    list.reverse_traversal(first);
    return 0;
}