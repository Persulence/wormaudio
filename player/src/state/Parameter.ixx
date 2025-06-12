module;

#include <algorithm>
#include <string>
#include <utility>
#include <variant>
#include <cmath>
#include <memory>
#include <vector>

#include "juce_data_structures/juce_data_structures.h"

export module parameter;

export using ParameterValue = float;

namespace parameter
{
    export class ParameterDef;

    export enum ParameterType
    {
        CONTINUOUS,
        DISCRETE,
        ENUM,
    };

    export bool isValidName(const std::string &name);
    export ParameterValue parseValue(const std::string& text);
    export std::string toString(ParameterValue value);
    export ParameterType getType(const ParameterDef& def);
    export template<class T> ParameterType getType();

    struct ParameterDefBase
    {
        juce::Value name;

        ParameterDefBase() = default;

        explicit ParameterDefBase(const std::string& name_):
            name(juce::String{name_})
        {

        }

        std::string getName() const
        {
            return static_cast<juce::String>(name.getValue()).toStdString();
        }
    };

    export struct ContinuousParameterDef : ParameterDefBase
    {
        // TODO cache for playing events
        // ParameterValue min;
        // ParameterValue max;

        juce::Value min;
        juce::Value max;

        // std::string name;

        ContinuousParameterDef(const ParameterValue min_, const ParameterValue max_, const std::string &name_):
            ParameterDefBase(name_), min(min_), max(max_)
        {

        }

        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            return std::clamp(value, static_cast<ParameterValue>(min.getValue()), static_cast<ParameterValue>(max.getValue()));
        }
    };

    export struct DiscreteParameterDef : ParameterDefBase
    {
        juce::Value min;
        juce::Value max;

        DiscreteParameterDef(const ParameterValue min_, const ParameterValue max_, const std::string& name_):
            ParameterDefBase(name_), min(min_), max(max_)
        {

        }

        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            return std::clamp(std::roundf(value), static_cast<ParameterValue>(min.getValue()), static_cast<ParameterValue>(max.getValue()));
        }
    };

    export struct EnumParameterDef : ParameterDefBase
    {
        struct Entry
        {
            std::string name;
            int value;
        };

        juce::Value name;

        std::vector<Entry> values;

        static EnumParameterDef createDefault(const std::string &name_)
        {
            EnumParameterDef def{name_};
            def.values.emplace_back("value", 0);
            return def;
        }

        explicit EnumParameterDef(const std::string &name_):
            ParameterDefBase(name_)
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
            // return std::visit([](auto& r){ return juce::String(r.name.getValue()).toStdString(); }, *this);
            return std::visit([](auto& r){ return r.getName(); }, *this);
        }

        [[nodiscard]] juce::Value getNameAsValue() const
        {
            return std::visit([](auto& r){ return r.name; }, *this);
        }

        void setName(const std::string& newName)
        {
            std::visit([&newName](auto& r){ r.name.setValue(juce::String(newName)); }, *this);
        }

        ParameterType getType() const
        {
            return parameter::getType(*this);
        }

        // JUCE_DECLARE_NON_COPYABLE(ParameterDef)
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

        [[nodiscard]] ParameterValue getValue() const
        {
            return value;
        }
    };


    export template<> ParameterType getType<ContinuousParameterDef>()
    {
        return CONTINUOUS;
    }

    export template<> ParameterType getType<DiscreteParameterDef>()
    {
        return DISCRETE;
    }

    export template<> ParameterType getType<EnumParameterDef>()
    {
        return ENUM;
    }
}
