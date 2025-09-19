#include<string.h>

#include "Person.h"

Person create_person(const char* name, const short int age) {
    Person p;

    memcpy(p.name, name, 20);
    p.age = age;

    return p;
}