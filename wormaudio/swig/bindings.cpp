// Copyright (c) 2025 Thomas Paley-Menzies
//
// This work is licensed under CC BY-NC-SA 4.0. To view a copy of the license, visit https://creativecommons.org/licenses/by-nc-sa/4.0

#include "bindings.h"

#include "resource/ClipElement.hpp"
#include "resource/serialization.hpp"

namespace binding
{
    void sanityCheck()
    {
        // resource::Handle<element::ClipElement> ce = resource::make<element::ClipElement>(
                // std::make_shared<asset::Asset>(asset::AssetLoader::getInstance(), "/home", asset::Settings::LAZY));
        // std::cout << "You are insane. " << ce->getName() << "\n";

        std::cout << "You are not insane. " << "\n";
    }


    WASystem WASystem::load(const std::string &path)
    {
        std::filesystem::path mainFilePath = path;
        resource::Handle<resource::Project> project = resource::make<resource::Project>(
                std::make_unique<asset::AssetManager>(false));

        asset::AssetLoader::getInstance()->setAssetRoot(std::filesystem::absolute(mainFilePath.parent_path()) / "asset");

        resource::readStructure(project, mainFilePath);

        return WASystem{project};
    }
}
