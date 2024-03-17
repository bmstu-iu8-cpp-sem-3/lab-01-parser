#include <gtest/gtest.h>
#include "header.hpp"

const char* kJsonData = R"({
    "items": [
        {
            "name": "Chuck Norris",
            "group": "1",
            "avg": "4.25",
            "debt": null
        },
        {
            "name": "Jan Clode Van Damme",
            "group": 31,
            "avg": 4,
            "debt": "C++"
        },
        {
            "name": "Terminator Ivanovich",
            "group": "SM6-111",
            "avg": 5,
            "debt": "C++"
        }
    ],
    "_meta": {
        "count": 3
    }
})";

// Тестовый класс
class ParseJSONTest : public ::testing::Test {
 protected:
  nlohmann::json json_data;
  void SetUp() override {
    json_data = nlohmann::json::parse(kJsonData);
  }
};

TEST_F(ParseJSONTest, ParsesCorrectNumberOfStudents) {
  auto students = parseJSON(json_data["items"]);
  EXPECT_EQ(students.size(), 3u) << "Should have parsed 3 students.";
}

TEST_F(ParseJSONTest, ParsesStudentsCorrectly) {
  auto students = parseJSON(json_data["items"]);
  EXPECT_EQ(students[0].name, "Chuck Norris") << "First student name should be Chuck Norris.";
  EXPECT_EQ(students[0].group.type(), typeid(std::string)) << "Group should be of type string for first student.";
  EXPECT_EQ(std::any_cast<std::string>(students[0].group), "1") << "Group should be '1' for first student.";
  EXPECT_TRUE(students[0].debt.type() == typeid(nullptr)) << "Debt should be null for first student.";

  EXPECT_EQ(students[1].name, "Jan Clode Van Damme") << "Second student name should be Jan Clode Van Damme.";
  EXPECT_EQ(students[1].group.type(), typeid(int)) << "Group should be of type int for second student.";
  EXPECT_EQ(std::any_cast<int>(students[1].group), 31) << "Group should be 31 for second student.";
  EXPECT_EQ(std::any_cast<std::string>(students[1].debt), "C++") << "Debt should be 'C++' for second student.";

  EXPECT_EQ(students[2].name, "Terminator Ivanovich") << "Third student name should be Terminator Ivanovich.";
  EXPECT_EQ(students[2].group.type(), typeid(std::string)) << "Group should be of type string for third student.";
  EXPECT_EQ(std::any_cast<std::string>(students[2].group), "SM6-111") << "Group should be 'SM6-111' for third student.";
  EXPECT_EQ(std::any_cast<std::string>(students[2].debt), "C++") << "Debt should be 'C++' for third student.";
}
