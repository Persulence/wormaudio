module;

#include <string>
#include <unordered_map>

#include "../event/ParameterList.hpp"

export module sm:ParameterLookup;

import parameter;

namespace sm
{
    export class ParameterLookup
    {

    public:
        std::unordered_map<std::string, std::unique_ptr<parameter::ParameterInstance>> instances;

        void refresh(event::ParameterList& list);

        ParameterValue getValue(const std::string& name) const
        {
            if (const auto it = instances.find(name); it != instances.end())
            {
                return it->second->getValue();
            }

            return {};
        }

        parameter::ParameterInstance& get(const parameter::Parameter& parameter) const
        {
            return get(parameter->getName());
        }

        parameter::ParameterInstance& get(const std::string& name) const
        {
            return *instances.at(name);
        }
    };
}
