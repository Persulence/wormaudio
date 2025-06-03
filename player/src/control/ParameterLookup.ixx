module;

#include <string>
#include <unordered_map>

export module control:ParameterLookup;

import parameter;

namespace sm
{

    export class ParameterLookup
    {
        std::unordered_map<std::string, ParameterInstance> parameters;
    public:
        const ParameterInstance& get(const parameter::Parameter& parameter) const
        {
            return get(parameter.def->getName());
        }

        const ParameterInstance& get(const std::string& name) const
        {
            // if (const auto it = parameters.find(name); it != parameters.end())
            // {
            //     return it->second;
            // }
            //
            // return ParameterInstance::defaultInstance();
            return parameters.at(name);
        }
    };
}
