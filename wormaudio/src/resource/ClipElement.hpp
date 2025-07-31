// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#pragma once

#include <memory>

#include "Element.hpp"
#include "ElementInstance.hpp"
#include "Asset.fwd.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "util/AudioContext.hpp"
#include "util/Data.hpp"

namespace element
{
    class ClipElement : public Element, public std::enable_shared_from_this<ClipElement>
    {
    public:
        automation::Property speed{automation::createProperty("speed", 0, automation::Unit::FACTOR)};
        util::Data<bool> loop{false};

        explicit ClipElement(asset::AssetHandle resource_);

        ElementInstancePtr createInstance(player::AudioContext context, automation::AutomationRegistryInstance& automation) override;

        std::string getName() override;

        asset::AssetHandle getAsset();

        std::vector<automation::Property> getProperties() override
        {
            return {volume, speed};
        }

    private:
        asset::AssetHandle asset;

        FRIEND_CEREAL
        ClipElement() = default;

        INTERNAL_SPLIT_SAVE
        {
            ar(cereal::base_class<Element>(this));
            ar(cereal::make_nvp("speed", speed));
            ar(CEREAL_NVP(asset), CEREAL_NVP(loop));
        }

        INTERNAL_SPLIT_LOAD
        {
            ar(cereal::base_class<Element>(this));
            cereal::make_optional_nvp(ar, "speed", speed);
            ar(CEREAL_NVP(asset), CEREAL_NVP(loop));
        }
    };
}