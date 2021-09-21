// Copyright 2021 Your MaxV <geraldy12319@gmail.com>

#include <gtest/gtest.h>
#include "student.hpp"


TEST(Json_parser_test, parse_right_file) {
    auto students = parse_json_file("PATH_TO_JSON");
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

//TEST(Json_parser_test, meta_error) {
//    EXPECT_THROW(parse_json_file("json_file2.json"), std::runtime_error);
//}
//
//TEST(Json_parser_test, items_not_an_array) {
//    EXPECT_THROW(parse_json_file("json_file3.json"), std::runtime_error);
//}
//
//TEST(Json_parser_test, wrong_path_error) {
//    EXPECT_THROW(parse_json_file("json_file.json"), std::runtime_error);
//}
//
//TEST(Json_parser_test, empty_path_error) {
//    EXPECT_THROW(parse_json_file(""), std::runtime_error);
//}
//
//TEST(Json_parser_test, wrong_type_group) {
//    EXPECT_THROW(parse_json_file("json_file4.json"), std::invalid_argument);
//}
//
//TEST(Json_parser_test, wrong_type_avg) {
//    EXPECT_THROW(parse_json_file("json_file5.json"), std::invalid_argument);
//}
//
//TEST(Json_parser_test, wrong_type_debt) {
//    EXPECT_THROW(parse_json_file("json_file6.json"), std::invalid_argument);
//}



