// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

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
