#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <variant>
#include <cmath>
#include <memory>
#include <vector>

#include "cereal/types/variant.hpp"
#include "cereal/types/string.hpp"

#include "juce_data_structures/juce_data_structures.h"
#include "resource/SharedResource.hpp"
#include "signal/Signal.hpp"
#include "util/Data.hpp"
#include "util/serialization_util.hpp"

using ParameterValue = float;

namespace parameter
{
    class ParameterDef;

    struct ParameterType
    {
        static const ParameterType DISCRETE;
        static const ParameterType CONTINUOUS;
        static const ParameterType ENUM;

        const std::string name;

        using Type = int;

        constexpr operator Type() const
        {
            return type;
        }

        static ParameterType get(Type id_);

    private:
        constexpr ParameterType(Type type_, std::string name_): name(std::move(name_)), type(type_) {}
        Type type;
    };

    constexpr  ParameterType ParameterType::DISCRETE{0, "discrete"};
    constexpr ParameterType ParameterType::CONTINUOUS{1, "continuous"};
    constexpr ParameterType ParameterType::ENUM{2, "enum"};

    bool isValidName(const std::string &name);
    ParameterValue parseValue(const std::string& text);
    std::string toString(ParameterValue value);
    ParameterType getType(const ParameterDef& def);
    template<class T> ParameterType getType();

    struct ParameterDefBase : util::Data<std::string>::Listener
    {
        using Changed = signal_event::Callback<>;

        util::Data<std::string> name;
        Changed::Signal changed;

        DISABLE_COPY(ParameterDefBase)
        // ENABLE_DEFAULT_MOVE(ParameterDefBase)

        explicit ParameterDefBase(const std::string& name_):
            name(name_)
        {
            // setIdentifier("parameter def");
            name.setupListener(this, [this](auto& a)
            {
                changed.emit();
            });
        }

        // Some utter stupidity is necessary here because I can't design anything well
        ParameterDefBase& operator=(ParameterDefBase&& other) noexcept
        {
            Listener::operator=(std::move(other));
            std::swap(name, other.name);
            std::swap(changed, other.changed);

            setCallback([this](auto& a)
            {
                changed.emit();
            });

            return *this;
        }

        ParameterDefBase(ParameterDefBase&& other) noexcept:
            Listener(std::move(other)),
            name(other.name),
            changed(std::move(other.changed))
        {
            setCallback([this](auto& a)
            {
                changed.emit();
            });
        }

        // Jank!
        std::string getName() const
        {
            return *name;
        }

    protected:
        FRIEND_CEREAL
        ParameterDefBase(): ParameterDefBase("") {}

        INTERNAL_SERIALIZE
        {
            // TODO
            ar(name);
        }
    };

    struct ContinuousParameterDef : ParameterDefBase
    {
        // TODO cache for playing events

        util::Data<ParameterValue> min;
        util::Data<ParameterValue> max;

        ContinuousParameterDef() = default;

        ContinuousParameterDef(const ParameterValue min_, const ParameterValue max_, const std::string &name_):
            ParameterDefBase(name_), min(min_), max(max_)
        {

        }

        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            return std::clamp(value, *min, *max);
        }

    private:
        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(cereal::base_class<ParameterDefBase>(this), CEREAL_NVP(min), CEREAL_NVP(max));
        }
    };

    struct DiscreteParameterDef : ParameterDefBase
    {
        util::Data<ParameterValue> min;
        util::Data<ParameterValue> max;

        DiscreteParameterDef() = default;

        DiscreteParameterDef(const ParameterValue min_, const ParameterValue max_, const std::string& name_):
            ParameterDefBase(name_), min(min_), max(max_)
        {

        }

        [[nodiscard]] ParameterValue validate(const ParameterValue value) const
        {
            return std::clamp(std::roundf(value), min.getValue(), max.getValue());
        }

    private:
        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            ar(cereal::base_class<ParameterDefBase>(this), CEREAL_NVP(min), CEREAL_NVP(max));
        }
    };

    struct EnumParameterDef : ParameterDefBase
    {
        struct Entry
        {
            std::string name;
            int value;
        };

        std::vector<Entry> values;

        EnumParameterDef() = default;

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

    private:
        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            // ar(cereal::base_class<ParameterDefBase>(this));
            std::cout << "TODO: Enum arameter\n";
        }
    };

    using ParameterDefVariant = std::variant<ContinuousParameterDef, DiscreteParameterDef, EnumParameterDef>;

    class ParameterDef : public resource::SharedResource, public ParameterDefVariant
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

        void setName(const std::string& newName)
        {
            std::visit([&newName](auto& r){ r.name = newName; }, *this);
        }

        ParameterType getType() const
        {
            return parameter::getType(*this);
        }

        ParameterDefBase::Changed::Signal& getChanged()
        {
            return std::visit([](auto& r) -> auto& { return r.changed; }, *this);
        }

        util::Data<std::string>& getNameAsValue()
        {
            return std::visit([](auto& r) -> auto& { return r.name; }, *this);
        }

    private:
        friend class cereal::access;
        explicit ParameterDef():
            variant() {}

        // INTERNAL_SERIALIZE
        // {
            // ar(cereal::base_class<ParameterDefVariant>(this));
        // }
    };

    using Parameter = resource::Handle<ParameterDef>;

    struct ParameterInstance
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


    template<>
    inline ParameterType getType<ContinuousParameterDef>()
    {
        return ParameterType::CONTINUOUS;
    }

    template<>
    inline ParameterType getType<DiscreteParameterDef>()
    {
        return ParameterType::DISCRETE;
    }

    template<>
    inline ParameterType getType<EnumParameterDef>()
    {
        return ParameterType::ENUM;
    }
}
