#pragma once

#include <memory>

#include "Element.hpp"
#include "ElementInstance.hpp"
#include "Resource.fwd.hpp"
#include "automation/instance/AutomationRegistryInstance.hpp"
#include "util/AudioContext.hpp"
#include "util/Data.hpp"

namespace element
{
    class ClipElement : public Element, public std::enable_shared_from_this<ClipElement>
    {
    public:
        util::Data<bool> loop{false};

        explicit ClipElement(asset::AssetHandle resource_):
            asset(std::move(resource_))
        {
        }

        ElementInstancePtr createInstance(player::AudioContext context, automation::AutomationRegistryInstance& automation) override;

        std::string getName() override;

        std::vector<automation::Property> getProperties() override
        {
            return {volume};
        }

    private:
        asset::AssetHandle asset;

        FRIEND_CEREAL
        ClipElement() = default;

        INTERNAL_SPLIT_SAVE
        {
            ar(
                cereal::base_class<Element>(this),
                CEREAL_NVP(asset), CEREAL_NVP(loop)
                );
        }

        INTERNAL_SPLIT_LOAD
        {
            ar(
                cereal::base_class<Element>(this),
                CEREAL_NVP(asset), CEREAL_NVP(loop)
                );
        }
    };
}