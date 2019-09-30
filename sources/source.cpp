// Copyright 2019 <ara07.99@icloud.com>

#include <header.hpp>

Json::Json(const std::map<std::string, std::any>& map)
{
    data = map;
}
Json::Json(const std::vector<std::any>& vector)
{
    data = vector;
}

// Конструктор из строки, содержащей Json-данные.
Json::Json(const std::string& str)
{
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '{') {
            data = parse_object(str, i);
        } else if (str[i] == '[') {
            data = parse_arr(str, i);
        } else if (!isspace(str[i])) {
            throw std::logic_error("No braces");
        }
    }
}

bool Json::is_array() const
{
    try
    {
        std::any_cast<std::vector<std::any>>(data);
        return true;
    }
    catch (const std::bad_any_cast& e)
    {
        return false;
    }
}

bool Json::is_object() const
{
    try
    {
        std::any_cast<std::map<std::string, std::any >> (data);
        return true;
    }
    catch (const std::bad_any_cast& e)
    {
        return false;
    }
}

{
    return data.has_value();
}

std::any& Json::operator[](const std::string& key)
{
    if (is_object())
    {
        auto& map = std::any_cast<std::map<std::string, std::any>&>(data);
        return map[key];
    } else {
        throw std::logic_error("Error");
    }
}

std::any& Json::operator[](int index)
{
    if (is_array())
    {
        auto& vector = std::any_cast<std::vector<std::any>&>(data);
        return vector[index];
    } else {
        throw std::logic_error("Error");
    }
}

const std::any& Json::operator[](const std::string& key) const
{
    if (is_object())
    {
        auto test = data;
        auto& map = std::any_cast<std::map<std::string, std::any>&>(test);
        return map[key];
    } else {
        throw std::logic_error("Error");
    }
}

const std::any& Json::operator[](int index) const
{
    if (is_array())
    {
        auto test = data;
        auto& vector = std::any_cast<std::vector<std::any>&>(test);
        return vector[index];
    } else {
        throw std::logic_error("Error!!!");
    }
}


Json Json::parse(const std::string& str)
{
    return Json(str);
}

Json Json::parseFile(const std::string& path_to_file)
{
    std::ifstream file(path_to_file);
    std::string str;
    std::string line;
    while (std::getline(file, line))
    {
        str += line;
    }
    return Json(str);
}

std::string parse_str(const std::string& str, size_t& pos)
{
    ++pos;
    std::string string;

    for (size_t i = pos; i < str.size(); ++i)
    {
        if (str[i] == ':' || str[i] == ',') {
            throw std::logic_error("Error");
        } else if (str[i] == '"') {
            string = str.substr(pos, i - pos);
            pos = i;
            return string;
        }
    }

    return string;
}

double parse_num(const std::string& str, size_t& pos)
{
    std::string string;

    for (size_t i = pos; i < str.size(); ++i)
    {
        if (isdigit(str[i]) || str[i] == '.') {
            string += str[i];
        } else if (str[i] == ',' || str[i] == ']' || str[i] == '}'
                   || isspace(str[i])) {
            pos = --i;
            return stod(string);
        } else {
            throw std::invalid_argument("Error");
        }
    }
    return stof(string);
}

bool parse_bool(const std::string& str, size_t& pos)
{
    std::string string;

    for (size_t i = pos; i < str.size(); ++i)
    {
        if (isalpha(str[i])) {
            string += str[i];
        } else if (str[i] == ',' || str[i] == ']' || str[i] == '}') {
            pos = --i;
            if (string == "false") {
                return false;
            } else if (string == "true") {
                return true;
            } else {
                throw std::invalid_argument("Wrong argument");
            }
        } else {
            throw std::invalid_argument("Error");
        }
    }
    return false;
}

void parse_null(const std::string& str, size_t& pos)
{
    while (isspace(str[pos]))
    {
        ++pos;
    }
}


std::vector<std::any> Json::parse_arr(const std::string& str, size_t& pos)
{
    std::vector<std::any> result;
    ++pos;
    State st = find_value;

    for (size_t i = pos; i < str.size(); ++i)
    {
        if (str[i] == '"')
        {
            if (st == find_value)
            {
                result.emplace_back(parse_str(str, i));
                st = find_comma_or_end;
            } else {
                throw std::invalid_argument("Error");
            }
        } else if (str[i] == '{') {
            if (st == find_value)
            {
                result.emplace_back(Json(parse_object(str, i)));
                st = find_comma_or_end;
            } else {
                throw std::invalid_argument("Error");
            }
        } else if (str[i] == '[') {
            if (st == find_value)
            {
                result.emplace_back(Json(parse_arr(str, i)));
                st = find_comma_or_end;
            } else {
                throw std::invalid_argument("Error");
            }
        } else if (str[i] == ']') {
            if (st == find_comma_or_end)
            {
                pos = i;
                return result;
            } else if (st == find_value) {
                parse_null(str, i);
                if (isdigit(str[i]))
                {
                    result.emplace_back(parse_num(str, i));
                } else if (isalpha(str[i])) {
                    result.emplace_back(parse_bool(str, i));
                }

                return result;
            }
        } else if (str[i] == ',') {
            st = find_value;
        } else {
            if (st == find_value)
            {
                parse_null(str, i);
                if (isdigit(str[i]))
                {
                    result.emplace_back(parse_num(str, i));
                } else if (isalpha(str[i])) {
                    result.emplace_back(parse_bool(str, i));
                }
                st = find_comma_or_end;
            } else if (!isspace(str[i])) {
                throw std::logic_error("Error");
            }
        }
    }
    return result;
}


std::map<std::string, std::any> Json::parse_object(const std::string& str,
                                                   size_t& pos)
{
    std::map<std::string, std::any> result;
    State st = find_key_or_end;
    std::string key;

    for (size_t i = pos; i < str.size(); ++i)
    {
        if (str[i] == '"')
        {
            if (st == find_key_or_end)
            {
                key = parse_str(str, i);
                st = find_colon;
            } else if (st == find_value) {
                result[key] = parse_str(str, i);
                st = find_key_or_end;
            } else {
                throw std::logic_error("Error");
            }
        } else if (str[i] == ':') {
            if (st == find_colon) {
                st = find_value;
            } else {
                throw std::logic_error("Error");
            }
        } else if (str[i] == '{') {
            if (st == find_value)
            {
                result[key] = Json(parse_object(str, i));
                st = find_key_or_end;
            }
        } else if (str[i] == '}') {
            if (st == find_key_or_end || st == find_comma_or_end)
            {
                pos = i;
                return result;
            } else {
                throw std::logic_error("Error");
            }
        } else if (str[i] == '[') {
            if (st == find_value)
            {
                result[key] = Json(parse_arr(str, i));
                st = find_key_or_end;
            }
        } else if (str[i] == ']') {
            if (st == find_key_or_end || st == find_comma_or_end)
            {
                pos = i;
                return result;
            } else {
                throw std::logic_error("Error");
            }
        } else if (!isspace(str[i])) {
            if (st == find_value)
            {
                if (isdigit(str[i]))
                {
                    result[key] = parse_num(str, i);
                } else {
                    result[key] = parse_bool(str, i);
                }
                st = find_key_or_end;
            }
        }
    }

    return result;
}
