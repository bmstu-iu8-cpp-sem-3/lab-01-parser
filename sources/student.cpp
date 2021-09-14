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
    for (nlohmann::json::iterator i = j["items"].begin();
         i != j["items"].end(); i++) {
        counter++;
    }

    if(counter != j["_meta"]["count"]) {
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

auto get_typed_group(const student& st) -> std::string {
    if (st.group.type() == typeid(std::string)) {
        return std::any_cast <std::string> (st.group);
    } else if (st.group.type() == typeid(unsigned int)) {
        return std::to_string(std::any_cast <unsigned int> (st.group));
    } else {
        return "null";
    }
}

auto get_typed_avg(const student& st) -> std::string {
    if (st.avg.type() == typeid (std::string)) {
        return std::any_cast <std::string> (st.avg);
    } else if (st.avg.type() == typeid(unsigned int)) {
        return std::to_string(std::any_cast <unsigned int> (st.avg));
    } else if (st.avg.type() == typeid(double)) {
        return std::to_string(std::any_cast <double> (st.avg));
    } else {
        return "null";
    }
}

auto get_typed_debt(const student& st) -> std::string{
    if (st.debt.type() == typeid (std::string)) {
        return std::any_cast <std::string> (st.debt);
    } if (st.debt.type() == typeid(std::vector<std::string>)) {
        return  std::to_string(std::any_cast<std::vector<std::string>>(st.debt).size()) + " items";
    }
    else {
        return "null";
    }
}

void print_students(std::ostream& stream,  const std::vector<student>& students){
    for (auto it = students.begin(); it != students.end(); it++){
        stream << get_typed_group(*it)
               << get_typed_avg(*it)
               << get_typed_debt(*it)
               << (*it).name;
    }
}

std::ostream & operator << (std::ostream& ostream, const std::vector<student>& students){
    print_students(ostream,students);
    return ostream;
}