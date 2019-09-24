#include <any>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <exception>

class Json
{
	std::any data;
public:
	enum State
	{
		find_key_or_end,
		find_colon,
		find_value,
		find_comma_or_end
	};
	Json(const std::map<std::string, std::any>& map);
	Json(const std::vector<std::any>& vector);
	// Конструктор из строки, содержащей Json-данные.
	Json(const std::string& s);
	// Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
	bool is_array() const;

	// Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
	bool is_object() const;

	// Метод возвращает true, если данный экземпляр не содержит ничего, т.е. null. Иначе false.
	bool is_null() const;

	// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-массивом, генерируется исключение.
	std::any& operator[](const std::string& key);

	// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-объектом, генерируется исключение.
	std::any& operator[](int index);
	// Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-массивом, генерируется исключение.
	const std::any& operator[](const std::string& key) const;

	// Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
	// Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
	// Если экземпляр является JSON-объектом, генерируется исключение.
	const std::any& operator[](int index) const;
	std::map<std::string, std::any> parse_object(const std::string& s, size_t& stance);
	std::vector<std::any> parse_arr(const std::string& s, size_t& stance);
	friend std::string parse_str(std::string& s, size_t& stance);
	friend double parse_num(std::string& s, size_t& stance);
	friend bool parse_bool(std::string& s, size_t& stance);
	friend void parse_null(std::string& s, size_t& stance);
	// Метод возвращает объект класса Json из строки, содержащей Json-данные.
	static Json parse(const std::string& s);

	// Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
	static Json parseFile(const std::string& path_to_file);
};
