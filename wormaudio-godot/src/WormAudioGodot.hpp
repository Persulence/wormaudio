
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

#pragma once

#include <functional>
#include <memory>
#include <string>

// THESE SHOULDN'T BE HERE
// WHY WON'T IT COMPILE?
// THE DESTRUCTOR IS IMPLEMENTED IN THE IMPL FILE WHERE TYPES ARE NOT INCOMPLETE
#include <api/MessageThreadManager.hpp>
#include <godot_cpp/variant/string.hpp>

namespace runtime
{
    class Runtime;
}

namespace wa
{
    inline std::string toString(godot::String str)
    {
        return std::string{str.utf8().get_data()};
    }

    class MessageThreadManager;

    class WormAudioGodot
    {
    public:
        enum Level
        {
            INFO,
            ERROR,
            IMPORTANT,
        };

        static WormAudioGodot& getInstance()
        {
            static WormAudioGodot instance;
            return instance;
        }

        ~WormAudioGodot();

        void initContext() const;
        void deInitContext() const;

        runtime::Runtime& getRuntime() const;

        static void log(const std::string &message);
        static void log(Level level, const std::string &message);

        // Wrappers for juce message thread functions without having to include all the juce headers
        static void callAsync(std::function<void()> f);
        static void callSync(std::function<void()> f);

    private:
        WormAudioGodot();

        // std::unique_ptr<wa::MessageThreadManager> messageThreadManager;
        // std::thread messageThread;
        // std::unique_ptr<runtime::Runtime> runtime;
        // std::unique_ptr<juce::ScopedJuceInitialiser_GUI> scope;
        std::unique_ptr<MessageThreadManager> manager;
    };
}
