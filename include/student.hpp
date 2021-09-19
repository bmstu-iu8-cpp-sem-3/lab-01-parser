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

struct student_t {
    std::string name;
    std::any group;
    std::any avg;
    std::any debt;
};

// structure to organize formatted output of parsing
struct col_widths{
    int name_width;
    int group_width;
    int avg_width;
    int debt_width;
};

auto get_name(const nlohmann::json& j)  -> std::string;
auto get_group(const nlohmann::json& j) -> std::any;
auto get_avg(const nlohmann::json& j)   -> std::any;
auto get_debt(const nlohmann::json& j)  -> std::any;

// initialise field of structure
void from_json(const nlohmann::json& j, student_t& s);

// functions return strings from std::any for fields of struct
// if type of field of parsed student isn't expected
// program throws an exception
auto get_str_group(const std::any& group) -> std::string;
auto get_str_avg(const std::any& avg)     -> std::string;
auto get_str_debt(const std::any& debt)   -> std::string;

std::vector<student_t> parse_json_file(const std::string& path);

col_widths table_params(const std::vector<student_t>& students);
void Print(const std::vector<student_t>& students,
           std::ostream& ostr = std::cout);

#endif // INCLUDE_STUDENT_HPP_
