#pragma once

#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"

#include "Asset.fwd.hpp"
#include "SharedResource.hpp"
#include "event/EventDef.hpp"
#include "event/ParameterList.hpp"
#include "util/serialization_util.hpp"

namespace resource
{
    class Project final : public SharedResource
    {
    public:
        Handle<event::ParameterListImpl> globalParameters;
        std::vector<Handle<event::EventDef>> events{};
        std::unique_ptr<asset::AssetManager> assetManager;

        Project(std::unique_ptr<asset::AssetManager> assetManager_);

        [[nodiscard]] asset::AssetManager& getAssetManager() const;
        // asset::AssetHandle getAsset(const juce::File &file) const;

        std::vector<ResourceHandle> getChildResources() override;

        Handle<event::EventDef> addEvent(Handle<event::EventDef> event)
        {
            events.push_back(event);
            return event;
        }

    private:
        FRIEND_CEREAL

        INTERNAL_SERIALIZE
        {
            using namespace cereal;
            ar(
                make_nvp("global_parameters", globalParameters),
                make_nvp("events", events)
                );
            make_optional_nvp(ar, "assets", assetManager);
        }
    };
}
