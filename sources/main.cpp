// Copyright 2021 Your MaxV <geraldy12319@gmail.com>
#include <student.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    std::string wrong_string =
            R"({
              "items": [
                {
                  "name": "Ivan",
                  "group": "IU1-11",
                  "avg": "4.2",
                  "debt": null
                },
                {
                  "name": "Pavel",
                  "group": 123,
                  "avg": 5,
                  "debt": "MatAn"
                },
                {
                  "name": "Borya",
                  "group": "IU2-12",
                  "avg": 4.66,
                  "debt": [
                    "Angem",
                    "Programming"
                  ]
                }
              ],
              "_meta": {
                "count": 3
              }
            })";
    auto students = ParseString(wrong_string);
    Print(students, std::cout);
    std::cout << "HI";
    return 0;
}
