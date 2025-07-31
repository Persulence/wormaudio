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

// Copied from godot-cpp/test/src and modified.

#include "gdextension_interface.h"

#include "godot_cpp/core/class_db.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"

#include "runtime/Runtime.hpp"

#include <memory>

#include "WormAudioGodot.hpp"

#include "resource/WASystemResource.hpp"
#include "WARuntime.hpp"
#include "node/WAListenerNode.hpp"
#include "node/WASystemNode.hpp"
#include "node/WASourceNode.hpp"
#include "sound/WASoundInstance.hpp"
#include "sound/WASoundDef.hpp"
#include "sound/WATransport.hpp"

namespace
{
    class GodotLoggerAdaptor : public juce::Logger
    {
    public:
        ~GodotLoggerAdaptor() override
        {
            setCurrentLogger(nullptr);
        }

    protected:
        void logMessage(const juce::String &message) override
        {
            wa::WormAudioGodot::log(wa::WormAudioGodot::INFO, message.toStdString());
        }
    };

    std::unique_ptr<GodotLoggerAdaptor> logger;

    /// @brief Called by Godot to let us register our classes with Godot.
    ///
    /// @param p_level the level being initialized by Godot
    ///
    /// @see GDExtensionInit
    void initializeExtension(godot::ModuleInitializationLevel p_level)
    {
        using namespace godot;
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
        {
            return;
        }

        logger = std::make_unique<GodotLoggerAdaptor>();
        juce::Logger::setCurrentLogger(logger.get());
        juce::Logger::writeToLog("WormAudio loaded!");
        wa::WormAudioGodot::getInstance().initContext();

        ClassDB::register_class<wa::WASystemResource>();
        ClassDB::register_class<wa::WASystemNode>();
        ClassDB::register_class<wa::WASourceNode>();
        ClassDB::register_class<wa::WAListenerNode>();
        ClassDB::register_class<wa::WARuntime>();
        ClassDB::register_class<wa::WATransport>();
        ClassDB::register_class<wa::WASoundDef>();
        ClassDB::register_class<wa::WASoundInstance>();
    }

    /// @brief Called by Godot to let us do any cleanup.
    ///
    /// @see GDExtensionInit
    void uninitializeExtension(godot::ModuleInitializationLevel p_level)
    {
        if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
        {
            wa::WormAudioGodot::getInstance().deInitContext();
            logger = nullptr;
        }
    }
}

extern "C"
{
/// @brief This is the entry point for the shared library.
///
/// @note The name of this function must match the "entry_symbol" in
/// templates/template.*.gdextension.in
///
/// @param p_get_proc_address the interface (need more info)
/// @param p_library the library (need more info)
/// @param r_initialization the intialization (need more info)
///
/// @returns GDExtensionBool
GDExtensionBool GDE_EXPORT GDExtensionInit(
        GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization)
{
    {
        godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
                                                       r_initialization);

        init_obj.register_initializer(initializeExtension);
        init_obj.register_terminator(uninitializeExtension);
        init_obj.set_minimum_library_initialization_level(
                godot::MODULE_INITIALIZATION_LEVEL_SCENE);

        return init_obj.init();
    }
}
}
