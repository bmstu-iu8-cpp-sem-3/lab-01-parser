#include <any>
#include <string>

#include <gtest/gtest.h>
#include "json.hpp"

namespace {

const char * const json_data = R"(
{
    "lastname" : "Ivanov",
    "firstname" : "Ivan",
    "age" : 25,
    "islegal" : false,
    "marks" : [
    	4,5,5,5,2,3
    ],
    "address" : {
    	"city" : "Moscow",
        "street" : "Vozdvijenka"
    }
})";

TEST(Json, LoadFromString) {
  Json object(json_data);
  EXPECT_EQ(std::any_cast<std::string>(object["lastname"]), "Ivanov");
  EXPECT_EQ(std::any_cast<bool>(object["islegal"]), false);
  EXPECT_EQ(std::any_cast<int>(object["age"]), 25);

  auto marks = std::any_cast<Json>(object["marks"]);
  EXPECT_EQ(std::any_cast<int>(marks[0]), 4);
  EXPECT_EQ(std::any_cast<int>(marks[1]), 5);

  auto address = std::any_cast<Json>(object["address"]);
  EXPECT_EQ(std::any_cast<std::string>(address["city"]), "Moscow");
  EXPECT_EQ(std::any_cast<std::string>(address["street"]), "Vozdvijenka");
}

}  // namespace
