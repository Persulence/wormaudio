// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "ParameterList.hpp"

namespace event
{
    using namespace parameter;

    void ParameterListImpl::insert(const Parameter &parameter)
    {
        parameters.push_back(parameter);
    }

    bool ParameterListImpl::remove(const Parameter &parameter)
    {
        auto p = Parameter{};
        if (const auto it = std::ranges::find(parameters, parameter); *it)
        {
            parameters.erase(it);
            return true;
        }

        return false;
    }

    std::vector<Parameter> & ParameterListImpl::getParameters()
    {
        return parameters;
    }

    std::vector<resource::ResourceHandle> ParameterListImpl::getChildResources()
    {
        return std::vector<resource::ResourceHandle>{parameters.begin(), parameters.end()};
    }
}
