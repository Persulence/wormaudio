module;

#include <algorithm>
#include <string>
#include <utility>
#include <variant>
#include <cmath>
#include <memory>
#include <vector>

export module parameter;

export using ParameterValue = float;

namespace parameter
{
    export bool isValidName(const std::string &name);
    export ParameterValue parseValue(const std::string& text);

    export enum ParameterType
    {
        CONTINUOUS,
        DISCRETE,
        ENUM,
    };

    export struct ContinuousParameterDef
    {
        ParameterValue min;
        ParameterValue max;

        std::string name;

        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            return std::clamp(value, min, max);
        }
    };

    export struct DiscreteParameterDef
    {
        ParameterValue min;
        ParameterValue max;

        std::string name;

        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            return std::clamp(std::roundf(value), min, max);
        }
    };

    export struct EnumParameterDef
    {
        struct Entry
        {
            std::string name;
            int value;
        };

        std::string name;

        std::vector<Entry> values;

        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            // float integral;
            // float fractional = std::modf(value, &integral);
            float ivalue = std::round(value);
            return std::clamp(ivalue, 0.f, static_cast<float>(values.size()));
        }
    };

    class ParameterDef : public std::variant<ContinuousParameterDef, DiscreteParameterDef, EnumParameterDef>
    {
    public:
        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            return std::visit([&value](auto& r){ return r.validate(value); }, *this);
        }

        [[nodiscard]] std::string getName() const
        {
            return std::visit([](auto& r){ return r.name; }, *this);
        }
    };

    export struct Parameter
    {
        std::shared_ptr<ParameterDef> def;
    };
}

export struct ParameterInstance
{
    parameter::Parameter parameter;
    ParameterValue value{};

    explicit ParameterInstance(parameter::Parameter parameter_):
        parameter(std::move(parameter_))
    {

    }

    ParameterInstance(const ParameterInstance& other) = delete;
    ParameterInstance& operator=(const ParameterInstance& other) = delete;
};