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
#include <vector>

#include "util/serialization_util.hpp"
#include "cereal/types/vector.hpp"

#include "Element.hpp"
#include "ElementInstance.hpp"
#include "util/Data.hpp"

#include "Asset.hpp"
#include "automation/Property.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "util/AudioContext.hpp"

namespace element
{
    class ChoiceElement : public Element, public std::enable_shared_from_this<ChoiceElement>
    {
    public:
        util::Data<bool> loop{false};
        util::Data<float> pitchRandom{0};
        // automation::Property pitch{automation::createProperty("pitch", 1, automation::Unit::FACTOR)};

        ChoiceElement() = default;

        [[nodiscard]] std::vector<std::shared_ptr<::automation::PropertyDef>> getProperties() override;

        [[nodiscard]] ElementInstancePtr createInstance(player::AudioContext,
                automation::AutomationRegistryInstance &automation) override;

        std::string getName() override;

        void addClip(const asset::AssetHandle &resource);

        const std::vector<asset::AssetHandle>& getClips() const { return clips; }

    private:
        std::vector<asset::AssetHandle> clips;

        bool dirty{true};
        std::vector<asset::ElementSampleBufferHandle> cachedBuffers;

        void cacheBuffers();

        FRIEND_CEREAL

        INTERNAL_SPLIT_SAVE
        {
            ar(
                cereal::make_nvp("base", cereal::base_class<Element>(this)),
                cereal::make_nvp("loop", loop),
                cereal::make_nvp("pitch_random", pitchRandom),
                cereal::make_nvp("clips", clips)
            );
        }

        INTERNAL_SPLIT_LOAD
        {
            ar(cereal::make_nvp("base", cereal::base_class<Element>(this)));
            ar(cereal::make_nvp("loop", loop));
            cereal::make_optional_nvp(ar, "pitch_random", pitchRandom);
            ar(cereal::make_nvp("clips", clips));
        }
    };
}