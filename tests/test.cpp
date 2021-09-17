// Copyright 2021 Your MaxV <geraldy12319@gmail.com>

#include <gtest/gtest.h>
#include "student.hpp"
TEST(Example, test) {
    EXPECT_TRUE(true);
}

TEST(Json_parser_test, parse_right_file) {
    auto students = parse_json_file("json_file1.json");
    std::stringstream parsed;
    Print(students, parsed);
    std::string compare =
            R"(| name  | group  | avg      | debt    |
|-------|--------|----------|---------|
| Ivan  | IU1-11 | 4.2      | null    |
|-------|--------|----------|---------|
| Pavel | 123    | 5        | MatAn   |
|-------|--------|----------|---------|
| Borya | IU2-12 | 4.660000 | 2 items |
|-------|--------|----------|---------|
)";
    EXPECT_EQ(compare,parsed.str());
}

// this test must fall
TEST(Json_parser_test, meta_error) {
    EXPECT_THROW(parse_json_file("json_file2.json"), std::runtime_error);
}

TEST(Json_parser_test, items_not_an_array) {
    EXPECT_THROW(parse_json_file("json_file3.json"), std::runtime_error);
}

TEST(Json_parser_test, wrong_path_error) {
    EXPECT_THROW(parse_json_file("json_file.json"), std::runtime_error);
}


