#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct City {
    char name[100];
    int population;
    struct Point position;
};

void printCity(struct City city) {
    printf("%s has a population of %i and has coordinates of (%i, %i)\n", city.name, city.population, city.position.x, city.position.y);
}

int main() {
    struct Point path[] = { {23, 39}, {90, -23}, {3,68} };

    for (int i = 0; i < sizeof(path) / sizeof(path[0]); i++) {
        printf("%i, %i\n", path[i].x, path[i].y);
    }

    struct City cities[] = {
        {"Etawah", 43230, { 120, 84} },
        {"Delhi", 849238348, 85, 19},
        {"Bangalore", 948883482, 975, 3}
    };

    for (int i = 0; i < sizeof(cities) / sizeof(cities[0]); i++) {
        printCity(cities[i]);
    }
}
