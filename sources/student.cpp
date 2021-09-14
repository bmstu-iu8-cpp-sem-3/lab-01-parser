// Copyright 2021 Your MaxV <geraldy12319@gmail.com>

#include <student.hpp>

auto get_name(const nlohmann::json& j) -> std::string {
    return j.get<std::string>();
}

auto get_debt(const nlohmann::json& j) -> std::any {
    if (j.is_null())
        return nullptr;
    else if (j.is_string())
        return j.get<std::string>();
    else
        return j.get<std::vector<std::string> >();
}

auto get_avg(const nlohmann::json& j) -> std::any {
    if (j.is_null())
        return nullptr;
    else if (j.is_string())
        return j.get<std::string>();
    else if (j.is_number_float())
        return j.get<double>();
    else
        return j.get<std::size_t>();
}

auto get_group(const nlohmann::json& j) -> std::any {
    if (j.is_string())
        return j.get<std::string>();
    else
    return j.get<std::size_t>();
}

void from_Json(const nlohmann::json& j, student& s) {
    s.name = get_name(j.at("name"));
    s.group = get_group(j.at("group"));
    s.avg = get_avg(j.at("avg"));
    s.debt = get_debt(j.at("debt"));
}

std::vector<student> parse_Json(nlohmann::json j) {
    int counter = 0;
    for (nlohmann::json::iterator i = j["items"].begin(); i != j["items"].end(); i++) {
        counter++;
    }

    if (counter != j["_meta"]["count"]) {
        throw std::runtime_error ("Wrong value for count in _meta");
    }
    std::vector<student> students;
    for (int i = 0; i < counter; i++) {
        student p;
        from_Json((j["items"][i]), p);
        students.push_back(p);
    }
    return students;
}

auto get_typed_group(std::vector <student> st, int n) -> std::string {
    if (typeid(st[n].group) == typeid(std::string)) {
        return std::any_cast <std::string> (st[n].group);
    } else if (typeid(st[n].group) == typeid(unsigned int)) {
        return std::to_string(std::any_cast <unsigned int> (st[n].group));
    } else {
        return "null";
    }
}

std::string get_typed_avg(std::vector <student> st, int n) {
    if (typeid(st[n].avg) == typeid (std::string)) {
        return std::any_cast <std::string> (st[n].avg);
    } else if (typeid(st[n].avg) == typeid(unsigned int)) {
        return std::to_string(std::any_cast <unsigned int> (st[n].avg));
    } else if (typeid(st[n].avg) == typeid(double)) {
        return std::to_string(std::any_cast <double> (st[n].avg));
    } else {
        return "null";
    }
}

std::string get_typed_debt(std::vector <student> st, int n) {
    if (typeid(st[n].debt) == typeid (std::string)) {
        return std::any_cast <std::string> (st[n].debt);
    } if (typeid(st[n].debt) == typeid(std::vector<std::string>)) {
        return  std::to_string(std::any_cast<std::vector<std::string>>(st[n].debt).size()) + " items";
    }
    else {
        return "null";
    }
}
