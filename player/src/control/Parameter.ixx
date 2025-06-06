module;

#include <algorithm>
#include <string>
#include <utility>
#include <variant>
#include <cmath>
#include <memory>
#include <vector>

#include "juce_core/system/juce_PlatformDefs.h"

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

        ContinuousParameterDef(const ParameterValue min_, const ParameterValue max_, std::string name_):
            min(min_), max(max_), name(std::move(name_))
        {

        }

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

        DiscreteParameterDef(const ParameterValue min_, const ParameterValue max_, std::string name_):
            min(min_), max(max_), name(std::move(name_))
        {

        }

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

        static EnumParameterDef createDefault(const std::string &name)
        {
            EnumParameterDef def{name};
            def.values.emplace_back("value", 0);
            return def;
        }

        explicit EnumParameterDef(std::string name_):
            name(std::move(name_))
        {
        }

        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            // float integral;
            // float fractional = std::modf(value, &integral);
            float ivalue = std::round(value);
            return std::clamp(ivalue, 0.f, static_cast<float>(values.size()));
        }
    };

    using ParameterDefVariant = std::variant<ContinuousParameterDef, DiscreteParameterDef, EnumParameterDef>;

    export class ParameterDef : public ParameterDefVariant
    {
    public:
        explicit ParameterDef(std::variant<ContinuousParameterDef, DiscreteParameterDef, EnumParameterDef> value):
            ParameterDefVariant(std::move(value))
        {

        }

        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            return std::visit([&value](auto& r){ return r.validate(value); }, *this);
        }

        [[nodiscard]] std::string getName() const
        {
            return std::visit([](auto& r){ return r.name; }, *this);
        }

        void setName(const std::string& newName)
        {
            std::visit([&newName](auto& r){ r.name = newName; }, *this);
        }

        JUCE_DECLARE_NON_COPYABLE(ParameterDef)
    };

    export using Parameter = std::shared_ptr<ParameterDef>;

    export struct ParameterInstance
    {
        Parameter parameter;
        ParameterValue value{};

        explicit ParameterInstance(Parameter parameter_):
            parameter(std::move(parameter_))
        {

        }

        ParameterInstance(const ParameterInstance& other) = delete;
        ParameterInstance& operator=(const ParameterInstance& other) = delete;

        // To allow callbacks in the future
        void setValue(const ParameterValue value_)
        {
            value = value_;
        }

        ParameterValue getValue() const
        {
            return value;
        }
    };
}
