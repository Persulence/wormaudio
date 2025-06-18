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
}
