#include "header.hpp"

int main(int argc, char** argv) {
  auto data = getJSON(argc, argv);
  auto students = parseJSON(data);
  print(students, std::cout);
  return 0;
}
