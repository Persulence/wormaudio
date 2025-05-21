module;

#include <string>
#include <unordered_map>

export module ParameterLookup;

import Parameter;

export class ParameterLookup
{
    std::unordered_map<std::string, ParameterInstance> parameters;
public:
    const ParameterInstance& get(const Parameter& parameter) const
    {
        return get(parameter.name);
    }

    const ParameterInstance& get(const std::string& name) const
    {
        if (const auto it = parameters.find(name); it != parameters.end())
        {
            return it->second;
        }

        return ParameterInstance::defaultInstance();
    }
};
