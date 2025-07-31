// Copyright (c)  2025 Persulence
//
// This file is part of the WormAudio project.
//
// WormAudio is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// WormAudio is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License along with Foobar. If not, see https://www.gnu.org/licenses/.
//

#include "WASystemNode.hpp"

#include <filesystem>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <resource/Project.hpp>
#include <resource/SharedResource.hpp>
#include <resource/serialization.hpp>

#include "WAListenerNode.hpp"
#include "sound/WASoundDef.hpp"

#include "../WormAudioGodot.hpp"

namespace wa
{
    WASystemNode::WASystemNode() {}

    WASystemNode::~WASystemNode() {}

    void WASystemNode::setSystemResource(const godot::Ref<WASystemResource> &ref)
    {
        system = nullptr;
        this->systemResource = ref;
    }

    void WASystemNode::_ready()
    {
        Node::_ready();

        if (getSystem())
        {
            WormAudioGodot::log("Starting runtime ");
            WormAudioGodot::getInstance().getRuntime().transport.setState(player::PLAYING);
            // WormAudioGodot::log("runtime state " + static_cast<int>(WormAudioGodot::getInstance().getRuntime().transport.getState()));
        }
    }

    resource::Handle<resource::Project> WASystemNode::getSystem()
    {
        if (!system)
        {
            system = loadSystem();
            WormAudioGodot::getInstance().getRuntime().getParameters().refresh(*system->globalParameters);
            system->getAssetManager().preprocess();
        }

        return system;
    }

    resource::Handle<resource::Project> WASystemNode::loadSystem() const
    {
        if (!systemResource.is_null())
        {
            auto settings = godot::ProjectSettings::get_singleton();
            auto globalPathString = settings->globalize_path(systemResource->getFilePath());

            // Load the system
            const std::filesystem::path mainFilePath = globalPathString.utf8().get_data();

            try
            {
                resource::Handle<resource::Project> loadedProject = resource::make<resource::Project>(
                        std::make_unique<asset::AssetManager>(false));

                asset::AssetLoader::getInstance()->setAssetRoot(
                        std::filesystem::absolute(mainFilePath.parent_path()) / "asset");

                resource::readStructure(loadedProject, mainFilePath);

                WormAudioGodot::log(WormAudioGodot::INFO, std::format("Loaded system {}", mainFilePath.string()));

                return loadedProject;
            }
            catch (std::exception &e)
            {
                WormAudioGodot::log(WormAudioGodot::ERROR,
                                    std::format("Failed to load system {}: {}", mainFilePath.string(), e.what()));
            }
        }
        return nullptr;
    }

    WASoundDef* WASystemNode::getSoundDef(const godot::String &name)
    {
        if (const auto system = getSystem())
        {
            if (const auto sound = system->getEvent(toString(name)))
            {
                return memnew(WASoundDef{*sound});
            }
        }

        return nullptr;
    }

    void WASystemNode::setListenerPath(const godot::NodePath &listenerPath)
    {
        this->listenerPath = listenerPath;
        listenerCache = nullptr;
    }

    WAListenerNode* WASystemNode::getListener()
    {
        if (!listenerCache)
        {
            listenerCache = get_node<WAListenerNode>(listenerPath);
        }

        return listenerCache;
    }

    void WASystemNode::_bind_methods()
    {
        using namespace godot;
        ClassDB::bind_method(D_METHOD("get_system"), &WASystemNode::getSystemResource);
        ClassDB::bind_method(D_METHOD("set_system", "system_res"), &WASystemNode::setSystemResource);

        ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "system", PROPERTY_HINT_RESOURCE_TYPE, "WASystemResource"),
                     "set_system", "get_system");

        ClassDB::bind_method(D_METHOD("get_listener_path"), &WASystemNode::getListenerPath);
        ClassDB::bind_method(D_METHOD("set_listener_path", "path"), &WASystemNode::setListenerPath);

        ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "listener_path", PROPERTY_HINT_NODE_TYPE, "WAListenerNode"),
                     "set_listener_path", "get_listener_path");

        ClassDB::bind_method(D_METHOD("get_sound_def", "sound_name"), &WASystemNode::getSoundDef);
    }

}
