// Copyright (c) 2025 Persulence
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "Project.hpp"

#include "asset/AssetManager.hpp"

namespace resource
{
    Project::Project(std::unique_ptr<asset::AssetManager> assetManager_):
        assetManager(std::move(assetManager_))
    {
        globalParameters = resource::make<event::ParameterListImpl>();
    }

    asset::AssetManager& Project::getAssetManager() const
    {
        return *assetManager;
    }

    std::vector<ResourceHandle> Project::getChildResources()
    {
        std::vector<ResourceHandle> result;
        for (auto& event : events)
        {
            result.push_back(event);
        }

        result.push_back(globalParameters);

        return result;
    }
}
