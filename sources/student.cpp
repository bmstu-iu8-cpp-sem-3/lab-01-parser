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

auto get_string(std::any value) -> std::string {
    if (value.type() == typeid(nullptr_t)) {
        return "null";
    }else if (value.type() == typeid(std::size_t)) {
        return std::to_string(std::any_cast<size_t>(value));
    }else if (value.type() == typeid(std::string)) {
        return std::any_cast<std::string>(value);
    }else if (value.type() == typeid(double)) {
        return std::to_string(std::any_cast<double>(value));
    }else {
        return std::to_string(
                (std::any_cast<std::vector<std::string>>(value)).size())
                + " items";
    }
}

void from_json(const nlohmann::json& j, student_t& s) {
    s.name = get_name(j.at("name"));
    s.group = get_group(j.at("group"));
    s.avg = get_avg(j.at("avg"));
    s.debt = get_debt(j.at("debt"));
}

std::vector<student_t> ParseString(const std::string& jsonString) {
    json data = json::parse(jsonString);

    // json checks
    if (!(data["items"].is_array())) {
        throw std::runtime_error(R"( "items" is not array!)");
    }
    if (data["items"].size() != (data["_meta"])["count"]) {
        throw std::runtime_error(R"("count" in "_meta" doesn't match "items" size)");
    }

    std::vector<student_t> students;
    // for huge json files this can speed up a program
    students.reserve(data["items"].size());

    for (const auto& item : data["items"]) {
        student_t st;
        from_json(item, st);
        students.push_back(st);
    }
    return students;
}

std::map<std::string, int> table_params(const std::vector<student_t>& students){
    std::vector<size_t> width (4);
    for (const auto& student : students) {
        if (student.name.length() > width[0]) {
            width[0] = student.name.length();
        }
        if (get_string(student.group).length() > width[1]) {
            width[1] = get_string(student.group).length();
        }
        if (get_string(student.avg).length() > width[2]) {
            width[2] = get_string(student.avg).length();
        }
        if (get_string(student.debt).length() > width[3]) {
            width[3] = get_string(student.debt).length();
        }
    }
    std::map<std::string, int> col_widths;
    col_widths["name_width"] = static_cast<int>(width[0]);
    col_widths["group_width"] = static_cast<int>(width[1]);
    col_widths["avg_width"] = static_cast<int>(width[2]);
    col_widths["debt_width"] = static_cast<int>(width[3]);
    return col_widths;
}

void Print(const std::vector<student_t>& students, std::ostream& ostr) {
    auto col_widths = table_params(students);

    std::string table_line;
    table_line += "|-";
    table_line += (std::string(col_widths["name_width"], '-'));
    table_line += "|-";
    table_line += (std::string(col_widths["group_width"], '-'));
    table_line += "|-";
    table_line += (std::string(col_widths["avg_width"], '-'));
    table_line += "|-";
    table_line += (std::string(col_widths["debt_width"], '-'));
    table_line += "|";

    ostr << "| " << std::left << std::setw(col_widths["name_width"])
         << "name";
    ostr << "| " << std::left << std::setw(col_widths["group_width"])
         << "group";
    ostr << "| " << std::left << std::setw(col_widths["avg_width"])
         << "avg";
    ostr << "| " << std::left << std::setw(col_widths["debt_width"])
         << "debt" << "|" << std::endl;
    ostr << std::right << table_line << std::endl;

    for (auto& student : students) {
        ostr << "| " << std::left << std::setw(col_widths["name_width"])
             << student.name;
        ostr << "| " << std::left << std::setw(col_widths["group_width"])
             << get_string(student.group);
        ostr << "| " << std::left << std::setw(col_widths["avg_width"])
             << get_string(student.avg);
        ostr << "| " << std::left << std::setw(col_widths["debt_width"])
             << get_string(student.debt) << "|" << std::endl;
        ostr << std::right << table_line << std::endl;
    }
}