module;

#include <string>
#include <unordered_map>

#include "../event/ParameterList.hpp"

export module control:ParameterLookup;

import parameter;

namespace sm
{
    export class ParameterLookup
    {

    public:
        std::unordered_map<std::string, std::unique_ptr<parameter::ParameterInstance>> instances;

        void refresh(event::ParameterList& list)
        {
            // TODO: persitent values

            instances.clear();
            for (auto& parameter : list.parameters)
            {
                // parameters[parameter->getName()] = parameter::ParameterInstance{parameter};
                instances.emplace(parameter->getName(), std::make_unique<parameter::ParameterInstance>(parameter));
            }
        }

        const parameter::ParameterInstance& get(const parameter::Parameter& parameter) const
        {
            return get(parameter->getName());
        }

        const parameter::ParameterInstance& get(const std::string& name) const
        {
            return *instances.at(name);
        }
    };
}
