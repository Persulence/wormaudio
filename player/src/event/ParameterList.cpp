#include "ParameterList.hpp"

namespace event
{
    using namespace parameter;

    void ParameterList::insert(const Parameter &parameter)
    {
        parameters.push_back(parameter);
    }

    void ParameterList::remove(const Parameter &parameter)
    {
        auto p = Parameter{};
        if (const auto it = std::ranges::find(parameters, parameter); *it)
        {
            parameters.erase(it);
        }
    }
}
