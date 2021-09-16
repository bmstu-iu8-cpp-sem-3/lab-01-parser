// Copyright 2021 Your MaxV <geraldy12319@gmail.com>
#include <student.hpp>
#include <iostream>

using json = nlohmann::json;

//int main(int argc, char* argv[]
int main() {
    auto students = parse_json_file("json_file.json");
    Print(students, std::cout);
//    if (argc != 1) {
//        for (int i = 1; i < argc; i++) {
//            auto students = parse_json_file(argv[i]);
//            Print(students, std::cout);
//        }
//    } else {
//        throw std::invalid_argument("Expected a path for a *.json file");
//    }
    return 0;
}
