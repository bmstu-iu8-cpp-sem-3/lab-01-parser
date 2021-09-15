// Copyright 2021 Your MaxV <geraldy12319@gmail.com>

#include <gtest/gtest.h>
#include "student.hpp"

TEST(Example, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(Example2, EmptyTest) {
    EXPECT_TRUE(true);
}

TEST(ParseTest, TableTest){
    std::string wrong_string =
            R"({
              "items": [
                {
                  "name": "Jmishenko Valeriy",
                  "group": "9",
                  "avg": "4.25",
                  "debt": null
                },
                {
                  "name": "Vitaliy Tsal",
                  "group": 31,
                  "avg": 4,
                  "debt": "C++"
                },
                {
                  "name": "Evgeniy Ponasenkov",
                  "group": "IU8-31",
                  "avg": 3.33,
                  "debt": [
                    "C++",
                    "Linux",
                    "Network"
                  ]
                }
              ],
              "_meta": {
                "count": 3
              }
            })";
    auto students = ParseString(wrong_string);

    std::stringstream ss;

    Print(students, ss);

    std::string expect_string = R"(| name               | group  | avg      | debt    |
|--------------------|--------|----------|---------|
| Jmishenko Valeriy  | 9      | 4.25     | null    |
|--------------------|--------|----------|---------|
| Vitaliy Tsal       | 31     | 4        | C++     |
|--------------------|--------|----------|---------|
| Evgeniy Ponasenkov | IU8-31 | 3.330000 | 3 items |
|--------------------|--------|----------|---------|
)";
    EXPECT_EQ(ss.str(), expect_string);
}

TEST(Json_parser_test, parse_string2) {
    std::string test_string =
            R"({
              "items": [
                {
                  "name": "Ivan",
                  "group": "IU1-11",
                  "avg": "4.2",
                  "debt": null
                },
                {
                  "name": "Pavel",
                  "group": 123,
                  "avg": 5,
                  "debt": "MatAn"
                },
                {
                  "name": "Borya",
                  "group": "IU2-12",
                  "avg": 4.66,
                  "debt": [
                    "Angem",
                    "Programming"
                  ]
                }
              ],
              "_meta": {
                "count": 3
              }
            })";
    auto students = ParseString(test_string);
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
    std::cout << "Yes and?" << std::endl;
    EXPECT_EQ(compare,parsed.str());
}
//
//              "items": [
//                {
//                  "name": "Ivan",
//                  "group": "IU1-11",
//                  "avg": "4.2",
//                  "debt": null
//                },
//                {
//                  "name": "Pavel",
//                  "group": 123,
//                  "avg": 5,
//                  "debt": "MatAn"
//                },
//                {
//                  "name": "Borya",
//                  "group": "IU2-12",
//                  "avg": 4.66,
//                  "debt": [
//                    "Angem",
//                    "Programming"
//                  ]
//                }
//              ],
//              "_meta": {
//                "count": 3
//              }
//            })";
//    auto students = ParseString(test_string);
//    std::stringstream parsed;
//    Print(students, parsed);
//    std::string compare =
//            R"(| name  | group  | avg      | debt    |
//|-------|--------|----------|---------|
//| Ivan  | IU1-11 | 4.2      | null    |
//|-------|--------|----------|---------|
//| Pavel | 123    | 5        | MatAn   |
//|-------|--------|----------|---------|
//| Borya | IU2-12 | 4.660000 | 2 items |
//|-------|--------|----------|---------|)";
//    EXPECT_EQ(compare,parsed.str());
//}
//>>>>>>> 4dd23c51f7e95cd66eb90d7b75a3751ac0ec5239
