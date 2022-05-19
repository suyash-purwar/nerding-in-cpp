#include <iostream>

// Understanding Namespaces
// Link: https://www.youtube.com/watch?v=etQX4Mme2f4&list=PL43pGnjiVwgTnNmcPuhvSUcSgpNfR48ui&index=1&t=1s

using std::cout;
using std::endl;
using std::string;

namespace namespace1 {
    string firstName = "Suyash";
    string lastName = "Purwar";
}

namespace namespace2 {
    int age = 19;
    float height = 5.7;
}

using namespace namespace1;

int main() {
    // '::' is called Scope Operator
    cout << "Hello" << endl;
    cout << firstName <<  lastName << endl;
    cout << namespace2::age << endl;
    cout << "My height is " << namespace2::height << " ft" << endl;
}