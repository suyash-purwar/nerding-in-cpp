#include <string>

std::string someText = "sdfghjkl";
std::string* const const t = &someText;

void test() {
  const int age = 30, b = 20;
  const int* agePtr = &age; // Pointer to constant
  agePtr = &b;
  // *agePtr = b;

  const std::string songName = "Jo Tum Mere Ho";

  const std::string* const songNamePtr = &songName; // Constant Pointer to constant

  std::string text = "systems engineering";
  const std::string* songNamePtr2 = &songName; // Pointer to constant
  songNamePtr2 = &text;
}