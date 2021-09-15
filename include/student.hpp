// Copyright 2021 Your MaxV <geraldy12319@gmail.com>

#ifndef INCLUDE_STUDENT_HPP_
#define INCLUDE_STUDENT_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <ostream>
#include <any>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>

using json = nlohmann::json;

struct student_t {
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
void from_json(const nlohmann::json& j, student_t& s);

// get a string from std::any
auto get_string(std::any value) -> std::string;

std::vector<student_t> ParseString(const std::string& jsonString);

std::map<std::string, int> table_params(const std::vector<student_t>& students);
void Print(const std::vector<student_t>& students, std::ostream& ostr);

#endif // INCLUDE_STUDENT_HPP_
