#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <string>
#include <any>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using nlohmann::json;

// Объявления, связанные с JSON
json getJSON(int argc, char** argv);

// Объявления, связанные со Student
struct Student {
 public:
  Student();
  Student(std::string name, std::any group, std::any avg, std::any debt);
  bool operator==(const Student& student) const;

  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

void from_json(const json& j, Student& s);
void print(Student& student, std::ostream& os);
void print(std::string s1, std::string s2, std::string s3, std::string s4, std::ostream& os);
void print(std::vector<Student>& students, std::ostream& os);
std::vector<Student> parseJSON(json& data);


#endif  // INCLUDE_HEADER_HPP_

