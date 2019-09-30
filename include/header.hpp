 Copyright 2019 Your Name <ara07.99@icloud.com>
#pragma once

#include <any>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <exception>

class Json
{
    std::any data;
public:
    enum State
    {
        find_key_or_end,
        find_colon,
        find_value,
        find_comma_or_end
    };
    explicit Json(const std::map<std::string, std::any>& map);

    explicit Json(const std::vector<std::any>& vector);

    explicit Json(const std::string& s);

    bool is_array() const;

    bool is_object() const;

    bool is_null() const;

    std::any& operator[](const std::string& key);

    std::any& operator[](int index);

    const std::any& operator[](const std::string& key) const;

    const std::any& operator[](int index) const;

    std::map<std::string, std::any> parse_object(const std::string& s,
                                                 size_t& stance);

    std::vector<std::any> parse_arr(const std::string& s, size_t& stance);

    static Json parse(const std::string& s);

    static Json parseFile(const std::string& path_to_file);
};
