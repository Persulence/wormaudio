// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
