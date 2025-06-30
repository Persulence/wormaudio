#pragma once
#include "Parameter.hpp"

namespace parameter
{
    class ParameterLookup
    {
    public:
        virtual ~ParameterLookup() = default;

        virtual ParameterValue getValue(const std::string& name) const = 0;;
        virtual ParameterInstance& get(const Parameter& parameter) const = 0;
        virtual ParameterInstance& get(const std::string& name) const = 0;
    };
}
