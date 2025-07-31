// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
