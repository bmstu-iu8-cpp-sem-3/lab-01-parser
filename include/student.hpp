// Copyright 2021 Your MaxV <geraldy12319@gmail.com>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <any>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>

struct student {
    std::string name;
    std::any group;
    std::any avg;
    std::any debt;
};
auto get_name(const nlohmann::json& j)  -> std::string;
auto get_group(const nlohmann::json& j) -> std::any;
auto get_avg(const nlohmann::json& j)   -> std::any;
auto get_debt(const nlohmann::json& j)  -> std::any;

// initialise field of structure
void from_Json(const nlohmann::json& j, student& s);

// returns a vector of students from json
std::vector<student> parse_Json(nlohmann::json j);

// return a string object made from std::any for a field of structure student
auto get_typed_group(std::vector <student> st, int n) -> std::string;
auto get_typed_avg(std::vector <student> st, int n)   -> std::string;
auto get_typed_debt(std::vector <student> st, int n)  -> std::string;

#endif // INCLUDE_STUDENT_HPP_
