#include <stdio.h>

typedef struct Person {
  char* name;
  short int age;
} person;

typedef struct Dimension {
  int x;
  int y;
} dimension;

typedef struct Rgb {
  short int r;
  short int g;
  short int b;
} rgb;

struct Pixel {
  dimension dim;
  rgb color;
};

void print_structure(person p) {
  printf("%s\n", p.name);
  printf("%d\n", p.age);
}

void print_pixel(struct Pixel p) {
  printf("Pixel info: \n");
  printf("X-axis %d\n", p.dim.x);
  printf("Y-axis %d\n", p.dim.y);
  printf("Red: %hd\n", p.color.r);
  printf("Blue %hd\n", p.color.b);
  printf("Green %hd\n", p.color.g);
}

struct Pixel create_pixel(int x, int y, short int r, short int g, short int b) {
  struct Pixel pixel;

  pixel.dim.x = x;
  pixel.dim.y = y;
  pixel.color.r = r;
  pixel.color.g = g;
  pixel.color.b = b;

  return pixel;
}

int main() {
  person person1;
  struct Person person2;
  person1.name = "Suyash";
  person1.age = 32;
  
  printf("%d\n", person1.age);
  printf("%s\n", person1.name);
  
  person2.name = "Shubham";
  person2.age = 20;
  
  print_structure(person2);

  struct Pixel pixel = create_pixel(30, 10, 120, 90, 22);
  print_pixel(pixel);

  return 0;
}
