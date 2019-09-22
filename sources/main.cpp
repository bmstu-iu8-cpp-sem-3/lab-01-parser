#include <iostream>
#include <string>
#include <any>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>

class Json {
private:

    enum class Act //delete if enum working without class
    {
        find_colon,
        find_value,
        find_key_or_end,
        find_comma_or_end
    };

    double parse_number(const std::string &number, size_t& pos) const {
        std::string res;
        double result;
        while(number[pos] != ','){
            if(number[pos] == ']') break;
            if(number[pos] == '}') break;
            if(!isspace(number[pos])) res.push_back(number[pos]);
            pos++;
        }
        pos--;
        std::stringstream ss;
        ss << res;
        ss >> result;
        return result;
    }

    bool parse_bool(const std::string b, size_t& pos) const {
        std::string res;
        bool result;
        while(b[pos] != 'e'){
            res.push_back(b[pos]);
            pos++;
        }
        res.push_back('e');
        if(res == "false"){
            return false;
        }else if(res == "true"){
            return true;
        }
    }

    std::string parse_string(const std::string str, size_t& pos) const {
        std::string res;
        pos++;
        while(str[pos] != '"'){
            res.push_back(str[pos]);
            pos++;
        }
        return res;
    }

    void skip(const std::string str, size_t& pos){
        while(isspace(str[pos])) pos++;
    }

    std::vector<std::any> parse_array(const std::string &str, size_t& pos){
        std::vector<std::any>res;
        auto state = Act::find_value;
        for(size_t i = pos; str[i] != ']'; i++){
            skip(str, i);
            auto k =str[i];
            if(str[i] == '['){
                if(state == Act::find_value){
                    i++;
                    res.emplace_back(Json(parse_array(str,i)));
                    state = Act::find_comma_or_end;
                }  //else throw std::bad_any_cast();
            } else if(str[i] == ']'){
                if(state == Act::find_comma_or_end){
                    pos = i;
                    return res;
                }
                if(state == Act::find_value){
                    pos = i;
                    return res;
                }
            } else if(str[i] == '{'){
                if(state == Act::find_value){
                    i++;
                    res.emplace_back(Json(parse_object(str,i)));
                    state = Act ::find_comma_or_end;
                }// else throw std::bad_any_cast();
            } else if(str[i] == '"'){
                if(state == Act::find_value){
                    res.emplace_back(parse_string(str,i));
                    state = Act::find_comma_or_end;
                } //else throw std::bad_any_cast();
            } else if(str[i] == ','){
                if(state == Act::find_comma_or_end){
                    state = Act::find_value;
                }// else throw std::bad_any_cast();
            } else if(isdigit(str[i]) || isalpha(str[i])){
                if(str[i] == '+' && isdigit(str[i + 1]) != 0 || str[i] == '-' && isdigit(str[i + 1]) !=  0) i++;
                if(str[i] >= '0' && str[i] <= '9' ){
                    if(state == Act::find_value){
                        res.emplace_back(parse_number(str,i));
                        state = Act ::find_comma_or_end;
                    }
                } else if(str[i] == 'f' || str[i] == 't'){
                    if(state == Act::find_value){
                        res.emplace_back(parse_bool(str,i));
                        state = Act ::find_comma_or_end;
                    }
                }
                //else throw std::bad_any_cast();
            }

        }

    }

