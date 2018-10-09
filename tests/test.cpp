#include <any>
#include <string>

#include <gtest/gtest.h>
#include <json.hpp>

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
  EXPECT_EQ(std::any_cast<double>(object["age"]), 25);

  auto marks = std::any_cast<Json>(object["marks"]);
  EXPECT_EQ(std::any_cast<double>(marks[0]), 4);
  EXPECT_EQ(std::any_cast<double>(marks[1]), 5);

  auto address = std::any_cast<Json>(object["address"]);
  EXPECT_EQ(std::any_cast<std::string>(address["city"]), "Moscow");
  EXPECT_EQ(std::any_cast<std::string>(address["street"]), "Vozdvijenka");
}

TEST(Json, NestedObjects) {
  auto object = Json::parse(R"({"key":{"d":{"key":{}}}})");
  auto key_object = std::any_cast<Json>(object["key"]);
  auto d_object = std::any_cast<Json>(key_object["d"]);
  ASSERT_NO_THROW(auto last_object = std::any_cast<Json>(d_object["key"]));
}

TEST(Json, NestedArrays) {
  auto array = Json::parse(R"([[],["key"],[]])");
  ASSERT_NO_THROW(auto array0 = std::any_cast<Json>(array[0]));
  ASSERT_NO_THROW(auto array2 = std::any_cast<Json>(array[2]));

  auto array1 = std::any_cast<Json>(array[1]);
  EXPECT_EQ(std::any_cast<std::string>(array1[0]), "key");
}

TEST(Json, EntitiesCombination) {
  auto object = Json::parse(R"({"key":[[[],"key"]]})");
  auto array0 = std::any_cast<Json>(object["key"]);
  auto array1 = std::any_cast<Json>(array0[0]);
  ASSERT_NO_THROW(auto array2 = std::any_cast<Json>(array1[0]));
  EXPECT_EQ(std::any_cast<std::string>(array1[1]), "key");
}

TEST(Json, SimpleObjects) {
  Json object = Json::parse(R"({"k1":{},"k2":{"key":"value"},"k3":{}})");
  ASSERT_NO_THROW(auto k1 = std::any_cast<Json>(object["k1"]));
  ASSERT_NO_THROW(auto k3 = std::any_cast<Json>(object["k3"]));

  auto k2 = std::any_cast<Json>(object["k2"]);
  EXPECT_EQ(std::any_cast<std::string>(k2["key"]), "value");
}

TEST(Json, ObjectsAndArraysWithNumeric) {
  auto object = Json::parse(R"({"k1":{},"k2":{"key": 40},"k3":[0.4]})");
  ASSERT_NO_THROW(auto k1 = std::any_cast<Json>(object["k1"]));

  auto k2 = std::any_cast<Json>(object["k2"]);
  EXPECT_EQ(std::any_cast<double>(k2["key"]), 40);

  auto k3 = std::any_cast<Json>(object["k3"]);
  EXPECT_EQ(std::any_cast<double>(k3[0]), 0.4);
}

TEST(Json, NoThrow) {
  ASSERT_NO_THROW(Json(R"({"key":[[[]]]})"));
  ASSERT_NO_THROW(Json(R"([[],["key"],[]])"));
  ASSERT_NO_THROW(Json(R"({"k1":{},"k2":{"key":"value"},"k3":{}})"));
  ASSERT_NO_THROW(Json(R"({"k1":{},"k2":{"key": 40},"k3":[0.4]})"));
  ASSERT_NO_THROW(Json(R"({"key":{"d":{"a":{}}}})"));
}

TEST(Json, AnyThrow) {
  ASSERT_ANY_THROW(Json(R"({"key":[[[]]})"));
  ASSERT_ANY_THROW(Json(R"([[]["key"],[]])"));
  ASSERT_ANY_THROW(Json(R"({"k1"{},"k2":{"key":"value"},"k3":{}})"));
  ASSERT_ANY_THROW(Json(R"({"k1":{},"k2":{"key": 40},k3":[0.4]})"));
  ASSERT_ANY_THROW(Json(R"("key":{"d":{"a":{}}}})"));
}

}  // namespace
