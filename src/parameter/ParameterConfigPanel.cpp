#include "ParameterConfigPanel.hpp"

#include "ContinuousParameterConfig.hpp"
#include "DiscreteParameterConfig.hpp"
#include "EnumParameterConfig.hpp"

namespace ui
{
    using namespace parameter;

    struct ConfigComponentVisitor
    {
        std::unique_ptr<PropertyFiller> operator()(ContinuousParameterDef& def) const
        {
            return std::make_unique<ContinuousParameterConfig>(def);
        }

        std::unique_ptr<PropertyFiller> operator()(DiscreteParameterDef& def) const
        {
            return std::make_unique<DiscreteParameterConfig>(def);
        }

        std::unique_ptr<PropertyFiller> operator()(EnumParameterDef& def) const
        {
            return std::make_unique<EnumParameterConfig>(def);
        }
    };

    void ParameterProperties::initProperties()
    {
        // Visit the thing
        ConfigComponentVisitor visitor;
        const std::shared_ptr ptr = std::visit(visitor, *parameter);
        add(ptr);
    }
}
