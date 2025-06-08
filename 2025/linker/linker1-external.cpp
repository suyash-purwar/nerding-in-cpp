#include <string>

std::string name = "suyash";

// This is not accessible to other because const type variable have
// internal linkage.
const int age = 22;

// static keyword makes the variable password have internal linkage
static std::string password = "oij82d-ai";

std::string sayMyName(std::string name) {
  return "Your name is " + name;
}