// Copyright 2019 <ara07.99@icloud.com>
#include "lib.h"
#include <any>


using json =  nlohmann::json;
nlohmann::json redistributionOfJson(nlohmann::json& input)
{
    nlohmann::json array = nlohmann::json::array();
    nlohmann::json object = nlohmann::json::object();
    for (size_t i = 0; i < input.size(); ++i)
    {
        size_t a = 0;
        object["ticker"] = input[a][i];
        ++a;
        object["id"] = input[a][i];
        ++a;
        object["description"] = input[a][i];
        array.push_back(object);
    }
    return array;
}

int main()
{
    const char * const json_data = R"(
[
["Si-9.15", "RTS-9.15", "GAZP-9.15"],
[100024, 100027, 100050],
["Futures contract for USD/RUB", "Futures contract for index RTS", "Futures contract for Gazprom shares"]
]
)";
    nlohmann::json input;
    input = nlohmann::json::parse(json_data);
    nlohmann::json output  = redistributionOfJson(input);
    return 0;
}
