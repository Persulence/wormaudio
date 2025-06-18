module;

#include <iostream>
#include <memory>
#include <unordered_map>

#include "../event/ParameterList.hpp"

module sm;

namespace sm
{
    void ParameterLookup::refresh(event::ParameterList &list)
    {
        std::unordered_map<std::string, std::unique_ptr<parameter::ParameterInstance>> newInstances;

// #ifdef DEBUG
        // std::cout << "Refreshing parameters\n";
// #endif
        for (auto& parameter : list.getParameters())
        {
            // Retain previous value if the parameter existed before
            ParameterValue value{};
            if (auto it = instances.find(parameter->getName()); it != instances.end())
                value = it->second->value;

            const auto instance = newInstances.emplace(parameter->getName(), std::make_unique<parameter::ParameterInstance>(parameter)).first;
            instance->second->value = value;
        }

        instances = std::move(newInstances);
    }
}