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
- При написание тестов учесть сценарии с различными типами для полями (`group`, `avg`, `debt`)

## Подсказки

Для парсинга **JSON** файла стоит воспользоваться библиотекой `nlohmann_json`,
подключив ее через пакетный менеджер **Hunter**.

```cpp
// include/student.hpp

struct Student {
    std::string Name;
    std::any Group;
    double Avg;
    std::any Debt;
}
```

```cpp
// sources/student.cpp

using nlohmann::json;

void from_json(const json& j, Student& s) {
    j.at("name").get_to(s.Name);
    j.at("group").get_to(s.Group);
    j.at("avg").get_to(s.Avg);
    j.at("debt").get_to(s.Debt);
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

    std::vector<Student> students;
    for (auto const& student : data.at("items")) {
        students.push_back(Student{student});
    }
    //...
}
```
