#include <header.hpp>

json getJSON(int argc, char** argv) {
  // Проверка на наличие аргумента с путем к файлу
  if (argc < 2) {
    throw std::runtime_error{"The file path was not passed"};
  }

  // Чтение JSON файла
  std::ifstream jsonFile(argv[1]);
  if (!jsonFile) {
    throw std::runtime_error{"unable to open json: " + std::string(argv[1])};
  }

  // Парсинг JSON
  json data = json::parse(jsonFile, nullptr, false);
  if (data.is_discarded()) {
    throw std::runtime_error{"Failed to parse JSON"};
  }

  // Проверка структуры JSON
  if (!data.contains("items") || !data["items"].is_array()) {
    throw std::runtime_error{"The 'items' array must be contained in the file"};
  }
  if (!data.contains("_meta") || data["items"].size() != data["_meta"].value("count", 0u)) {
    throw std::runtime_error{"_meta value does not match the array size"};
  }

  return data;
}

