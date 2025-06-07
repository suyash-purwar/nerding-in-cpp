#include <iostream>

using std::cout;
using std::endl;
using std::string;

int sum(int a, int b);
// int sum(int a, int b, int c=10); // If we uncomment this, there'll be errors because at line 13, the expression will match two overloaded function declarations
float sum(float a, float b, float c);
double sum(double a, double b);

int main() {
    cout << sum(2, 23) << endl;
    cout << sum(72.21, 84.23) << endl;
    cout << sum(122.324, 90.00223) << endl;
    
    return 0;
}

int sum(int a, int b) {
    return a + b;
}

int sum(int a, int b, int c) {
    return a + b + c;
}

float sum(float a, float b) {
    return a + b;
}

double sum(double a, double b) {
    return a + b;
}