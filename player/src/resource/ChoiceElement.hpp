// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

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

        ChoiceElement() = default;

        [[nodiscard]] std::vector<std::shared_ptr<::automation::PropertyDef>> getProperties() override;

        [[nodiscard]] ElementInstancePtr createInstance(::player::AudioContext,
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
                cereal::make_nvp("clips", clips)
            );
        }

        INTERNAL_SPLIT_LOAD
        {
            ar(
                cereal::make_nvp("base", cereal::base_class<Element>(this)),
                cereal::make_nvp("loop", loop),
                cereal::make_nvp("clips", clips)
            );
        }
    };
}