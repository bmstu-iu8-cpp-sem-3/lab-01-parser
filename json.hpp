#include <any>

class Json {
public:
    // Конструктор из строки, содержащей Json-данные.
    Json(const std::string& s)
    {
		throw std::logic_error("not implemented");
    }
	
    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array() const
    {
		throw std::logic_error("not implemented");
    }
    // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object() const
    {
		throw std::logic_error("not implemented");
    }

    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    std::any& operator[](const std::string& key)
    {
		throw std::logic_error("not implemented");
    }
    
    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    std::any& operator[](int index)
    {
		throw std::logic_error("not implemented");
    }
    
    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string& s)
    {
		throw std::logic_error("not implemented");
    }
    
    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const std::string& path_to_file)
    {
		throw std::logic_error("not implemented");
    }
};