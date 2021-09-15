// Copyright 2021 Your MaxV <geraldy12319@gmail.com>
#include <student.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    std::string wrong_string =
            R"({
              "items": [
                {
                  "name": "Jmishenko Valeriy",
                  "group": "9",
                  "avg": "4.25",
                  "debt": "null"
                },
                {
                  "name": "Vitaliy Tsal",
                  "group": 31,
                  "avg": 4,
                  "debt": "C++"
                },
                {
                  "name": "Evgeniy Ponasenkov",
                  "group": "IU8-31",
                  "avg": 3.33,
                  "debt": [
                    "C++",
                    "Linux",
                    "Network"
                  ]
                }
              ],
              "_meta": {
                "count": 3
              }
            })";
    auto students = ParseString(wrong_string);
    Print(students, std::cout);
    return 0;
}
