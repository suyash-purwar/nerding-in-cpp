#include <iostream>

using std::cout;
using std::endl;
using std::string;

string appendEndl(string msg); // Function Declaration

void scream() {
    cout << "Ahhhhhhhhhhhhhh!" << endl;
}

int main() {
    string msg1 = "Code";
    string msg2 = "Fast!";

    cout << appendEndl(msg1);
    cout << appendEndl(msg2);
    
    scream();

    cout << sum(2, 4) << endl;
    cout << sum(2.23, 84.2);

    return 0;
}

string appendEndl(string msg) {  // Function Definition
    return msg + '\n';
}