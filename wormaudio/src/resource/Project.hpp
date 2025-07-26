// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#pragma once

#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"

#include "Asset.fwd.hpp"
#include "asset/AssetManager.hpp"
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

        explicit Project(std::unique_ptr<asset::AssetManager> assetManager_);

        [[nodiscard]] asset::AssetManager& getAssetManager() const;
        // asset::AssetHandle getAsset(const juce::File &file) const;

        std::vector<ResourceHandle> getChildResources() override;

        Handle<event::EventDef> addEvent(Handle<event::EventDef> handle)
        {
            events.push_back(handle);
            return handle;
        }

        void removeEvent(const Handle<event::EventDef> &handle)
        {
            std::erase(events, handle);
        }

        std::optional<Handle<event::EventDef>> getEvent(const std::string& name)
        {
            if (const auto it = std::ranges::find_if(events, [&name](const auto& e){ return e->nameValue().getValue() == name; }); it != events.end())
            {
                return *it;
            }

            return {};
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