    std::map<std::string,std::any> parse_object(const std::string &str, size_t& pos){

        std::map<std::string,std::any> res;
        auto state = Act::find_key_or_end;
        std::string key;
        for(size_t i = pos; i < str.length(); i++){
            skip(str, i);
            if(str[i] == '"'){
                if(state == Act::find_key_or_end){
                    key = parse_string(str, i);
                    state = Act::find_colon;
                } else if(state == Act::find_value){
                    res[key] = parse_string(str,i);
                    state = Act::find_comma_or_end;
                }
                // else throw std::bad_any_cast();
            } else if(str[i] == ','){
                if(state == Act::find_comma_or_end){
                    state = Act::find_key_or_end;
                }// else throw std::bad_any_cast();
            } else if(str[i] == '['){
                if(state == Act::find_value){
                    i++;
                    res[key] = Json(parse_array(str,i));
                    state = Act::find_comma_or_end;
                } //else throw std::bad_any_cast();
            } else if(str[i] == '}'){
                if(state == Act::find_comma_or_end){
                    pos = i;
                    return res;
                }
                if(state == Act::find_key_or_end){
                    pos = i;
                    return res;
                }
                if(state == Act::find_value){
                    pos = i;
                    return res;
                }
            } else if(str[i] == '{'){
                if(state == Act::find_value){
                    i++;
                    res[key] = Json(parse_object(str,i));
                    state = Act ::find_comma_or_end;
                } //else throw std::bad_any_cast();
            } else if(str[i] == ':'){
                if(state == Act::find_colon){
                    state = Act::find_value;
                } //else throw std::bad_any_cast();
            } else if(isdigit(str[i]) || isalpha(str[i])){
                if(str[i] == '+' && isdigit(str[i + 1]) != 0 || str[i] == '-' && isdigit(str[i + 1]) !=  0) i++;
                if(str[i] >= '0' && str[i] <= '9' ){
                    if(state == Act::find_value){
                        res[key] = parse_number(str,i);
                        state = Act ::find_comma_or_end;
                    }
                } else if(str[i] == 'f' || str[i] == 't'){
                    if(state == Act::find_value){
                        res[key] = parse_bool(str,i);
                        state = Act ::find_comma_or_end;
                    }
                }
                // else throw std::bad_any_cast();
            }
        }
    }
    //------------------------------------------------------------------------------------------------------------------
public:
    // Конструктор из строки, содержащей Json-данные.
    Json(const std::string &s) {
        for(size_t i = 0; s[i] != '\0'; i++){
            skip(s, i);
            if(s[i] == '{'){
                _data = std::any_cast<std::map<std::string,std::any>>(parse_object(s,i));
            }else if(s[i] == '['){
                _data = std::any_cast<std::vector<std::any>>(parse_array(s,i));
            } else if (!isspace(s[i])){
                //throw std::bad_any_cast();
            }
        }
    };

    Json() {};
    Json(const std::vector<std::any> &array) : _data(array) {};
    Json(const std::map<std::string,std::any> &object) : _data(object) {};

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-массив. Иначе false.
    bool is_array() const {
        if(this->_data.type() != typeid(std::vector<std::any>)) return false;
        return true;
    }

    // Метод возвращает true, если данный экземпляр содержит в себе JSON-объект. Иначе false.
    bool is_object() const {
        if(this->_data.type() != typeid(std::map<std::string,std::any>)) return false;
        return true;
    }


    // Метод возвращает значение по ключу key, если экземпляр является JSON-объектом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-массивом, генерируется исключение.
    std::any &operator[](const std::string &key){
        if(this->is_object()){
            auto &data = std :: any_cast< std::map < std :: string , std::any >&> (_data) ;
            return data[key];
        } else if(this->is_array()){
            std::cout<<"f";
        }
    }

    // Метод возвращает значение по индексу index, если экземпляр является JSON-массивом.
    // Значение может иметь один из следующих типов: Json, std::string, double, bool или быть пустым.
    // Если экземпляр является JSON-объектом, генерируется исключение.
    std::any &operator[](int index){
        if(this->is_array()){
            auto &data = std :: any_cast< std::vector < std::any >&> (_data);
            return data[index];
        } else if(this->is_object()){
            std::cout<<"f";
        }
    }

    // Метод возвращает объект класса Json из строки, содержащей Json-данные.
    static Json parse(const std::string &s) {
        return Json(s);
    }

    // Метод возвращает объекта класса Json из файла, содержащего Json-данные в текстовом формате.
    static Json parseFile(const std::string &path_to_file) {
        std::ifstream f(path_to_file);
        std::stringstream ss;
        ss << f.rdbuf();
        std::cout<<ss.str();
        return Json(ss.str());
    }

private:
    std::any _data;
};
