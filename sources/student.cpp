// Copyright 2021 Your MaxV <geraldy12319@gmail.com>

#include <student.hpp>

auto get_name(const nlohmann::json& j) -> std::string {
    if (j.is_string())
        return j.get<std::string>();
    else
        throw std::invalid_argument("Expected string in name");
}

auto get_debt(const nlohmann::json& j) -> std::any {
    if (j.is_null())
        return nullptr;
    else if (j.is_string())
        return j.get<std::string>();
    else if (j.is_array())
        return j.get<std::vector<std::string> >();
    else
        throw std::invalid_argument(
                "Expected string or array of strings for debt");
}

auto get_avg(const nlohmann::json& j) -> std::any {
    if (j.is_null())
        return nullptr;
    else if (j.is_string())
        return j.get<std::string>();
    else if (j.is_number_float())
        return j.get<double>();
    else if (j.is_number_unsigned())
        return j.get<std::size_t>();
    else
        throw std::invalid_argument(
                "Expected string, double or unsigned value for avg");
}

auto get_group(const nlohmann::json& j) -> std::any {
    if (j.is_string())
        return j.get<std::string>();
    else if  (j.is_number_unsigned())
        return j.get<std::size_t>();
    else
        throw std::invalid_argument(
                "Expected string or unsigned value for group");
}

auto get_str_group(const std::any& group) -> std::string {
    if (group.type() == typeid(std::string))
        return std::any_cast <std::string> (group);
    else if (group.type() == typeid(size_t))
        return std::to_string(std::any_cast <size_t> (group));
    else
        return "null";
}

auto get_str_avg(const std::any& avg) -> std::string {
    if (avg.type() == typeid(std::string))
        return std::any_cast <std::string> (avg);
    else if (avg.type() == typeid(size_t))
        return std::to_string(std::any_cast <size_t> (avg));
    else if (avg.type() == typeid(double))
        return std::to_string(std::any_cast <double> (avg));
    else
        return "null";
}

auto get_str_debt(const std::any& debt) -> std::string {
    if (debt.type() == typeid(std::string))
        return std::any_cast<std::string>(debt);
    else if (debt.type() == typeid(std::nullptr_t))
        return "null";
    else if (debt.type() == typeid(std::vector<std::string>))
        return std::to_string(
                std::any_cast<std::vector<std::string>>(debt).size())
                + " items";
    else
        return "null";
}

void from_json(const nlohmann::json& j, student_t& s) {
    s.name = get_name(j.at("name"));
    s.group = get_group(j.at("group"));
    s.avg = get_avg(j.at("avg"));
    s.debt = get_debt(j.at("debt"));
}

std::vector<student_t> parse_json_file(const std::string& path){
    if (path.empty()){
        throw std::runtime_error("Expected a path for json file");
    }

    std::ifstream file(path);

    if (!file) {
        throw std::runtime_error{"File was not opened"};
    }

    nlohmann::json data;
    file >> data;

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

col_widths table_params(const std::vector<student_t>& students) {
    std::vector<size_t> width(4, 0);
    for (const auto& student : students) {
        if (student.name.length() > width[0]) {
            width[0] = student.name.length();
        }
        if (get_str_group(student.group).length() > width[1]) {
            width[1] = get_str_group(student.group).length();
        }
        if (get_str_avg(student.avg).length() > width[2]) {
            width[2] = get_str_avg(student.avg).length();
        }
        if (get_str_debt(student.debt).length() > width[3]) {
            width[3] = get_str_debt(student.debt).length();
        }
    }
    col_widths result {0, 0, 0 , 0};
    result.name_width = static_cast<int>(width[0]) + 1;
    result.group_width = static_cast<int>(width[1]) + 1;
    result.avg_width = static_cast<int>(width[2]) + 1;
    result.debt_width = static_cast<int>(width[3]) + 1;
    return result;
}

void Print(const std::vector<student_t>& students, std::ostream& ostr) {
    auto col_widths = table_params(students);

    std::string table_line;
    table_line += "|-";
    table_line += (std::string(col_widths.name_width, '-'));
    table_line += "|-";
    table_line += (std::string(col_widths.group_width, '-'));
    table_line += "|-";
    table_line += (std::string(col_widths.avg_width, '-'));
    table_line += "|-";
    table_line += (std::string(col_widths.debt_width, '-'));
    table_line += "|";

    ostr << "| " << std::left << std::setw(col_widths.name_width)
         << "name";
    ostr << "| " << std::left << std::setw(col_widths.group_width)
         << "group";
    ostr << "| " << std::left << std::setw(col_widths.avg_width)
         << "avg";
    ostr << "| " << std::left << std::setw(col_widths.debt_width)
         << "debt" << "|" << std::endl;
    ostr << std::right << table_line << std::endl;

    for (auto& student : students) {
        ostr << "| " << std::left << std::setw(col_widths.name_width)
             << student.name;
        ostr << "| " << std::left << std::setw(col_widths.group_width)
             << get_str_group(student.group);
        ostr << "| " << std::left << std::setw(col_widths.avg_width)
             << get_str_avg(student.avg);
        ostr << "| " << std::left << std::setw(col_widths.debt_width)
             << get_str_debt(student.debt) << "|" << std::endl;
        ostr << std::right << table_line << std::endl;
    }
}
