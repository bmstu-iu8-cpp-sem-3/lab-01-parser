#include <student.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {

  json j;
  j["name"] = "Ivan Ivanov";
  j["group"] = "IU1-11";
  j["avg"] = 5;
  j["debt"] = "no";

  student s1;
  from_Json(j,s1);
  student s2;
  from_Json(j,s2);
  std::vector<student> s;
  s.push_back(s1);
  s.push_back(s2);
  std::cout << get_typed_group(s,0);
//  std::cout << std::to_string(std::any_cast<unsigned int>(s[0].avg)) ;
  return 0;
}