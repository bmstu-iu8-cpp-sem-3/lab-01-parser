# Лабораторная работа № 1

## Задание

Реализовать утилиту табличного вывода массива данных, хранящихся в файле формата **JSON**.<br />

В качестве аргумента утилите передается путь в к файлу, который в ключе `items`<br />
содержит массив объектов, каждый объект из которых имеет следующие ключи:<br />
`name` - фамилия и имя студента (строчный тип)<br />
`group` - номер группы (строчный/целочисленный тип)<br />
`avg` - средний балл (строчный/целочисленный/вещественный тип)<br />
`debt` - список задолженностей (строчный/перечислительный тип)<br />

## Иллюстрация

Рассмотрим на примере **students.json** файл содержащий описание 3 студентов.

```json
{
  "items": [
    {
      "name": "Ivanov Petr",
      "group": "1",
      "avg": "4.25",
      "debt": null
    },
    {
      "name": "Sidorov Ivan",
      "group": 31,
      "avg": 4,
      "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
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
}
```

И иллюстрацию того, что должна вывести программа после обработки данного файла.
```sh
# ./parser students.json

| name          | group  | avg  | debt          |
|---------------|--------|------|---------------|
| Ivanov Petr   | 1      | 4.25 | null          |
|---------------|--------|------|---------------|
| Sidorov Ivan  | 31     | 4.00 | C++           |
|---------------|--------|------|---------------|
| Pertov Nikita | IU8-31 | 3.33 | 3 items       |
|---------------|--------|------|---------------|
```

## Требования

При разработке утилиты `parser` необходимо учесть следующие моменты:

- Реализовать проверку входных данных:
  * наличия аргумента, содержащего путь к файлу
  * существования файла
  * `items is array`
  * `_meta.count == len(items)`
- Вывод ошибок должен быть информативным
- При написание тестов учесть сценарии с различными типами для полей (`group`, `avg`, `debt`)

## Подсказки

Для парсинга **JSON** файла стоит воспользоваться библиотекой `nlohmann_json`,
подключив ее через пакетный менеджер **Hunter**.

```cpp
// include/student.hpp

struct Student {
    std::string name;
    std::any group;
    std::any avg;
    std::any debt;
}
```

```cpp
// sources/student.cpp

using nlohmann::json;

void from_json(const json& j, student_t& s) {

    s.name = get_name(j.at("group"));
    s.group = get_group(j.at("group"));
    s.avg = get_avg(j.at("avg"));
    s.debt = get_group(j.at("debt"));
}

auto get_name(const json& j) -> std::string {
    return j.get<std::string>();
}

auto get_debt(const json& j) -> std::any {
    if (j.is_null())
        return nullptr;
    else if (j.is_string())
        return j.get<std::string>();
    else
        return j.get<std::vector<std::string> >();
}

auto get_avg(const json& j) -> std::any {
    if (j.is_null())
        return nullptr;
    else if (j.is_string())
        return j.get<std::string>();
    else if (j.is_number_float())
        return j.get<double>();
    else
        return j.get<std::size_t>();
}

auto get_group(const json& j) -> std::any {
    if (j.is_string())
        return = j.get<std::string>();
    else
        return j.get<std::size_t>();
}
```

```cpp
// sources/main.cpp

int main() {
    //...
    std::ifstream file{jsonPath};
    if (!file) {
        throw std::runtime_error{"unable to open json: " + jsonPath};
    }

    json data;
    file >> data;

    std::vector<student_t> students;
    for (auto const& item : data.at("items")) {
        auto student = item.get<student_t>()
        students.push_back(student);
    }
    //...
    print(students, std::cout);
}

void print(const std::vector<student_t>& students, std::ostream& os) {

    //...
    for (auto const& student : students) {
        print(student, os);
    }
}
void print(const student_t& student, std::ostream& os) {
    //...
    if (student.debt.type() == typeid(std::nullptr_t)) {
        os << "null";
    } else if (student.debt.type() == typeid(std::string)) {
        os << std::any_cast<std::string>(student.debt);
    } else {
        os
          << std::any_cast<std::vector<std::string> >(student.debt).size()
          << " items";
    }
}
```
