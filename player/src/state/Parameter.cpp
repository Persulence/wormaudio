module;

#include <regex>

module parameter;

namespace parameter
{
    const std::regex PARAMETER_REGEX{"[a-zA-Z][a-zA-Z0-9]*"};

    bool isValidName(const std::string &name)
    {
        return regex_match(name, PARAMETER_REGEX);
    }

    ParameterValue parameter::parseValue(const std::string &text)
    {
        try
        {
            return std::stof(text);
        }
        catch (std::exception e)
        {
            return 0;
        }
    }
}